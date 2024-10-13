#ifndef RQT2_MYPKG__VISIBILITY_CONTROL_H_
#define RQT2_MYPKG__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define RQT2_MYPKG_EXPORT __attribute__ ((dllexport))
    #define RQT2_MYPKG_IMPORT __attribute__ ((dllimport))
  #else
    #define RQT2_MYPKG_EXPORT __declspec(dllexport)
    #define RQT2_MYPKG_IMPORT __declspec(dllimport)
  #endif
  #ifdef RQT2_MYPKG_BUILDING_LIBRARY
    #define RQT2_MYPKG_PUBLIC RQT2_MYPKG_EXPORT
  #else
    #define RQT2_MYPKG_PUBLIC RQT2_MYPKG_IMPORT
  #endif
  #define RQT2_MYPKG_PUBLIC_TYPE RQT2_MYPKG_PUBLIC
  #define RQT2_MYPKG_LOCAL
#else
  #define RQT2_MYPKG_EXPORT __attribute__ ((visibility("default")))
  #define RQT2_MYPKG_IMPORT
  #if __GNUC__ >= 4
    #define RQT2_MYPKG_PUBLIC __attribute__ ((visibility("default")))
    #define RQT2_MYPKG_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define RQT2_MYPKG_PUBLIC
    #define RQT2_MYPKG_LOCAL
  #endif
  #define RQT2_MYPKG_PUBLIC_TYPE
#endif

#endif  // RQT2_MYPKG__VISIBILITY_CONTROL_H_
