
#ifndef AMS_CORE_EXPORT_H
#define AMS_CORE_EXPORT_H

#ifdef SHARED_EXPORTS_BUILT_AS_STATIC
#  define AMS_CORE_EXPORT
#  define CORE_NO_EXPORT
#else
#  ifndef AMS_CORE_EXPORT
#    ifdef core_EXPORTS
        /* We are building this library */
#      define AMS_CORE_EXPORT 
#    else
        /* We are using this library */
#      define AMS_CORE_EXPORT 
#    endif
#  endif

#  ifndef CORE_NO_EXPORT
#    define CORE_NO_EXPORT 
#  endif
#endif

#ifndef CORE_DEPRECATED
#  define CORE_DEPRECATED __declspec(deprecated)
#endif

#ifndef CORE_DEPRECATED_EXPORT
#  define CORE_DEPRECATED_EXPORT AMS_CORE_EXPORT CORE_DEPRECATED
#endif

#ifndef CORE_DEPRECATED_NO_EXPORT
#  define CORE_DEPRECATED_NO_EXPORT CORE_NO_EXPORT CORE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CORE_NO_DEPRECATED
#    define CORE_NO_DEPRECATED
#  endif
#endif

#endif /* AMS_CORE_EXPORT_H */
