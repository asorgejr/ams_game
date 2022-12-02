
export module ams:UniquePtrExtensions;
#ifndef AMS_MODULES_STD
import <concepts>;
import <memory>;
import <type_traits>;
#else
import std;
#endif
import :config;
import ams.Exceptions;

namespace ams {

template<typename D, typename T>
concept DeleterT = requires(D d, T* t) {
  // the call operator exists
  { d(t) } -> std::same_as<void>;
};

template<class U, DeleterT<U> D> struct NotifyPtrs;
template<class U> class PtrToUnique;


struct _PtrToUniqueCbx {
  //Only these classes have access to private constructor
  template<class U, DeleterT<U> D> friend struct NotifyPtrs;
  template<class U> friend class PtrToUnique;

private:
  class ControlBlock
  {
    friend struct _PtrToUniqueCbx;

  private:
    unsigned int _referenceCount;//no. of PtrToUniques referencing it
    int _validCount;             //valid if non-zero. Also used to store dynamic array size

    enum
    {
      invalid = -1
    };

    inline bool isValid() const {
      //return (_validCount);
      return (_validCount > invalid);
    }
    inline void invalidate() {
      //_validCount = 0;
      _validCount = invalid;
    }
    inline bool decWeakCanDelete() {
      //return (0 == --_referenceCount + _validCount);
      return (--_referenceCount + _validCount < 0);
    }

  public:
    //construction
    inline constexpr ControlBlock(size_t count = 1)
        : _referenceCount(0), _validCount(count) {
    }
    // tests if _validCount is set non-zero
    inline bool getValid() const {
      return isValid();
    }
    //self destructs if no other references - otherwise zeroes _validCount
    inline void markInvalid() {
      if (0 == _referenceCount)
        delete this;
      else
        invalidate();
    }
    //increments observer count
    inline void addWeak() {
      _referenceCount++;
    }
    //decrements observer count and self destructs if result is zero
    inline void releaseWeak() {
      if (decWeakCanDelete())
        delete this;//nothing left referencing it
    }
  };//end class ControlBlock

  mutable ControlBlock* pCB;

  _PtrToUniqueCbx() : pCB(nullptr) {
  }
  inline bool checkValid() const {
    return (pCB) ? (pCB->isValid()) ? true : quickRelease() : false;
  }
  // only used by checkValid()
  bool quickRelease() const {
    pCB->releaseWeak();
    pCB = nullptr;
    return false;
  }
  void release() const {
    if (pCB) {
      pCB->releaseWeak();
      pCB = nullptr;
    }
  }

public:
  bool adoptBlockIfValid(_PtrToUniqueCbx const& src) {
    if (src.pCB && src.pCB->getValid()) {
      src.pCB->addWeak();
      pCB = src.pCB;
      return true;
    } else
      return false;
  }
  void adoptBlock(_PtrToUniqueCbx const& src) {
    if (src.pCB) {
      src.pCB->addWeak();
      pCB = src.pCB;
    }
  }
  inline void stealBlock(_PtrToUniqueCbx const& src) {
    pCB = src.pCB;
    src.pCB = nullptr;
  }
  void assureAndAdoptOwnerBlock(_PtrToUniqueCbx const& src, size_t arrayCount = 1) {
    if (nullptr == src.pCB)
      src.pCB = new ControlBlock(arrayCount);
    src.pCB->addWeak();
    pCB = src.pCB;
  }
  inline void markInvalid() const {
    if (pCB) {
      pCB->markInvalid();
      pCB = nullptr;
    }
  }
  void setOwnerBlock(size_t arrayCount) {
    if (pCB)
      pCB->markInvalid();
    pCB = new ControlBlock(arrayCount);
  }
  inline size_t arrayCount() const {
    return (nullptr == pCB || pCB->_validCount < 0) ? 0 : pCB->_validCount;
  }
};//end struct _PtrToUniqueCbx

template<class T, DeleterT<T> D>
struct MakeChooser {
  template<class... Types>
  static auto make(Types&&... args) {
    return (D::template allocate(std::forward<Types>(args)...));
  }
};
template<class T>
struct MakeChooser<T, std::default_delete<T>> {
  template<class... Types>
  static auto make(Types&&... args) {
    return (new T(std::forward<Types>(args)...));
  }
};

}// namespace ams


export namespace ams {

template<class T>
struct AllocatingDeleter {
  //required by std::unique_ptr
  void operator()(T* p) {
    delete p;
  }
  //required by make_notifying_unique
  template<class... Types>
  static inline T* allocate(Types&&... args) {
    return new T(std::forward<Types>(args)...);
  }
};
  
template<class T, DeleterT<T> D = std::default_delete<T>>
struct NotifyPtrs// if we derive from D, then operator D& () will never be called
{
private:
  //D will typically be dataless so we still need empty base class optimisation
  struct InnerDeleter : public D {
    mutable _PtrToUniqueCbx cbx;
  };
  InnerDeleter innerDeleter;// is a D

  template<class U>
  using if_base_of = std::enable_if_t<std::is_base_of<T, U>::value>;


  inline _PtrToUniqueCbx& getCbx() const {
    return innerDeleter.cbx;
  }

  template<class U, DeleterT<U> D> friend struct NotifyPtrs;
  template<class U> friend class PtrToUnique;

public:
  inline NotifyPtrs() {}

  //Explicitly handle move from NotifyingUniquePtr to NotifyingUniquePtr
  inline NotifyPtrs(NotifyPtrs const& deleter) {
    getCbx().pCB = deleter.getCbx().pCB;
  }
  template<class U, class = if_base_of<U>>
  inline NotifyPtrs(NotifyPtrs<U> const& deleter) {
    getCbx().pCB = deleter.getCbx().pCB;
  }

  //permit move from unique_ptr to NotifyingUniquePtr
  template<DeleterT D2, class = std::enable_if_t<std::is_convertible<D2, D>::value>>
  inline NotifyPtrs(const D2& deleter) {
  }
  template<DeleterT D2, class = std::enable_if_t<std::is_convertible<D2, D>::value>>
  inline auto& operator=(const D2& deleter) {
    getCbx().release();
    return *this;
  }

  //Permits and intercepts move from NotifyingUniquePtr to unique_ptr
  operator D&() {///plain unique_ptr doesnt support ref_ptrs
    //so any that reference this object must be zeroed
    getCbx().markInvalid();
    return innerDeleter;//return the passed in deleter
  }

  //The functor call to do the deletion
  void operator()(T* p) {
    //zero ref_ptrs that reference this object
    getCbx().markInvalid();
    //leave deletion to passed in deleter
    innerDeleter(p);
  }

  void resetAllPtrs() {
    getCbx().markInvalid();
  }
};

/**
  * @brief A type of std::unique_ptr which adds the ability to share weak pointers to it.
  * These pointers are guaranteed to read as null if the object has been deleted ensuring that it never dangles.
  */
template<class T, DeleterT<T> D = std::default_delete<T>>
using NotifyingUniquePtr = typename std::template unique_ptr<T, NotifyPtrs<T, D>>;

/**
  * @brief Makes a NotifyingUniquePtr.
  */
template<class T, DeleterT<T> D = std::default_delete<T>, class... Types, std::enable_if_t<!std::is_array_v<T>, int> = 0>
inline auto makeNotifyingUnique(Types&&... args) {
  return NotifyingUniquePtr<T, D>(
    MakeChooser<T, D>::make(std::forward<Types>(args)...));
}

/**
  * @brief Makes a NotifyingUniquePtr.
  */
template<class T, DeleterT<T> D = std::default_delete<T>, class... Types, std::enable_if_t<!std::is_array_v<T>, int> = 0>
inline auto customMakeUnique(Types&&... args) {
  return std::unique_ptr<T, D>(
    MakeChooser<T, D>::make(std::forward<Types>(args)...));
}

/**
  * @brief This is a weak pointer to a NotifyingUniquePtr. It is guaranteed to read as null if the object has been 
  * deleted ensuring that it never dangles.
  */
template<class T>
class PtrToUnique
{
  template<class U>
  using if_base_of = std::enable_if_t<std::is_base_of<T, U>::value>;

public:
  //default constructor - initialises as nullptr
  inline PtrToUnique() {}

  //destructor
  inline ~PtrToUnique() {
    cbx.release();
  }

  //Construction and assignment to nullptr
  inline PtrToUnique(std::nullptr_t) {}
  inline PtrToUnique const& operator=(std::nullptr_t) {
    cbx.release();
    return *this;
  }

  //Copy Construction and assignment explicit to prevent compiler defaults
  inline PtrToUnique(PtrToUnique const& ptr) {
    pointTo(ptr);
  }
  inline PtrToUnique const& operator=(PtrToUnique const& ptr) {
    cbx.release();
    pointTo(ptr);
    return *this;
  }

  //Construction and assignment from PtrToUnique<U>
  template<class U, class = if_base_of<U>>
  inline PtrToUnique(PtrToUnique<U> const& ptr) {
    pointTo(ptr);
  }
  template<class U, class = if_base_of<U>>
  inline PtrToUnique<T> const& operator=(PtrToUnique<U> const& ptr) {
    cbx.release();
    pointTo(ptr);
    return *this;
  }

  //Move Construction and assignment
  inline PtrToUnique(PtrToUnique const&& ptr) noexcept {
    accept_move(ptr);
  }
  inline PtrToUnique const& operator=(PtrToUnique const&& ptr) noexcept {
    cbx.release();
    accept_move(ptr);
    return *this;
  }

  //Move Construction and assignment from PtrToUnique<U>
  template<class U, class = if_base_of<U>>
  inline PtrToUnique(PtrToUnique<U> const&& ptr) {
    accept_move(ptr);
  }
  template<class U, class = if_base_of<U>>
  inline PtrToUnique<T> const& operator=(PtrToUnique<U> const&& ptr) {
    cbx.release();
    accept_move(ptr);
    return *this;
  }

  //Construction and assignment from NotifyingUniquePtr
  template<DeleterT<T> Del>
  inline PtrToUnique(NotifyingUniquePtr<T, Del> const& ptr) {
    pointTo(ptr);
  }
  template<DeleterT<T> Del>
  inline PtrToUnique& operator=(NotifyingUniquePtr<T, Del> const& ptr) {
    cbx.release();
    pointTo(ptr);
    return *this;
  }

  //Construction and assignment from NotifyingUniquePtr<U>
  template<class U, DeleterT<T> Del, class = if_base_of<U>>
  inline PtrToUnique(NotifyingUniquePtr<U, Del> const& ptr) {
    pointTo(ptr);
  }
  template<class U, DeleterT<T> Del, class = if_base_of<U>>
  inline PtrToUnique& operator=(NotifyingUniquePtr<U, Del> const& ptr) {
    cbx.release();
    pointTo(ptr);
    return *this;
  }

  //but PROHIBIT from a NotifyingUniquePtr going out of scope
  template<class U, DeleterT<T> Del>
  PtrToUnique(NotifyingUniquePtr<U, Del> const&& ptr) = delete;
  template<class U, DeleterT<T> Del>
  PtrToUnique& operator=(NotifyingUniquePtr<U, Del> const&& ptr) = delete;

  //boolean test
  inline explicit operator bool() const {
    return cbx.checkValid();
  }

  // get() extract raw pointer
  inline T* get() const {
    return checkedPointer();
  }

  //dereference
  inline T* const operator->() const {
    auto ret = checkedPointer();
    if constexpr (AMSExceptions) {
      if (!ret) {
        throw NullPointerException("PtrToUnique: Attempt to dereference a null pointer");
      }
    }
    return ret;
  }
  inline T& operator*() const {
    if constexpr (AMSExceptions)
      return (cbx.checkValid()) ? *_pT : throw NullPointerException("PtrToUnique: Attempt to dereference a null pointer");
    else
      return *_pT;
  }

  //casting
  template<class U, class = if_base_of<U>>
  PtrToUnique<U> staticPtrCast() {
    PtrToUnique<U> ptr;
    ptr._pT = static_cast<U*>(_pT);
    ptr.cbx.adoptBlock(cbx);
    return ptr;
  }

private:
  template<class U> friend class PtrToUnique;
  template<class _T> friend class _InwardsOffset;
  template<class _T> friend class _InwardsIndexOffset;

  //-----------------Data members------------------------
  //The pointer, local copy - ignored when control block says invalid
  mutable T* _pT;
  //control block connection - hold reliable validity flag
  mutable _PtrToUniqueCbx cbx;
  //------------------------------------------------------

  //service functions for construction and assignment
  template<class U>
  inline void pointTo(PtrToUnique<U> const& ptr) {
    if (cbx.adoptBlockIfValid(ptr.cbx))
      _pT = ptr._pT;
  }
  template<class U>
  inline void accept_move(PtrToUnique<U> const& ptr) {
    cbx.stealBlock(ptr.cbx);
    _pT = ptr._pT;
  }
  template<class U, DeleterT<T> D>
  inline void pointTo(NotifyingUniquePtr<U, D> const& ptr) {
    if ((_pT = ptr.get()))
      cbx.assureAndAdoptOwnerBlock(ptr.get_deleter().getCbx());
  }
  inline T* const checkedPointer() const {
    return (cbx.checkValid()) ? _pT : nullptr;
  }

  //Private aliasing constructors not called - available for extended functionality

  //from NotifyingUniquePtr
  template<class U, DeleterT<T> Del>
  inline PtrToUnique(NotifyingUniquePtr<U, Del> const& ptr, T* pTar) {
    if ((_pT = (ptr.get()) ? pTar : nullptr))
      cbx.assureAndAdoptOwnerBlock(ptr.get_deleter().cbx);
  }
  template<class U, DeleterT<T> Del>//don't cosume a unique_ptr
  inline PtrToUnique(NotifyingUniquePtr<U, Del> const&& ptr, T* pTar) = delete;

  //from PtrToUnique
  template<class U>
  inline PtrToUnique(PtrToUnique<U> const& ptr, T* pTar) {
    cbx.adoptBlock(ptr.cbx);
    _pT = pTar;
  }
  inline PtrToUnique(_PtrToUniqueCbx const& _cbx, T* pTar) {//Called when source is falling out of scope
    cbx.stealBlock(_cbx);                                                  //slightly faster
    _pT = pTar;
  }
};


template<class T, DeleterT<T> D>
inline auto& zeroPtrsTo(NotifyingUniquePtr<T, D>& ptr) {
  ptr.get_deleter().resetAllPtrs();
  return ptr;
}
template<class T, DeleterT<T> D>//dont't consume a unique_ptr
inline auto& zeroPtrsTo(NotifyingUniquePtr<T, D>&& ptr) = delete;


//________________Comparison - only == and != ____________________-

//________________ PtrToUnique with nullptr ________________________-

// ==
template<class L>
inline bool operator==(PtrToUnique<L> const& l_ptr, std::nullptr_t) {
  return l_ptr.get() == nullptr;
}
template<class R>
inline bool operator==(std::nullptr_t, PtrToUnique<R> const& r_ptr) {
  return nullptr == r_ptr.get();
}
// !=
template<class L>
inline bool operator!=(PtrToUnique<L> const& l_ptr, std::nullptr_t) {
  return l_ptr.get() != nullptr;
}
template<class R>
inline bool operator!=(std::nullptr_t, PtrToUnique<R> const& r_ptr) {
  return nullptr != r_ptr.get();
}

// __________________PtrToUnique with raw_pointer_______________________-

// ==
template<class L, class R>
inline bool operator==(PtrToUnique<L> const& l_ptr, R const* p) {
  return l_ptr.get() == p;
}
template<class L, class R>
inline bool operator==(L const* p, PtrToUnique<R> const& r_ptr) {
  return p == r_ptr.get();
}
// !=
template<class L, class R>
inline bool operator!=(PtrToUnique<L> const& l_ptr, R const* p) {
  return l_ptr.get() != p;
}
template<class L, class R>
inline bool operator!=(L const* p, PtrToUnique<R> const& r_ptr) {
  return p != r_ptr.get();
}

// ____________________PtrToUnique with PtrToUnique_____________________

// ==
template<class L, class R>
inline bool operator==(PtrToUnique<L> const& l_ptr, PtrToUnique<R> const& r_ptr) {
  return l_ptr.get() == r_ptr.get();
}
// !=
template<class L, class R>
inline bool operator!=(PtrToUnique<L> const& l_ptr, PtrToUnique<R> const& r_ptr) {
  return l_ptr.get() != r_ptr.get();
}

// _________________________PtrToUnique with NotifyingUniquePtr_________________

// ==
template<class L, class R, DeleterT<R> D>
inline bool operator==(PtrToUnique<L> const& l_ptr, NotifyingUniquePtr<R, D> const& r_ptr) {
  return l_ptr.get() == r_ptr.get();
}
template<class L, class R, DeleterT<R> D>
inline bool operator==(NotifyingUniquePtr<L, D> const& l_ptr, PtrToUnique<R> const& r_ptr) {
  return l_ptr.get() == r_ptr.get();
}
// !=
template<class L, class R, DeleterT<R> D>
inline bool operator!=(PtrToUnique<L> const& l_ptr, NotifyingUniquePtr<R, D> const& r_ptr) {
  return l_ptr.get() != r_ptr.get();
}
template<class L, class R, DeleterT<R> D>
inline bool operator!=(NotifyingUniquePtr<L, D> const& l_ptr, PtrToUnique<R> const& r_ptr) {
  return l_ptr.get() != r_ptr.get();
}

  
} // namespace ams
