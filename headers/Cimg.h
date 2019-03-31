/*
 #
 #  File            : CImg.h
 #                    ( C++ header file )
 #
 #  Description     : The C++ Template Image Processing Toolkit.
 #                    This file is the main component of the CImg Library project.
 #                    ( http://cimg.eu )
 #
 #  Project manager : David Tschumperle.
 #                    ( http://tschumperle.users.greyc.fr/ )
 #
 #                    A complete list of contributors is available in file 'README.txt'
 #                    distributed within the CImg package.
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.1
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL and CeCILL-C licenses and that you accept its terms.
 #
*/

// Set version number of the library.
#ifndef cimg_version
#define cimg_version 256

/*-----------------------------------------------------------
 #
 # Test and possibly auto-set CImg configuration variables
 # and include required headers.
 #
 # If you find that the default configuration variables are
 # not adapted to your system, you can override their values
 # before including the header file "CImg.h"
 # (use the #define directive).
 #
 ------------------------------------------------------------*/

// Include standard C++ headers.
// This is the minimal set of required headers to make CImg-based codes compile.
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <climits>
#include <ctime>
#include <exception>
#include <algorithm>

// Detect/configure OS variables.
//
// Define 'cimg_OS' to: '0' for an unknown OS (will try to minize library dependencies).
//                      '1' for a Unix-like OS (Linux, Solaris, BSD, MacOSX, Irix, ...).
//                      '2' for Microsoft Windows.
//                      (auto-detection is performed if 'cimg_OS' is not set by the user).
#ifndef cimg_OS
#if defined(unix)        || defined(__unix)      || defined(__unix__) \
 || defined(linux)       || defined(__linux)     || defined(__linux__) \
 || defined(sun)         || defined(__sun) \
 || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
 || defined(__FreeBSD__) || defined (__DragonFly__) \
 || defined(sgi)         || defined(__sgi) \
 || defined(__MACOSX__)  || defined(__APPLE__) \
 || defined(__CYGWIN__)
#define cimg_OS 1
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
   || defined(WIN64)    || defined(_WIN64) || defined(__WIN64__)
#define cimg_OS 2
#else
#define cimg_OS 0
#endif
#elif !(cimg_OS==0 || cimg_OS==1 || cimg_OS==2)
#error CImg Library: Invalid configuration variable 'cimg_OS'.
#error (correct values are '0 = unknown OS', '1 = Unix-like OS', '2 = Microsoft Windows').
#endif
#ifndef cimg_date
#define cimg_date __DATE__
#endif
#ifndef cimg_time
#define cimg_time __TIME__
#endif

// Disable silly warnings on some Microsoft VC++ compilers.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4319)
#pragma warning(disable:4512)
#pragma warning(disable:4571)
#pragma warning(disable:4640)
#pragma warning(disable:4706)
#pragma warning(disable:4710)
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4820)
#pragma warning(disable:4996)

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif
#endif

// Define correct string functions for each compiler and OS.
#if cimg_OS==2 && defined(_MSC_VER)
#define cimg_sscanf std::sscanf
#define cimg_sprintf std::sprintf
#define cimg_snprintf cimg::_snprintf
#define cimg_vsnprintf cimg::_vsnprintf
#else
#include <stdio.h>
#if defined(__MACOSX__) || defined(__APPLE__)
#define cimg_sscanf cimg::_sscanf
#define cimg_sprintf cimg::_sprintf
#define cimg_snprintf cimg::_snprintf
#define cimg_vsnprintf cimg::_vsnprintf
#else
#define cimg_sscanf std::sscanf
#define cimg_sprintf std::sprintf
#define cimg_snprintf snprintf
#define cimg_vsnprintf vsnprintf
#endif
#endif

// Include OS-specific headers.
#if cimg_OS==1
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#elif cimg_OS==2
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif
#include <shlobj.h>
#include <process.h>
#include <io.h>
#endif

// Look for C++11 features.
#ifndef cimg_use_cpp11
#if __cplusplus>201100
#define cimg_use_cpp11 1
#else
#define cimg_use_cpp11 0
#endif
#endif
#if cimg_use_cpp11==1
#include <initializer_list>
#include <utility>
#endif

// Convenient macro to define pragma
#ifdef _MSC_VER
#define cimg_pragma(x) __pragma(x)
#else
#define cimg_pragma(x) _Pragma(#x)
#endif

// Define own types 'cimg_long/ulong' and 'cimg_int64/uint64' to ensure portability.
// ( constrained to 'sizeof(cimg_ulong/cimg_long) = sizeof(void*)' and 'sizeof(cimg_int64/cimg_uint64)=8' ).
#if cimg_OS==2

#define cimg_uint64 unsigned __int64
#define cimg_int64 __int64
#define cimg_ulong UINT_PTR
#define cimg_long INT_PTR
#ifdef _MSC_VER
#define cimg_fuint64 "%I64u"
#define cimg_fint64 "%I64d"
#else
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#endif

#else

#if UINTPTR_MAX==0xffffffff || defined(__arm__) || defined(_M_ARM) || ((ULONG_MAX)==(UINT_MAX))
#define cimg_uint64 unsigned long long
#define cimg_int64 long long
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#else
#define cimg_uint64 unsigned long
#define cimg_int64 long
#define cimg_fuint64 "%lu"
#define cimg_fint64 "%ld"
#endif

#if defined(__arm__) || defined(_M_ARM)
#define cimg_ulong unsigned long long
#define cimg_long long long
#else
#define cimg_ulong unsigned long
#define cimg_long long
#endif

#endif

// Configure filename separator.
//
// Filename separator is set by default to '/', except for Windows where it is '\'.
#ifndef cimg_file_separator
#if cimg_OS==2
#define cimg_file_separator '\\'
#else
#define cimg_file_separator '/'
#endif
#endif

// Configure verbosity of output messages.
//
// Define 'cimg_verbosity' to: '0' to hide library messages (quiet mode).
//                             '1' to output library messages on the console.
//                             '2' to output library messages on a basic dialog window (default behavior).
//                             '3' to do as '1' + add extra warnings (may slow down the code!).
//                             '4' to do as '2' + add extra warnings (may slow down the code!).
//
// Define 'cimg_strict_warnings' to replace warning messages by exception throwns.
//
// Define 'cimg_use_vt100' to allow output of color messages on VT100-compatible terminals.
#ifndef cimg_verbosity
#if cimg_OS==2
#define cimg_verbosity 2
#else
#define cimg_verbosity 1
#endif
#elif !(cimg_verbosity==0 || cimg_verbosity==1 || cimg_verbosity==2 || cimg_verbosity==3 || cimg_verbosity==4)
#error CImg Library: Configuration variable 'cimg_verbosity' is badly defined.
#error (should be { 0=quiet | 1=console | 2=dialog | 3=console+warnings | 4=dialog+warnings }).
#endif

// Configure OpenMP support.
// (http://www.openmp.org)
//
// Define 'cimg_use_openmp' to enable OpenMP support (requires OpenMP 3.0+).
//
// OpenMP directives are used in many CImg functions to get
// advantages of multi-core CPUs.
#if !defined(cimg_use_openmp)
#ifdef _OPENMP
#define cimg_use_openmp 1
#else
#define cimg_use_openmp 0
#endif
#endif
#if cimg_use_openmp!=0
#include <omp.h>
#define cimg_pragma_openmp(p) cimg_pragma(omp p)
#else
#define cimg_pragma_openmp(p)
#endif

// Configure the 'abort' signal handler (does nothing by default).
// A typical signal handler can be defined in your own source like this:
// #define cimg_abort_test if (is_abort) throw CImgAbortException("")
//
// where 'is_abort' is a boolean variable defined somewhere in your code and reachable in the method.
// 'cimg_abort_test2' does the same but is called more often (in inner loops).
#if defined(cimg_abort_test) && cimg_use_openmp!=0

// Define abort macros to be used with OpenMP.
#ifndef _cimg_abort_init_omp
#define _cimg_abort_init_omp bool _cimg_abort_go_omp = true; cimg::unused(_cimg_abort_go_omp)
#endif
#ifndef _cimg_abort_try_omp
#define _cimg_abort_try_omp if (_cimg_abort_go_omp) try
#endif
#ifndef _cimg_abort_catch_omp
#define _cimg_abort_catch_omp catch (CImgAbortException&) { cimg_pragma(omp atomic) _cimg_abort_go_omp&=false; }
#endif
#ifdef cimg_abort_test2
#ifndef _cimg_abort_try_omp2
#define _cimg_abort_try_omp2 _cimg_abort_try_omp
#endif
#ifndef _cimg_abort_catch_omp2
#define _cimg_abort_catch_omp2 _cimg_abort_catch_omp
#endif
#ifndef _cimg_abort_catch_fill_omp
#define _cimg_abort_catch_fill_omp \
  catch (CImgException& e) { cimg_pragma(omp critical(abort)) CImg<charT>::string(e._message).move_to(is_error); \
                             cimg_pragma(omp atomic) _cimg_abort_go_omp&=false; }
#endif
#endif
#endif

#ifndef _cimg_abort_init_omp
#define _cimg_abort_init_omp
#endif
#ifndef _cimg_abort_try_omp
#define _cimg_abort_try_omp
#endif
#ifndef _cimg_abort_catch_omp
#define _cimg_abort_catch_omp
#endif
#ifndef _cimg_abort_try_omp2
#define _cimg_abort_try_omp2
#endif
#ifndef _cimg_abort_catch_omp2
#define _cimg_abort_catch_omp2
#endif
#ifndef _cimg_abort_catch_fill_omp
#define _cimg_abort_catch_fill_omp
#endif
#ifndef cimg_abort_init
#define cimg_abort_init
#endif
#ifndef cimg_abort_test
#define cimg_abort_test
#endif
#ifndef cimg_abort_test2
#define cimg_abort_test2
#endif

// Configure display framework.
//
// Define 'cimg_display' to: '0' to disable display capabilities.
//                           '1' to use the X-Window framework (X11).
//                           '2' to use the Microsoft GDI32 framework.
#ifndef cimg_display
#if cimg_OS==0
#define cimg_display 0
#elif cimg_OS==1
#define cimg_display 1
#elif cimg_OS==2
#define cimg_display 2
#endif
#elif !(cimg_display==0 || cimg_display==1 || cimg_display==2)
#error CImg Library: Configuration variable 'cimg_display' is badly defined.
#error (should be { 0=none | 1=X-Window (X11) | 2=Microsoft GDI32 }).
#endif

// Include display-specific headers.
#if cimg_display==1
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <pthread.h>
#ifdef cimg_use_xshm
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif
#ifdef cimg_use_xrandr
#include <X11/extensions/Xrandr.h>
#endif
#endif
#ifndef cimg_appname
#define cimg_appname "CImg"
#endif

// Configure OpenCV support.
// (http://opencv.willowgarage.com/wiki/)
//
// Define 'cimg_use_opencv' to enable OpenCV support.
//
// OpenCV library may be used to access images from cameras
// (see method 'CImg<T>::load_camera()').
#ifdef cimg_use_opencv
#ifdef True
#undef True
#define _cimg_redefine_True
#endif
#ifdef False
#undef False
#define _cimg_redefine_False
#endif
#ifdef Status
#undef Status
#define _cimg_redefine_Status
#endif
#include <cstddef>
#include <opencv2/opencv.hpp>
#if CV_MAJOR_VERSION >=3
#define _cimg_fourcc cv::VideoWriter::fourcc
#else
#define _cimg_fourcc CV_FOURCC
#endif
#endif

// Configure LibPNG support.
// (http://www.libpng.org)
//
// Define 'cimg_use_png' to enable LibPNG support.
//
// PNG library may be used to get a native support of '.png' files.
// (see methods 'CImg<T>::{load,save}_png()'.
#ifdef cimg_use_png
extern "C" {
#include "png.h"
}
#endif

// Configure LibJPEG support.
// (http://en.wikipedia.org/wiki/Libjpeg)
//
// Define 'cimg_use_jpeg' to enable LibJPEG support.
//
// JPEG library may be used to get a native support of '.jpg' files.
// (see methods 'CImg<T>::{load,save}_jpeg()').
#ifdef cimg_use_jpeg
extern "C" {
#include "jpeglib.h"
#include "setjmp.h"
}
#endif

// Configure LibTIFF support.
// (http://www.libtiff.org)
//
// Define 'cimg_use_tiff' to enable LibTIFF support.
//
// TIFF library may be used to get a native support of '.tif' files.
// (see methods 'CImg[List]<T>::{load,save}_tiff()').
#ifdef cimg_use_tiff
extern "C" {
#define uint64 uint64_hack_
#define int64 int64_hack_
#include "tiffio.h"
#undef uint64
#undef int64
}
#endif

// Configure LibMINC2 support.
// (http://en.wikibooks.org/wiki/MINC/Reference/MINC2.0_File_Format_Reference)
//
// Define 'cimg_use_minc2' to enable LibMINC2 support.
//
// MINC2 library may be used to get a native support of '.mnc' files.
// (see methods 'CImg<T>::{load,save}_minc2()').
#ifdef cimg_use_minc2
#include "minc_io_simple_volume.h"
#include "minc_1_simple.h"
#include "minc_1_simple_rw.h"
#endif

// Configure Zlib support.
// (http://www.zlib.net)
//
// Define 'cimg_use_zlib' to enable Zlib support.
//
// Zlib library may be used to allow compressed data in '.cimgz' files
// (see methods 'CImg[List]<T>::{load,save}_cimg()').
#ifdef cimg_use_zlib
extern "C" {
#include "zlib.h"
}
#endif

// Configure libcurl support.
// (http://curl.haxx.se/libcurl/)
//
// Define 'cimg_use_curl' to enable libcurl support.
//
// Libcurl may be used to get a native support of file downloading from the network.
// (see method 'cimg::load_network()'.)
#ifdef cimg_use_curl
#include "curl/curl.h"
#endif

// Configure Magick++ support.
// (http://www.imagemagick.org/Magick++)
//
// Define 'cimg_use_magick' to enable Magick++ support.
//
// Magick++ library may be used to get a native support of various image file formats.
// (see methods 'CImg<T>::{load,save}()').
#ifdef cimg_use_magick
#include "Magick++.h"
#endif

// Configure FFTW3 support.
// (http://www.fftw.org)
//
// Define 'cimg_use_fftw3' to enable libFFTW3 support.
//
// FFTW3 library may be used to efficiently compute the Fast Fourier Transform
// of image data, without restriction on the image size.
// (see method 'CImg[List]<T>::FFT()').
#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

// Configure LibBoard support.
// (http://libboard.sourceforge.net/)
//
// Define 'cimg_use_board' to enable Board support.
//
// Board library may be used to draw 3D objects in vector-graphics canvas
// that can be saved as '.ps' or '.svg' files afterwards.
// (see method 'CImg<T>::draw_object3d()').
#ifdef cimg_use_board
#include "Board.h"
#endif

// Configure OpenEXR support.
// (http://www.openexr.com/)
//
// Define 'cimg_use_openexr' to enable OpenEXR support.
//
// OpenEXR library may be used to get a native support of '.exr' files.
// (see methods 'CImg<T>::{load,save}_exr()').
#ifdef cimg_use_openexr
#include "ImfRgbaFile.h"
#include "ImfInputFile.h"
#include "ImfChannelList.h"
#include "ImfMatrixAttribute.h"
#include "ImfArray.h"
#endif

// Configure TinyEXR support.
// (https://github.com/syoyo/tinyexr)
//
// Define 'cimg_use_tinyexr' to enable TinyEXR support.
//
// TinyEXR is a small, single header-only library to load and save OpenEXR(.exr) images.
#ifdef cimg_use_tinyexr
#ifndef TINYEXR_IMPLEMENTATION
#define TINYEXR_IMPLEMENTATION
#endif
#include "tinyexr.h"
#endif

// Lapack configuration.
// (http://www.netlib.org/lapack)
//
// Define 'cimg_use_lapack' to enable LAPACK support.
//
// Lapack library may be used in several CImg methods to speed up
// matrix computations (eigenvalues, inverse, ...).
#ifdef cimg_use_lapack
extern "C" {
extern void sgetrf_(int*, int*, float*, int*, int*, int*);
extern void sgetri_(int*, float*, int*, int*, float*, int*, int*);
extern void sgetrs_(char*, int*, int*, float*, int*, int*, float*, int*, int*);
extern void sgesvd_(char*, char*, int*, int*, float*, int*, float*, float*, int*, float*, int*, float*, int*, int*);
extern void ssyev_(char*, char*, int*, float*, int*, float*, float*, int*, int*);
extern void dgetrf_(int*, int*, double*, int*, int*, int*);
extern void dgetri_(int*, double*, int*, int*, double*, int*, int*);
extern void dgetrs_(char*, int*, int*, double*, int*, int*, double*, int*, int*);
extern void dgesvd_(char*, char*, int*, int*, double*, int*, double*, double*,
int*, double*, int*, double*, int*, int*);
extern void dsyev_(char*, char*, int*, double*, int*, double*, double*, int*, int*);
extern void dgels_(char*, int*,int*,int*,double*,int*,double*,int*,double*,int*,int*);
extern void sgels_(char*, int*,int*,int*,float*,int*,float*,int*,float*,int*,int*);
}
#endif

// Check if min/max/PI macros are defined.
//
// CImg does not compile if macros 'min', 'max' or 'PI' are defined,
// because it redefines functions min(), max() and const variable PI in the cimg:: namespace.
// so it '#undef' these macros if necessary, and restore them to reasonable
// values at the end of this file.
#ifdef min
#undef min
#define _cimg_redefine_min
#endif
#ifdef max
#undef max
#define _cimg_redefine_max
#endif
#ifdef PI
#undef PI
#define _cimg_redefine_PI
#endif

// Define 'cimg_library' namespace suffix.
//
// You may want to add a suffix to the 'cimg_library' namespace, for instance if you need to work
// with several versions of the library at the same time.
#ifdef cimg_namespace_suffix
#define __cimg_library_suffixed(s) cimg_library_##s
#define _cimg_library_suffixed(s) __cimg_library_suffixed(s)
#define cimg_library_suffixed _cimg_library_suffixed(cimg_namespace_suffix)
#else
#define cimg_library_suffixed cimg_library
#endif

/*------------------------------------------------------------------------------
  #
  # Define user-friendly macros.
  #
  # These CImg macros are prefixed by 'cimg_' and can be used safely in your own
  # code. They are useful to parse command line options, or to write image loops.
  #
  ------------------------------------------------------------------------------*/

// Macros to define program usage, and retrieve command line arguments.
#define cimg_usage(usage) cimg_library_suffixed::cimg::option((char*)0,argc,argv,(char*)0,usage,false)
#define cimg_help(str) cimg_library_suffixed::cimg::option((char*)0,argc,argv,str,(char*)0)
#define cimg_option(name,defaut,usage) cimg_library_suffixed::cimg::option(name,argc,argv,defaut,usage)

// Macros to define and manipulate local neighborhoods.
#define CImg_2x2(I,T) T I[4]; \
                      T& I##cc = I[0]; T& I##nc = I[1]; \
                      T& I##cn = I[2]; T& I##nn = I[3]; \
                      I##cc = I##nc = \
                      I##cn = I##nn = 0

#define CImg_3x3(I,T) T I[9]; \
                      T& I##pp = I[0]; T& I##cp = I[1]; T& I##np = I[2]; \
                      T& I##pc = I[3]; T& I##cc = I[4]; T& I##nc = I[5]; \
                      T& I##pn = I[6]; T& I##cn = I[7]; T& I##nn = I[8]; \
                      I##pp = I##cp = I##np = \
                      I##pc = I##cc = I##nc = \
                      I##pn = I##cn = I##nn = 0

#define CImg_4x4(I,T) T I[16]; \
                      T& I##pp = I[0]; T& I##cp = I[1]; T& I##np = I[2]; T& I##ap = I[3]; \
                      T& I##pc = I[4]; T& I##cc = I[5]; T& I##nc = I[6]; T& I##ac = I[7]; \
                      T& I##pn = I[8]; T& I##cn = I[9]; T& I##nn = I[10]; T& I##an = I[11]; \
                      T& I##pa = I[12]; T& I##ca = I[13]; T& I##na = I[14]; T& I##aa = I[15]; \
                      I##pp = I##cp = I##np = I##ap = \
                      I##pc = I##cc = I##nc = I##ac = \
                      I##pn = I##cn = I##nn = I##an = \
                      I##pa = I##ca = I##na = I##aa = 0

#define CImg_5x5(I,T) T I[25]; \
                      T& I##bb = I[0]; T& I##pb = I[1]; T& I##cb = I[2]; T& I##nb = I[3]; T& I##ab = I[4]; \
                      T& I##bp = I[5]; T& I##pp = I[6]; T& I##cp = I[7]; T& I##np = I[8]; T& I##ap = I[9]; \
                      T& I##bc = I[10]; T& I##pc = I[11]; T& I##cc = I[12]; T& I##nc = I[13]; T& I##ac = I[14]; \
                      T& I##bn = I[15]; T& I##pn = I[16]; T& I##cn = I[17]; T& I##nn = I[18]; T& I##an = I[19]; \
                      T& I##ba = I[20]; T& I##pa = I[21]; T& I##ca = I[22]; T& I##na = I[23]; T& I##aa = I[24]; \
                      I##bb = I##pb = I##cb = I##nb = I##ab = \
                      I##bp = I##pp = I##cp = I##np = I##ap = \
                      I##bc = I##pc = I##cc = I##nc = I##ac = \
                      I##bn = I##pn = I##cn = I##nn = I##an = \
                      I##ba = I##pa = I##ca = I##na = I##aa = 0

#define CImg_2x2x2(I,T) T I[8]; \
                      T& I##ccc = I[0]; T& I##ncc = I[1]; \
                      T& I##cnc = I[2]; T& I##nnc = I[3]; \
                      T& I##ccn = I[4]; T& I##ncn = I[5]; \
                      T& I##cnn = I[6]; T& I##nnn = I[7]; \
                      I##ccc = I##ncc = \
                      I##cnc = I##nnc = \
                      I##ccn = I##ncn = \
                      I##cnn = I##nnn = 0

#define CImg_3x3x3(I,T) T I[27]; \
                      T& I##ppp = I[0]; T& I##cpp = I[1]; T& I##npp = I[2]; \
                      T& I##pcp = I[3]; T& I##ccp = I[4]; T& I##ncp = I[5]; \
                      T& I##pnp = I[6]; T& I##cnp = I[7]; T& I##nnp = I[8]; \
                      T& I##ppc = I[9]; T& I##cpc = I[10]; T& I##npc = I[11]; \
                      T& I##pcc = I[12]; T& I##ccc = I[13]; T& I##ncc = I[14]; \
                      T& I##pnc = I[15]; T& I##cnc = I[16]; T& I##nnc = I[17]; \
                      T& I##ppn = I[18]; T& I##cpn = I[19]; T& I##npn = I[20]; \
                      T& I##pcn = I[21]; T& I##ccn = I[22]; T& I##ncn = I[23]; \
                      T& I##pnn = I[24]; T& I##cnn = I[25]; T& I##nnn = I[26]; \
                      I##ppp = I##cpp = I##npp = \
                      I##pcp = I##ccp = I##ncp = \
                      I##pnp = I##cnp = I##nnp = \
                      I##ppc = I##cpc = I##npc = \
                      I##pcc = I##ccc = I##ncc = \
                      I##pnc = I##cnc = I##nnc = \
                      I##ppn = I##cpn = I##npn = \
                      I##pcn = I##ccn = I##ncn = \
                      I##pnn = I##cnn = I##nnn = 0

#define cimg_get2x2(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(x,y,z,c), I[1] = (T)(img)(_n1##x,y,z,c), I[2] = (T)(img)(x,_n1##y,z,c), \
  I[3] = (T)(img)(_n1##x,_n1##y,z,c)

#define cimg_get3x3(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,z,c), I[1] = (T)(img)(x,_p1##y,z,c), I[2] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[3] = (T)(img)(_p1##x,y,z,c), I[4] = (T)(img)(x,y,z,c), I[5] = (T)(img)(_n1##x,y,z,c), \
  I[6] = (T)(img)(_p1##x,_n1##y,z,c), I[7] = (T)(img)(x,_n1##y,z,c), I[8] = (T)(img)(_n1##x,_n1##y,z,c)

#define cimg_get4x4(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,z,c), I[1] = (T)(img)(x,_p1##y,z,c), I[2] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[3] = (T)(img)(_n2##x,_p1##y,z,c), I[4] = (T)(img)(_p1##x,y,z,c), I[5] = (T)(img)(x,y,z,c), \
  I[6] = (T)(img)(_n1##x,y,z,c), I[7] = (T)(img)(_n2##x,y,z,c), I[8] = (T)(img)(_p1##x,_n1##y,z,c), \
  I[9] = (T)(img)(x,_n1##y,z,c), I[10] = (T)(img)(_n1##x,_n1##y,z,c), I[11] = (T)(img)(_n2##x,_n1##y,z,c), \
  I[12] = (T)(img)(_p1##x,_n2##y,z,c), I[13] = (T)(img)(x,_n2##y,z,c), I[14] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[15] = (T)(img)(_n2##x,_n2##y,z,c)

#define cimg_get5x5(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p2##x,_p2##y,z,c), I[1] = (T)(img)(_p1##x,_p2##y,z,c), I[2] = (T)(img)(x,_p2##y,z,c), \
  I[3] = (T)(img)(_n1##x,_p2##y,z,c), I[4] = (T)(img)(_n2##x,_p2##y,z,c), I[5] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[6] = (T)(img)(_p1##x,_p1##y,z,c), I[7] = (T)(img)(x,_p1##y,z,c), I[8] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[9] = (T)(img)(_n2##x,_p1##y,z,c), I[10] = (T)(img)(_p2##x,y,z,c), I[11] = (T)(img)(_p1##x,y,z,c), \
  I[12] = (T)(img)(x,y,z,c), I[13] = (T)(img)(_n1##x,y,z,c), I[14] = (T)(img)(_n2##x,y,z,c), \
  I[15] = (T)(img)(_p2##x,_n1##y,z,c), I[16] = (T)(img)(_p1##x,_n1##y,z,c), I[17] = (T)(img)(x,_n1##y,z,c), \
  I[18] = (T)(img)(_n1##x,_n1##y,z,c), I[19] = (T)(img)(_n2##x,_n1##y,z,c), I[20] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[21] = (T)(img)(_p1##x,_n2##y,z,c), I[22] = (T)(img)(x,_n2##y,z,c), I[23] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[24] = (T)(img)(_n2##x,_n2##y,z,c)

#define cimg_get6x6(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p2##x,_p2##y,z,c), I[1] = (T)(img)(_p1##x,_p2##y,z,c), I[2] = (T)(img)(x,_p2##y,z,c), \
  I[3] = (T)(img)(_n1##x,_p2##y,z,c), I[4] = (T)(img)(_n2##x,_p2##y,z,c), I[5] = (T)(img)(_n3##x,_p2##y,z,c), \
  I[6] = (T)(img)(_p2##x,_p1##y,z,c), I[7] = (T)(img)(_p1##x,_p1##y,z,c), I[8] = (T)(img)(x,_p1##y,z,c), \
  I[9] = (T)(img)(_n1##x,_p1##y,z,c), I[10] = (T)(img)(_n2##x,_p1##y,z,c), I[11] = (T)(img)(_n3##x,_p1##y,z,c), \
  I[12] = (T)(img)(_p2##x,y,z,c), I[13] = (T)(img)(_p1##x,y,z,c), I[14] = (T)(img)(x,y,z,c), \
  I[15] = (T)(img)(_n1##x,y,z,c), I[16] = (T)(img)(_n2##x,y,z,c), I[17] = (T)(img)(_n3##x,y,z,c), \
  I[18] = (T)(img)(_p2##x,_n1##y,z,c), I[19] = (T)(img)(_p1##x,_n1##y,z,c), I[20] = (T)(img)(x,_n1##y,z,c), \
  I[21] = (T)(img)(_n1##x,_n1##y,z,c), I[22] = (T)(img)(_n2##x,_n1##y,z,c), I[23] = (T)(img)(_n3##x,_n1##y,z,c), \
  I[24] = (T)(img)(_p2##x,_n2##y,z,c), I[25] = (T)(img)(_p1##x,_n2##y,z,c), I[26] = (T)(img)(x,_n2##y,z,c), \
  I[27] = (T)(img)(_n1##x,_n2##y,z,c), I[28] = (T)(img)(_n2##x,_n2##y,z,c), I[29] = (T)(img)(_n3##x,_n2##y,z,c), \
  I[30] = (T)(img)(_p2##x,_n3##y,z,c), I[31] = (T)(img)(_p1##x,_n3##y,z,c), I[32] = (T)(img)(x,_n3##y,z,c), \
  I[33] = (T)(img)(_n1##x,_n3##y,z,c), I[34] = (T)(img)(_n2##x,_n3##y,z,c), I[35] = (T)(img)(_n3##x,_n3##y,z,c)

#define cimg_get7x7(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p3##x,_p3##y,z,c), I[1] = (T)(img)(_p2##x,_p3##y,z,c), I[2] = (T)(img)(_p1##x,_p3##y,z,c), \
  I[3] = (T)(img)(x,_p3##y,z,c), I[4] = (T)(img)(_n1##x,_p3##y,z,c), I[5] = (T)(img)(_n2##x,_p3##y,z,c), \
  I[6] = (T)(img)(_n3##x,_p3##y,z,c), I[7] = (T)(img)(_p3##x,_p2##y,z,c), I[8] = (T)(img)(_p2##x,_p2##y,z,c), \
  I[9] = (T)(img)(_p1##x,_p2##y,z,c), I[10] = (T)(img)(x,_p2##y,z,c), I[11] = (T)(img)(_n1##x,_p2##y,z,c), \
  I[12] = (T)(img)(_n2##x,_p2##y,z,c), I[13] = (T)(img)(_n3##x,_p2##y,z,c), I[14] = (T)(img)(_p3##x,_p1##y,z,c), \
  I[15] = (T)(img)(_p2##x,_p1##y,z,c), I[16] = (T)(img)(_p1##x,_p1##y,z,c), I[17] = (T)(img)(x,_p1##y,z,c), \
  I[18] = (T)(img)(_n1##x,_p1##y,z,c), I[19] = (T)(img)(_n2##x,_p1##y,z,c), I[20] = (T)(img)(_n3##x,_p1##y,z,c), \
  I[21] = (T)(img)(_p3##x,y,z,c), I[22] = (T)(img)(_p2##x,y,z,c), I[23] = (T)(img)(_p1##x,y,z,c), \
  I[24] = (T)(img)(x,y,z,c), I[25] = (T)(img)(_n1##x,y,z,c), I[26] = (T)(img)(_n2##x,y,z,c), \
  I[27] = (T)(img)(_n3##x,y,z,c), I[28] = (T)(img)(_p3##x,_n1##y,z,c), I[29] = (T)(img)(_p2##x,_n1##y,z,c), \
  I[30] = (T)(img)(_p1##x,_n1##y,z,c), I[31] = (T)(img)(x,_n1##y,z,c), I[32] = (T)(img)(_n1##x,_n1##y,z,c), \
  I[33] = (T)(img)(_n2##x,_n1##y,z,c), I[34] = (T)(img)(_n3##x,_n1##y,z,c), I[35] = (T)(img)(_p3##x,_n2##y,z,c), \
  I[36] = (T)(img)(_p2##x,_n2##y,z,c), I[37] = (T)(img)(_p1##x,_n2##y,z,c), I[38] = (T)(img)(x,_n2##y,z,c), \
  I[39] = (T)(img)(_n1##x,_n2##y,z,c), I[40] = (T)(img)(_n2##x,_n2##y,z,c), I[41] = (T)(img)(_n3##x,_n2##y,z,c), \
  I[42] = (T)(img)(_p3##x,_n3##y,z,c), I[43] = (T)(img)(_p2##x,_n3##y,z,c), I[44] = (T)(img)(_p1##x,_n3##y,z,c), \
  I[45] = (T)(img)(x,_n3##y,z,c), I[46] = (T)(img)(_n1##x,_n3##y,z,c), I[47] = (T)(img)(_n2##x,_n3##y,z,c), \
  I[48] = (T)(img)(_n3##x,_n3##y,z,c)

#define cimg_get8x8(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p3##x,_p3##y,z,c), I[1] = (T)(img)(_p2##x,_p3##y,z,c), I[2] = (T)(img)(_p1##x,_p3##y,z,c), \
  I[3] = (T)(img)(x,_p3##y,z,c), I[4] = (T)(img)(_n1##x,_p3##y,z,c), I[5] = (T)(img)(_n2##x,_p3##y,z,c), \
  I[6] = (T)(img)(_n3##x,_p3##y,z,c), I[7] = (T)(img)(_n4##x,_p3##y,z,c), I[8] = (T)(img)(_p3##x,_p2##y,z,c), \
  I[9] = (T)(img)(_p2##x,_p2##y,z,c), I[10] = (T)(img)(_p1##x,_p2##y,z,c), I[11] = (T)(img)(x,_p2##y,z,c), \
  I[12] = (T)(img)(_n1##x,_p2##y,z,c), I[13] = (T)(img)(_n2##x,_p2##y,z,c), I[14] = (T)(img)(_n3##x,_p2##y,z,c), \
  I[15] = (T)(img)(_n4##x,_p2##y,z,c), I[16] = (T)(img)(_p3##x,_p1##y,z,c), I[17] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[18] = (T)(img)(_p1##x,_p1##y,z,c), I[19] = (T)(img)(x,_p1##y,z,c), I[20] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[21] = (T)(img)(_n2##x,_p1##y,z,c), I[22] = (T)(img)(_n3##x,_p1##y,z,c), I[23] = (T)(img)(_n4##x,_p1##y,z,c), \
  I[24] = (T)(img)(_p3##x,y,z,c), I[25] = (T)(img)(_p2##x,y,z,c), I[26] = (T)(img)(_p1##x,y,z,c), \
  I[27] = (T)(img)(x,y,z,c), I[28] = (T)(img)(_n1##x,y,z,c), I[29] = (T)(img)(_n2##x,y,z,c), \
  I[30] = (T)(img)(_n3##x,y,z,c), I[31] = (T)(img)(_n4##x,y,z,c), I[32] = (T)(img)(_p3##x,_n1##y,z,c), \
  I[33] = (T)(img)(_p2##x,_n1##y,z,c), I[34] = (T)(img)(_p1##x,_n1##y,z,c), I[35] = (T)(img)(x,_n1##y,z,c), \
  I[36] = (T)(img)(_n1##x,_n1##y,z,c), I[37] = (T)(img)(_n2##x,_n1##y,z,c), I[38] = (T)(img)(_n3##x,_n1##y,z,c), \
  I[39] = (T)(img)(_n4##x,_n1##y,z,c), I[40] = (T)(img)(_p3##x,_n2##y,z,c), I[41] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[42] = (T)(img)(_p1##x,_n2##y,z,c), I[43] = (T)(img)(x,_n2##y,z,c), I[44] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[45] = (T)(img)(_n2##x,_n2##y,z,c), I[46] = (T)(img)(_n3##x,_n2##y,z,c), I[47] = (T)(img)(_n4##x,_n2##y,z,c), \
  I[48] = (T)(img)(_p3##x,_n3##y,z,c), I[49] = (T)(img)(_p2##x,_n3##y,z,c), I[50] = (T)(img)(_p1##x,_n3##y,z,c), \
  I[51] = (T)(img)(x,_n3##y,z,c), I[52] = (T)(img)(_n1##x,_n3##y,z,c), I[53] = (T)(img)(_n2##x,_n3##y,z,c), \
  I[54] = (T)(img)(_n3##x,_n3##y,z,c), I[55] = (T)(img)(_n4##x,_n3##y,z,c), I[56] = (T)(img)(_p3##x,_n4##y,z,c), \
  I[57] = (T)(img)(_p2##x,_n4##y,z,c), I[58] = (T)(img)(_p1##x,_n4##y,z,c), I[59] = (T)(img)(x,_n4##y,z,c), \
  I[60] = (T)(img)(_n1##x,_n4##y,z,c), I[61] = (T)(img)(_n2##x,_n4##y,z,c), I[62] = (T)(img)(_n3##x,_n4##y,z,c), \
  I[63] = (T)(img)(_n4##x,_n4##y,z,c);

#define cimg_get9x9(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p4##x,_p4##y,z,c), I[1] = (T)(img)(_p3##x,_p4##y,z,c), I[2] = (T)(img)(_p2##x,_p4##y,z,c), \
  I[3] = (T)(img)(_p1##x,_p4##y,z,c), I[4] = (T)(img)(x,_p4##y,z,c), I[5] = (T)(img)(_n1##x,_p4##y,z,c), \
  I[6] = (T)(img)(_n2##x,_p4##y,z,c), I[7] = (T)(img)(_n3##x,_p4##y,z,c), I[8] = (T)(img)(_n4##x,_p4##y,z,c), \
  I[9] = (T)(img)(_p4##x,_p3##y,z,c), I[10] = (T)(img)(_p3##x,_p3##y,z,c), I[11] = (T)(img)(_p2##x,_p3##y,z,c), \
  I[12] = (T)(img)(_p1##x,_p3##y,z,c), I[13] = (T)(img)(x,_p3##y,z,c), I[14] = (T)(img)(_n1##x,_p3##y,z,c), \
  I[15] = (T)(img)(_n2##x,_p3##y,z,c), I[16] = (T)(img)(_n3##x,_p3##y,z,c), I[17] = (T)(img)(_n4##x,_p3##y,z,c), \
  I[18] = (T)(img)(_p4##x,_p2##y,z,c), I[19] = (T)(img)(_p3##x,_p2##y,z,c), I[20] = (T)(img)(_p2##x,_p2##y,z,c), \
  I[21] = (T)(img)(_p1##x,_p2##y,z,c), I[22] = (T)(img)(x,_p2##y,z,c), I[23] = (T)(img)(_n1##x,_p2##y,z,c), \
  I[24] = (T)(img)(_n2##x,_p2##y,z,c), I[25] = (T)(img)(_n3##x,_p2##y,z,c), I[26] = (T)(img)(_n4##x,_p2##y,z,c), \
  I[27] = (T)(img)(_p4##x,_p1##y,z,c), I[28] = (T)(img)(_p3##x,_p1##y,z,c), I[29] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[30] = (T)(img)(_p1##x,_p1##y,z,c), I[31] = (T)(img)(x,_p1##y,z,c), I[32] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[33] = (T)(img)(_n2##x,_p1##y,z,c), I[34] = (T)(img)(_n3##x,_p1##y,z,c), I[35] = (T)(img)(_n4##x,_p1##y,z,c), \
  I[36] = (T)(img)(_p4##x,y,z,c), I[37] = (T)(img)(_p3##x,y,z,c), I[38] = (T)(img)(_p2##x,y,z,c), \
  I[39] = (T)(img)(_p1##x,y,z,c), I[40] = (T)(img)(x,y,z,c), I[41] = (T)(img)(_n1##x,y,z,c), \
  I[42] = (T)(img)(_n2##x,y,z,c), I[43] = (T)(img)(_n3##x,y,z,c), I[44] = (T)(img)(_n4##x,y,z,c), \
  I[45] = (T)(img)(_p4##x,_n1##y,z,c), I[46] = (T)(img)(_p3##x,_n1##y,z,c), I[47] = (T)(img)(_p2##x,_n1##y,z,c), \
  I[48] = (T)(img)(_p1##x,_n1##y,z,c), I[49] = (T)(img)(x,_n1##y,z,c), I[50] = (T)(img)(_n1##x,_n1##y,z,c), \
  I[51] = (T)(img)(_n2##x,_n1##y,z,c), I[52] = (T)(img)(_n3##x,_n1##y,z,c), I[53] = (T)(img)(_n4##x,_n1##y,z,c), \
  I[54] = (T)(img)(_p4##x,_n2##y,z,c), I[55] = (T)(img)(_p3##x,_n2##y,z,c), I[56] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[57] = (T)(img)(_p1##x,_n2##y,z,c), I[58] = (T)(img)(x,_n2##y,z,c), I[59] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[60] = (T)(img)(_n2##x,_n2##y,z,c), I[61] = (T)(img)(_n3##x,_n2##y,z,c), I[62] = (T)(img)(_n4##x,_n2##y,z,c), \
  I[63] = (T)(img)(_p4##x,_n3##y,z,c), I[64] = (T)(img)(_p3##x,_n3##y,z,c), I[65] = (T)(img)(_p2##x,_n3##y,z,c), \
  I[66] = (T)(img)(_p1##x,_n3##y,z,c), I[67] = (T)(img)(x,_n3##y,z,c), I[68] = (T)(img)(_n1##x,_n3##y,z,c), \
  I[69] = (T)(img)(_n2##x,_n3##y,z,c), I[70] = (T)(img)(_n3##x,_n3##y,z,c), I[71] = (T)(img)(_n4##x,_n3##y,z,c), \
  I[72] = (T)(img)(_p4##x,_n4##y,z,c), I[73] = (T)(img)(_p3##x,_n4##y,z,c), I[74] = (T)(img)(_p2##x,_n4##y,z,c), \
  I[75] = (T)(img)(_p1##x,_n4##y,z,c), I[76] = (T)(img)(x,_n4##y,z,c), I[77] = (T)(img)(_n1##x,_n4##y,z,c), \
  I[78] = (T)(img)(_n2##x,_n4##y,z,c), I[79] = (T)(img)(_n3##x,_n4##y,z,c), I[80] = (T)(img)(_n4##x,_n4##y,z,c)

#define cimg_get2x2x2(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(x,y,z,c), I[1] = (T)(img)(_n1##x,y,z,c), I[2] = (T)(img)(x,_n1##y,z,c), \
  I[3] = (T)(img)(_n1##x,_n1##y,z,c), I[4] = (T)(img)(x,y,_n1##z,c), I[5] = (T)(img)(_n1##x,y,_n1##z,c), \
  I[6] = (T)(img)(x,_n1##y,_n1##z,c), I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)

#define cimg_get3x3x3(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,_p1##z,c), I[1] = (T)(img)(x,_p1##y,_p1##z,c), \
  I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c), I[3] = (T)(img)(_p1##x,y,_p1##z,c), I[4] = (T)(img)(x,y,_p1##z,c), \
  I[5] = (T)(img)(_n1##x,y,_p1##z,c), I[6] = (T)(img)(_p1##x,_n1##y,_p1##z,c), I[7] = (T)(img)(x,_n1##y,_p1##z,c), \
  I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c), I[9] = (T)(img)(_p1##x,_p1##y,z,c), I[10] = (T)(img)(x,_p1##y,z,c), \
  I[11] = (T)(img)(_n1##x,_p1##y,z,c), I[12] = (T)(img)(_p1##x,y,z,c), I[13] = (T)(img)(x,y,z,c), \
  I[14] = (T)(img)(_n1##x,y,z,c), I[15] = (T)(img)(_p1##x,_n1##y,z,c), I[16] = (T)(img)(x,_n1##y,z,c), \
  I[17] = (T)(img)(_n1##x,_n1##y,z,c), I[18] = (T)(img)(_p1##x,_p1##y,_n1##z,c), I[19] = (T)(img)(x,_p1##y,_n1##z,c), \
  I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c), I[21] = (T)(img)(_p1##x,y,_n1##z,c), I[22] = (T)(img)(x,y,_n1##z,c), \
  I[23] = (T)(img)(_n1##x,y,_n1##z,c), I[24] = (T)(img)(_p1##x,_n1##y,_n1##z,c), I[25] = (T)(img)(x,_n1##y,_n1##z,c), \
  I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)

// Macros to perform various image loops.
//
// These macros are simpler to use than loops with C++ iterators.
#define cimg_for(img,ptrs,T_ptrs) \
  for (T_ptrs *ptrs = (img)._data, *_max##ptrs = (img)._data + (img).size(); ptrs<_max##ptrs; ++ptrs)
#define cimg_rof(img,ptrs,T_ptrs) for (T_ptrs *ptrs = (img)._data + (img).size() - 1; ptrs>=(img)._data; --ptrs)
#define cimg_foroff(img,off) for (cimg_ulong off = 0, _max##off = (img).size(); off<_max##off; ++off)
#define cimg_rofoff(img,off) for (cimg_long off = (cimg_long)((img).size() - 1); off>=0; --off)

#define cimg_for1(bound,i) for (int i = 0; i<(int)(bound); ++i)
#define cimg_forX(img,x) cimg_for1((img)._width,x)
#define cimg_forY(img,y) cimg_for1((img)._height,y)
#define cimg_forZ(img,z) cimg_for1((img)._depth,z)
#define cimg_forC(img,c) cimg_for1((img)._spectrum,c)
#define cimg_forXY(img,x,y) cimg_forY(img,y) cimg_forX(img,x)
#define cimg_forXZ(img,x,z) cimg_forZ(img,z) cimg_forX(img,x)
#define cimg_forYZ(img,y,z) cimg_forZ(img,z) cimg_forY(img,y)
#define cimg_forXC(img,x,c) cimg_forC(img,c) cimg_forX(img,x)
#define cimg_forYC(img,y,c) cimg_forC(img,c) cimg_forY(img,y)
#define cimg_forZC(img,z,c) cimg_forC(img,c) cimg_forZ(img,z)
#define cimg_forXYZ(img,x,y,z) cimg_forZ(img,z) cimg_forXY(img,x,y)
#define cimg_forXYC(img,x,y,c) cimg_forC(img,c) cimg_forXY(img,x,y)
#define cimg_forXZC(img,x,z,c) cimg_forC(img,c) cimg_forXZ(img,x,z)
#define cimg_forYZC(img,y,z,c) cimg_forC(img,c) cimg_forYZ(img,y,z)
#define cimg_forXYZC(img,x,y,z,c) cimg_forC(img,c) cimg_forXYZ(img,x,y,z)

#define cimg_rof1(bound,i) for (int i = (int)(bound) - 1; i>=0; --i)
#define cimg_rofX(img,x) cimg_rof1((img)._width,x)
#define cimg_rofY(img,y) cimg_rof1((img)._height,y)
#define cimg_rofZ(img,z) cimg_rof1((img)._depth,z)
#define cimg_rofC(img,c) cimg_rof1((img)._spectrum,c)
#define cimg_rofXY(img,x,y) cimg_rofY(img,y) cimg_rofX(img,x)
#define cimg_rofXZ(img,x,z) cimg_rofZ(img,z) cimg_rofX(img,x)
#define cimg_rofYZ(img,y,z) cimg_rofZ(img,z) cimg_rofY(img,y)
#define cimg_rofXC(img,x,c) cimg_rofC(img,c) cimg_rofX(img,x)
#define cimg_rofYC(img,y,c) cimg_rofC(img,c) cimg_rofY(img,y)
#define cimg_rofZC(img,z,c) cimg_rofC(img,c) cimg_rofZ(img,z)
#define cimg_rofXYZ(img,x,y,z) cimg_rofZ(img,z) cimg_rofXY(img,x,y)
#define cimg_rofXYC(img,x,y,c) cimg_rofC(img,c) cimg_rofXY(img,x,y)
#define cimg_rofXZC(img,x,z,c) cimg_rofC(img,c) cimg_rofXZ(img,x,z)
#define cimg_rofYZC(img,y,z,c) cimg_rofC(img,c) cimg_rofYZ(img,y,z)
#define cimg_rofXYZC(img,x,y,z,c) cimg_rofC(img,c) cimg_rofXYZ(img,x,y,z)

#define cimg_for_in1(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), _max##i = (int)(i1)<(int)(bound)?(int)(i1):(int)(bound) - 1; i<=_max##i; ++i)
#define cimg_for_inX(img,x0,x1,x) cimg_for_in1((img)._width,x0,x1,x)
#define cimg_for_inY(img,y0,y1,y) cimg_for_in1((img)._height,y0,y1,y)
#define cimg_for_inZ(img,z0,z1,z) cimg_for_in1((img)._depth,z0,z1,z)
#define cimg_for_inC(img,c0,c1,c) cimg_for_in1((img)._spectrum,c0,c1,c)
#define cimg_for_inXY(img,x0,y0,x1,y1,x,y) cimg_for_inY(img,y0,y1,y) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inXZ(img,x0,z0,x1,z1,x,z) cimg_for_inZ(img,z0,z1,z) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inXC(img,x0,c0,x1,c1,x,c) cimg_for_inC(img,c0,c1,c) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inYZ(img,y0,z0,y1,z1,y,z) cimg_for_inZ(img,x0,z1,z) cimg_for_inY(img,y0,y1,y)
#define cimg_for_inYC(img,y0,c0,y1,c1,y,c) cimg_for_inC(img,c0,c1,c) cimg_for_inY(img,y0,y1,y)
#define cimg_for_inZC(img,z0,c0,z1,c1,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inZ(img,z0,z1,z)
#define cimg_for_inXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_inZ(img,z0,z1,z) cimg_for_inXY(img,x0,y0,x1,y1,x,y)
#define cimg_for_inXYC(img,x0,y0,c0,x1,y1,c1,x,y,c) cimg_for_inC(img,c0,c1,c) cimg_for_inXY(img,x0,y0,x1,y1,x,y)
#define cimg_for_inXZC(img,x0,z0,c0,x1,z1,c1,x,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inXZ(img,x0,z0,x1,z1,x,z)
#define cimg_for_inYZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inYZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_inXYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_inC(img,c0,c1,c) cimg_for_inXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)
#define cimg_for_insideX(img,x,n) cimg_for_inX(img,n,(img)._width - 1 - (n),x)
#define cimg_for_insideY(img,y,n) cimg_for_inY(img,n,(img)._height - 1 - (n),y)
#define cimg_for_insideZ(img,z,n) cimg_for_inZ(img,n,(img)._depth  - 1 - (n),z)
#define cimg_for_insideC(img,c,n) cimg_for_inC(img,n,(img)._spectrum - 1 - (n),c)
#define cimg_for_insideXY(img,x,y,n) cimg_for_inXY(img,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),x,y)
#define cimg_for_insideXYZ(img,x,y,z,n) \
  cimg_for_inXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)
#define cimg_for_insideXYZC(img,x,y,z,c,n) \
  cimg_for_inXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)

#define cimg_for_out1(boundi,i0,i1,i) \
 for (int i = (int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); ++i, i = i==(int)(i0)?(int)(i1) + 1:i)
#define cimg_for_out2(boundi,boundj,i0,j0,i1,j1,i,j) \
 for (int j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j?0:(int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); \
  ++i, i = _n1j?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_out3(boundi,boundj,boundk,i0,j0,k0,i1,j1,k1,i,j,k) \
 for (int k = 0; k<(int)(boundk); ++k) \
 for (int _n1k = (int)(k<(int)(k0) || k>(int)(k1)), j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j || _n1k?0:(int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); \
  ++i, i = _n1j || _n1k?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_out4(boundi,boundj,boundk,boundl,i0,j0,k0,l0,i1,j1,k1,l1,i,j,k,l) \
 for (int l = 0; l<(int)(boundl); ++l) \
 for (int _n1l = (int)(l<(int)(l0) || l>(int)(l1)), k = 0; k<(int)(boundk); ++k) \
 for (int _n1k = (int)(k<(int)(k0) || k>(int)(k1)), j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j || _n1k || _n1l?0:(int)(i0)>0?0:(int)(i1) + 1; \
  i<(int)(boundi); ++i, i = _n1j || _n1k || _n1l?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_outX(img,x0,x1,x) cimg_for_out1((img)._width,x0,x1,x)
#define cimg_for_outY(img,y0,y1,y) cimg_for_out1((img)._height,y0,y1,y)
#define cimg_for_outZ(img,z0,z1,z) cimg_for_out1((img)._depth,z0,z1,z)
#define cimg_for_outC(img,c0,c1,c) cimg_for_out1((img)._spectrum,c0,c1,c)
#define cimg_for_outXY(img,x0,y0,x1,y1,x,y) cimg_for_out2((img)._width,(img)._height,x0,y0,x1,y1,x,y)
#define cimg_for_outXZ(img,x0,z0,x1,z1,x,z) cimg_for_out2((img)._width,(img)._depth,x0,z0,x1,z1,x,z)
#define cimg_for_outXC(img,x0,c0,x1,c1,x,c) cimg_for_out2((img)._width,(img)._spectrum,x0,c0,x1,c1,x,c)
#define cimg_for_outYZ(img,y0,z0,y1,z1,y,z) cimg_for_out2((img)._height,(img)._depth,y0,z0,y1,z1,y,z)
#define cimg_for_outYC(img,y0,c0,y1,c1,y,c) cimg_for_out2((img)._height,(img)._spectrum,y0,c0,y1,c1,y,c)
#define cimg_for_outZC(img,z0,c0,z1,c1,z,c) cimg_for_out2((img)._depth,(img)._spectrum,z0,c0,z1,c1,z,c)
#define cimg_for_outXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) \
  cimg_for_out3((img)._width,(img)._height,(img)._depth,x0,y0,z0,x1,y1,z1,x,y,z)
#define cimg_for_outXYC(img,x0,y0,c0,x1,y1,c1,x,y,c) \
  cimg_for_out3((img)._width,(img)._height,(img)._spectrum,x0,y0,c0,x1,y1,c1,x,y,c)
#define cimg_for_outXZC(img,x0,z0,c0,x1,z1,c1,x,z,c) \
  cimg_for_out3((img)._width,(img)._depth,(img)._spectrum,x0,z0,c0,x1,z1,c1,x,z,c)
#define cimg_for_outYZC(img,y0,z0,c0,y1,z1,c1,y,z,c) \
  cimg_for_out3((img)._height,(img)._depth,(img)._spectrum,y0,z0,c0,y1,z1,c1,y,z,c)
#define cimg_for_outXYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
 cimg_for_out4((img)._width,(img)._height,(img)._depth,(img)._spectrum,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c)
#define cimg_for_borderX(img,x,n) cimg_for_outX(img,n,(img)._width - 1 - (n),x)
#define cimg_for_borderY(img,y,n) cimg_for_outY(img,n,(img)._height - 1 - (n),y)
#define cimg_for_borderZ(img,z,n) cimg_for_outZ(img,n,(img)._depth - 1 - (n),z)
#define cimg_for_borderC(img,c,n) cimg_for_outC(img,n,(img)._spectrum - 1 - (n),c)
#define cimg_for_borderXY(img,x,y,n) cimg_for_outXY(img,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),x,y)
#define cimg_for_borderXYZ(img,x,y,z,n) \
  cimg_for_outXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)
#define cimg_for_borderXYZC(img,x,y,z,c,n) \
 cimg_for_outXYZC(img,n,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n), \
                  (img)._depth - 1 - (n),(img)._spectrum - 1 - (n),x,y,z,c)

#define cimg_for_spiralXY(img,x,y) \
 for (int x = 0, y = 0, _n1##x = 1, _n1##y = (img).width()*(img).height(); _n1##y; \
      --_n1##y, _n1##x+=(_n1##x>>2) - ((!(_n1##x&3)?--y:((_n1##x&3)==1?(img)._width - 1 - ++x:\
      ((_n1##x&3)==2?(img)._height - 1 - ++y:--x))))?0:1)

#define cimg_for_lineXY(x,y,x0,y0,x1,y1) \
 for (int x = (int)(x0), y = (int)(y0), _sx = 1, _sy = 1, _steep = 0, \
      _dx=(x1)>(x0)?(int)(x1) - (int)(x0):(_sx=-1,(int)(x0) - (int)(x1)), \
      _dy=(y1)>(y0)?(int)(y1) - (int)(y0):(_sy=-1,(int)(y0) - (int)(y1)), \
      _counter = _dx, \
      _err = _dx>_dy?(_dy>>1):((_steep=1),(_counter=_dy),(_dx>>1)); \
      _counter>=0; \
      --_counter, x+=_steep? \
      (y+=_sy,(_err-=_dx)<0?_err+=_dy,_sx:0): \
      (y+=(_err-=_dy)<0?_err+=_dx,_sy:0,_sx))

#define cimg_for2(bound,i) \
 for (int i = 0, _n1##i = 1>=(bound)?(int)(bound) - 1:1; \
      _n1##i<(int)(bound) || i==--_n1##i; \
      ++i, ++_n1##i)
#define cimg_for2X(img,x) cimg_for2((img)._width,x)
#define cimg_for2Y(img,y) cimg_for2((img)._height,y)
#define cimg_for2Z(img,z) cimg_for2((img)._depth,z)
#define cimg_for2C(img,c) cimg_for2((img)._spectrum,c)
#define cimg_for2XY(img,x,y) cimg_for2Y(img,y) cimg_for2X(img,x)
#define cimg_for2XZ(img,x,z) cimg_for2Z(img,z) cimg_for2X(img,x)
#define cimg_for2XC(img,x,c) cimg_for2C(img,c) cimg_for2X(img,x)
#define cimg_for2YZ(img,y,z) cimg_for2Z(img,z) cimg_for2Y(img,y)
#define cimg_for2YC(img,y,c) cimg_for2C(img,c) cimg_for2Y(img,y)
#define cimg_for2ZC(img,z,c) cimg_for2C(img,c) cimg_for2Z(img,z)
#define cimg_for2XYZ(img,x,y,z) cimg_for2Z(img,z) cimg_for2XY(img,x,y)
#define cimg_for2XZC(img,x,z,c) cimg_for2C(img,c) cimg_for2XZ(img,x,z)
#define cimg_for2YZC(img,y,z,c) cimg_for2C(img,c) cimg_for2YZ(img,y,z)
#define cimg_for2XYZC(img,x,y,z,c) cimg_for2C(img,c) cimg_for2XYZ(img,x,y,z)

#define cimg_for_in2(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1; \
      i<=(int)(i1) && (_n1##i<(int)(bound) || i==--_n1##i); \
      ++i, ++_n1##i)
#define cimg_for_in2X(img,x0,x1,x) cimg_for_in2((img)._width,x0,x1,x)
#define cimg_for_in2Y(img,y0,y1,y) cimg_for_in2((img)._height,y0,y1,y)
#define cimg_for_in2Z(img,z0,z1,z) cimg_for_in2((img)._depth,z0,z1,z)
#define cimg_for_in2C(img,c0,c1,c) cimg_for_in2((img)._spectrum,c0,c1,c)
#define cimg_for_in2XY(img,x0,y0,x1,y1,x,y) cimg_for_in2Y(img,y0,y1,y) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2XZ(img,x0,z0,x1,z1,x,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2XC(img,x0,c0,x1,c1,x,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2YZ(img,y0,z0,y1,z1,y,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2Y(img,y0,y1,y)
#define cimg_for_in2YC(img,y0,c0,y1,c1,y,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2Y(img,y0,y1,y)
#define cimg_for_in2ZC(img,z0,c0,z1,c1,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2Z(img,z0,z1,z)
#define cimg_for_in2XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in2XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in2YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in2XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in2C(img,c0,c1,c) cimg_for_in2XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for3(bound,i) \
 for (int i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1; \
      _n1##i<(int)(bound) || i==--_n1##i; \
      _p1##i = i++, ++_n1##i)
#define cimg_for3X(img,x) cimg_for3((img)._width,x)
#define cimg_for3Y(img,y) cimg_for3((img)._height,y)
#define cimg_for3Z(img,z) cimg_for3((img)._depth,z)
#define cimg_for3C(img,c) cimg_for3((img)._spectrum,c)
#define cimg_for3XY(img,x,y) cimg_for3Y(img,y) cimg_for3X(img,x)
#define cimg_for3XZ(img,x,z) cimg_for3Z(img,z) cimg_for3X(img,x)
#define cimg_for3XC(img,x,c) cimg_for3C(img,c) cimg_for3X(img,x)
#define cimg_for3YZ(img,y,z) cimg_for3Z(img,z) cimg_for3Y(img,y)
#define cimg_for3YC(img,y,c) cimg_for3C(img,c) cimg_for3Y(img,y)
#define cimg_for3ZC(img,z,c) cimg_for3C(img,c) cimg_for3Z(img,z)
#define cimg_for3XYZ(img,x,y,z) cimg_for3Z(img,z) cimg_for3XY(img,x,y)
#define cimg_for3XZC(img,x,z,c) cimg_for3C(img,c) cimg_for3XZ(img,x,z)
#define cimg_for3YZC(img,y,z,c) cimg_for3C(img,c) cimg_for3YZ(img,y,z)
#define cimg_for3XYZC(img,x,y,z,c) cimg_for3C(img,c) cimg_for3XYZ(img,x,y,z)

#define cimg_for_in3(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1; \
      i<=(int)(i1) && (_n1##i<(int)(bound) || i==--_n1##i); \
      _p1##i = i++, ++_n1##i)
#define cimg_for_in3X(img,x0,x1,x) cimg_for_in3((img)._width,x0,x1,x)
#define cimg_for_in3Y(img,y0,y1,y) cimg_for_in3((img)._height,y0,y1,y)
#define cimg_for_in3Z(img,z0,z1,z) cimg_for_in3((img)._depth,z0,z1,z)
#define cimg_for_in3C(img,c0,c1,c) cimg_for_in3((img)._spectrum,c0,c1,c)
#define cimg_for_in3XY(img,x0,y0,x1,y1,x,y) cimg_for_in3Y(img,y0,y1,y) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3XZ(img,x0,z0,x1,z1,x,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3XC(img,x0,c0,x1,c1,x,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3YZ(img,y0,z0,y1,z1,y,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3Y(img,y0,y1,y)
#define cimg_for_in3YC(img,y0,c0,y1,c1,y,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3Y(img,y0,y1,y)
#define cimg_for_in3ZC(img,z0,c0,z1,c1,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3Z(img,z0,z1,z)
#define cimg_for_in3XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in3XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in3YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in3XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in3C(img,c0,c1,c) cimg_for_in3XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for4(bound,i) \
 for (int i = 0, _p1##i = 0, _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2; \
      _n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i); \
      _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for4X(img,x) cimg_for4((img)._width,x)
#define cimg_for4Y(img,y) cimg_for4((img)._height,y)
#define cimg_for4Z(img,z) cimg_for4((img)._depth,z)
#define cimg_for4C(img,c) cimg_for4((img)._spectrum,c)
#define cimg_for4XY(img,x,y) cimg_for4Y(img,y) cimg_for4X(img,x)
#define cimg_for4XZ(img,x,z) cimg_for4Z(img,z) cimg_for4X(img,x)
#define cimg_for4XC(img,x,c) cimg_for4C(img,c) cimg_for4X(img,x)
#define cimg_for4YZ(img,y,z) cimg_for4Z(img,z) cimg_for4Y(img,y)
#define cimg_for4YC(img,y,c) cimg_for4C(img,c) cimg_for4Y(img,y)
#define cimg_for4ZC(img,z,c) cimg_for4C(img,c) cimg_for4Z(img,z)
#define cimg_for4XYZ(img,x,y,z) cimg_for4Z(img,z) cimg_for4XY(img,x,y)
#define cimg_for4XZC(img,x,z,c) cimg_for4C(img,c) cimg_for4XZ(img,x,z)
#define cimg_for4YZC(img,y,z,c) cimg_for4C(img,c) cimg_for4YZ(img,y,z)
#define cimg_for4XYZC(img,x,y,z,c) cimg_for4C(img,c) cimg_for4XYZ(img,x,y,z)

#define cimg_for_in4(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2; \
      i<=(int)(i1) && (_n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i)); \
      _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for_in4X(img,x0,x1,x) cimg_for_in4((img)._width,x0,x1,x)
#define cimg_for_in4Y(img,y0,y1,y) cimg_for_in4((img)._height,y0,y1,y)
#define cimg_for_in4Z(img,z0,z1,z) cimg_for_in4((img)._depth,z0,z1,z)
#define cimg_for_in4C(img,c0,c1,c) cimg_for_in4((img)._spectrum,c0,c1,c)
#define cimg_for_in4XY(img,x0,y0,x1,y1,x,y) cimg_for_in4Y(img,y0,y1,y) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4XZ(img,x0,z0,x1,z1,x,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4XC(img,x0,c0,x1,c1,x,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4YZ(img,y0,z0,y1,z1,y,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4Y(img,y0,y1,y)
#define cimg_for_in4YC(img,y0,c0,y1,c1,y,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4Y(img,y0,y1,y)
#define cimg_for_in4ZC(img,z0,c0,z1,c1,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4Z(img,z0,z1,z)
#define cimg_for_in4XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in4XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in4YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in4XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in4C(img,c0,c1,c) cimg_for_in4XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for5(bound,i) \
 for (int i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2; \
      _n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for5X(img,x) cimg_for5((img)._width,x)
#define cimg_for5Y(img,y) cimg_for5((img)._height,y)
#define cimg_for5Z(img,z) cimg_for5((img)._depth,z)
#define cimg_for5C(img,c) cimg_for5((img)._spectrum,c)
#define cimg_for5XY(img,x,y) cimg_for5Y(img,y) cimg_for5X(img,x)
#define cimg_for5XZ(img,x,z) cimg_for5Z(img,z) cimg_for5X(img,x)
#define cimg_for5XC(img,x,c) cimg_for5C(img,c) cimg_for5X(img,x)
#define cimg_for5YZ(img,y,z) cimg_for5Z(img,z) cimg_for5Y(img,y)
#define cimg_for5YC(img,y,c) cimg_for5C(img,c) cimg_for5Y(img,y)
#define cimg_for5ZC(img,z,c) cimg_for5C(img,c) cimg_for5Z(img,z)
#define cimg_for5XYZ(img,x,y,z) cimg_for5Z(img,z) cimg_for5XY(img,x,y)
#define cimg_for5XZC(img,x,z,c) cimg_for5C(img,c) cimg_for5XZ(img,x,z)
#define cimg_for5YZC(img,y,z,c) cimg_for5C(img,c) cimg_for5YZ(img,y,z)
#define cimg_for5XYZC(img,x,y,z,c) cimg_for5C(img,c) cimg_for5XYZ(img,x,y,z)

#define cimg_for_in5(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2; \
      i<=(int)(i1) && (_n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i)); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for_in5X(img,x0,x1,x) cimg_for_in5((img)._width,x0,x1,x)
#define cimg_for_in5Y(img,y0,y1,y) cimg_for_in5((img)._height,y0,y1,y)
#define cimg_for_in5Z(img,z0,z1,z) cimg_for_in5((img)._depth,z0,z1,z)
#define cimg_for_in5C(img,c0,c1,c) cimg_for_in5((img)._spectrum,c0,c1,c)
#define cimg_for_in5XY(img,x0,y0,x1,y1,x,y) cimg_for_in5Y(img,y0,y1,y) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5XZ(img,x0,z0,x1,z1,x,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5XC(img,x0,c0,x1,c1,x,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5YZ(img,y0,z0,y1,z1,y,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5Y(img,y0,y1,y)
#define cimg_for_in5YC(img,y0,c0,y1,c1,y,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5Y(img,y0,y1,y)
#define cimg_for_in5ZC(img,z0,c0,z1,c1,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5Z(img,z0,z1,z)
#define cimg_for_in5XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in5XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in5YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in5XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in5C(img,c0,c1,c) cimg_for_in5XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for6(bound,i) \
 for (int i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3; \
      _n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for6X(img,x) cimg_for6((img)._width,x)
#define cimg_for6Y(img,y) cimg_for6((img)._height,y)
#define cimg_for6Z(img,z) cimg_for6((img)._depth,z)
#define cimg_for6C(img,c) cimg_for6((img)._spectrum,c)
#define cimg_for6XY(img,x,y) cimg_for6Y(img,y) cimg_for6X(img,x)
#define cimg_for6XZ(img,x,z) cimg_for6Z(img,z) cimg_for6X(img,x)
#define cimg_for6XC(img,x,c) cimg_for6C(img,c) cimg_for6X(img,x)
#define cimg_for6YZ(img,y,z) cimg_for6Z(img,z) cimg_for6Y(img,y)
#define cimg_for6YC(img,y,c) cimg_for6C(img,c) cimg_for6Y(img,y)
#define cimg_for6ZC(img,z,c) cimg_for6C(img,c) cimg_for6Z(img,z)
#define cimg_for6XYZ(img,x,y,z) cimg_for6Z(img,z) cimg_for6XY(img,x,y)
#define cimg_for6XZC(img,x,z,c) cimg_for6C(img,c) cimg_for6XZ(img,x,z)
#define cimg_for6YZC(img,y,z,c) cimg_for6C(img,c) cimg_for6YZ(img,y,z)
#define cimg_for6XYZC(img,x,y,z,c) cimg_for6C(img,c) cimg_for6XYZ(img,x,y,z)

#define cimg_for_in6(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3; \
      i<=(int)(i1) && \
      (_n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i)); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for_in6X(img,x0,x1,x) cimg_for_in6((img)._width,x0,x1,x)
#define cimg_for_in6Y(img,y0,y1,y) cimg_for_in6((img)._height,y0,y1,y)
#define cimg_for_in6Z(img,z0,z1,z) cimg_for_in6((img)._depth,z0,z1,z)
#define cimg_for_in6C(img,c0,c1,c) cimg_for_in6((img)._spectrum,c0,c1,c)
#define cimg_for_in6XY(img,x0,y0,x1,y1,x,y) cimg_for_in6Y(img,y0,y1,y) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6XZ(img,x0,z0,x1,z1,x,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6XC(img,x0,c0,x1,c1,x,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6YZ(img,y0,z0,y1,z1,y,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6Y(img,y0,y1,y)
#define cimg_for_in6YC(img,y0,c0,y1,c1,y,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6Y(img,y0,y1,y)
#define cimg_for_in6ZC(img,z0,c0,z1,c1,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6Z(img,z0,z1,z)
#define cimg_for_in6XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in6XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in6YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in6XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in6C(img,c0,c1,c) cimg_for_in6XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for7(bound,i) \
 for (int i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3; \
      _n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for7X(img,x) cimg_for7((img)._width,x)
#define cimg_for7Y(img,y) cimg_for7((img)._height,y)
#define cimg_for7Z(img,z) cimg_for7((img)._depth,z)
#define cimg_for7C(img,c) cimg_for7((img)._spectrum,c)
#define cimg_for7XY(img,x,y) cimg_for7Y(img,y) cimg_for7X(img,x)
#define cimg_for7XZ(img,x,z) cimg_for7Z(img,z) cimg_for7X(img,x)
#define cimg_for7XC(img,x,c) cimg_for7C(img,c) cimg_for7X(img,x)
#define cimg_for7YZ(img,y,z) cimg_for7Z(img,z) cimg_for7Y(img,y)
#define cimg_for7YC(img,y,c) cimg_for7C(img,c) cimg_for7Y(img,y)
#define cimg_for7ZC(img,z,c) cimg_for7C(img,c) cimg_for7Z(img,z)
#define cimg_for7XYZ(img,x,y,z) cimg_for7Z(img,z) cimg_for7XY(img,x,y)
#define cimg_for7XZC(img,x,z,c) cimg_for7C(img,c) cimg_for7XZ(img,x,z)
#define cimg_for7YZC(img,y,z,c) cimg_for7C(img,c) cimg_for7YZ(img,y,z)
#define cimg_for7XYZC(img,x,y,z,c) cimg_for7C(img,c) cimg_for7XYZ(img,x,y,z)

#define cimg_for_in7(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p3##i = i - 3<0?0:i - 3, \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3; \
      i<=(int)(i1) && \
      (_n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i)); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for_in7X(img,x0,x1,x) cimg_for_in7((img)._width,x0,x1,x)
#define cimg_for_in7Y(img,y0,y1,y) cimg_for_in7((img)._height,y0,y1,y)
#define cimg_for_in7Z(img,z0,z1,z) cimg_for_in7((img)._depth,z0,z1,z)
#define cimg_for_in7C(img,c0,c1,c) cimg_for_in7((img)._spectrum,c0,c1,c)
#define cimg_for_in7XY(img,x0,y0,x1,y1,x,y) cimg_for_in7Y(img,y0,y1,y) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7XZ(img,x0,z0,x1,z1,x,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7XC(img,x0,c0,x1,c1,x,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7YZ(img,y0,z0,y1,z1,y,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7Y(img,y0,y1,y)
#define cimg_for_in7YC(img,y0,c0,y1,c1,y,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7Y(img,y0,y1,y)
#define cimg_for_in7ZC(img,z0,c0,z1,c1,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7Z(img,z0,z1,z)
#define cimg_for_in7XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in7XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in7YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in7XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in7C(img,c0,c1,c) cimg_for_in7XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for8(bound,i) \
 for (int i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3, \
      _n4##i = 4>=(bound)?(int)(bound) - 1:4; \
      _n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
      i==(_n4##i = _n3##i = _n2##i = --_n1##i); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for8X(img,x) cimg_for8((img)._width,x)
#define cimg_for8Y(img,y) cimg_for8((img)._height,y)
#define cimg_for8Z(img,z) cimg_for8((img)._depth,z)
#define cimg_for8C(img,c) cimg_for8((img)._spectrum,c)
#define cimg_for8XY(img,x,y) cimg_for8Y(img,y) cimg_for8X(img,x)
#define cimg_for8XZ(img,x,z) cimg_for8Z(img,z) cimg_for8X(img,x)
#define cimg_for8XC(img,x,c) cimg_for8C(img,c) cimg_for8X(img,x)
#define cimg_for8YZ(img,y,z) cimg_for8Z(img,z) cimg_for8Y(img,y)
#define cimg_for8YC(img,y,c) cimg_for8C(img,c) cimg_for8Y(img,y)
#define cimg_for8ZC(img,z,c) cimg_for8C(img,c) cimg_for8Z(img,z)
#define cimg_for8XYZ(img,x,y,z) cimg_for8Z(img,z) cimg_for8XY(img,x,y)
#define cimg_for8XZC(img,x,z,c) cimg_for8C(img,c) cimg_for8XZ(img,x,z)
#define cimg_for8YZC(img,y,z,c) cimg_for8C(img,c) cimg_for8YZ(img,y,z)
#define cimg_for8XYZC(img,x,y,z,c) cimg_for8C(img,c) cimg_for8XYZ(img,x,y,z)

#define cimg_for_in8(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p3##i = i - 3<0?0:i - 3, \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3, \
      _n4##i = i + 4>=(int)(bound)?(int)(bound) - 1:i + 4; \
      i<=(int)(i1) && (_n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
      i==(_n4##i = _n3##i = _n2##i = --_n1##i)); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for_in8X(img,x0,x1,x) cimg_for_in8((img)._width,x0,x1,x)
#define cimg_for_in8Y(img,y0,y1,y) cimg_for_in8((img)._height,y0,y1,y)
#define cimg_for_in8Z(img,z0,z1,z) cimg_for_in8((img)._depth,z0,z1,z)
#define cimg_for_in8C(img,c0,c1,c) cimg_for_in8((img)._spectrum,c0,c1,c)
#define cimg_for_in8XY(img,x0,y0,x1,y1,x,y) cimg_for_in8Y(img,y0,y1,y) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8XZ(img,x0,z0,x1,z1,x,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8XC(img,x0,c0,x1,c1,x,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8YZ(img,y0,z0,y1,z1,y,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8Y(img,y0,y1,y)
#define cimg_for_in8YC(img,y0,c0,y1,c1,y,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8Y(img,y0,y1,y)
#define cimg_for_in8ZC(img,z0,c0,z1,c1,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8Z(img,z0,z1,z)
#define cimg_for_in8XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in8XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in8YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in8XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in8C(img,c0,c1,c) cimg_for_in8XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for9(bound,i) \
  for (int i = 0, _p4##i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
       _n1##i = 1>=(int)(bound)?(int)(bound) - 1:1, \
       _n2##i = 2>=(int)(bound)?(int)(bound) - 1:2, \
       _n3##i = 3>=(int)(bound)?(int)(bound) - 1:3, \
       _n4##i = 4>=(int)(bound)?(int)(bound) - 1:4; \
       _n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
       i==(_n4##i = _n3##i = _n2##i = --_n1##i); \
       _p4##i = _p3##i, _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for9X(img,x) cimg_for9((img)._width,x)
#define cimg_for9Y(img,y) cimg_for9((img)._height,y)
#define cimg_for9Z(img,z) cimg_for9((img)._depth,z)
#define cimg_for9C(img,c) cimg_for9((img)._spectrum,c)
#define cimg_for9XY(img,x,y) cimg_for9Y(img,y) cimg_for9X(img,x)
#define cimg_for9XZ(img,x,z) cimg_for9Z(img,z) cimg_for9X(img,x)
#define cimg_for9XC(img,x,c) cimg_for9C(img,c) cimg_for9X(img,x)
#define cimg_for9YZ(img,y,z) cimg_for9Z(img,z) cimg_for9Y(img,y)
#define cimg_for9YC(img,y,c) cimg_for9C(img,c) cimg_for9Y(img,y)
#define cimg_for9ZC(img,z,c) cimg_for9C(img,c) cimg_for9Z(img,z)
#define cimg_for9XYZ(img,x,y,z) cimg_for9Z(img,z) cimg_for9XY(img,x,y)
#define cimg_for9XZC(img,x,z,c) cimg_for9C(img,c) cimg_for9XZ(img,x,z)
#define cimg_for9YZC(img,y,z,c) cimg_for9C(img,c) cimg_for9YZ(img,y,z)
#define cimg_for9XYZC(img,x,y,z,c) cimg_for9C(img,c) cimg_for9XYZ(img,x,y,z)

#define cimg_for_in9(bound,i0,i1,i) \
  for (int i = (int)(i0)<0?0:(int)(i0), \
       _p4##i = i - 4<0?0:i - 4, \
       _p3##i = i - 3<0?0:i - 3, \
       _p2##i = i - 2<0?0:i - 2, \
       _p1##i = i - 1<0?0:i - 1, \
       _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
       _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
       _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3, \
       _n4##i = i + 4>=(int)(bound)?(int)(bound) - 1:i + 4; \
       i<=(int)(i1) && (_n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
       i==(_n4##i = _n3##i = _n2##i = --_n1##i)); \
       _p4##i = _p3##i, _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for_in9X(img,x0,x1,x) cimg_for_in9((img)._width,x0,x1,x)
#define cimg_for_in9Y(img,y0,y1,y) cimg_for_in9((img)._height,y0,y1,y)
#define cimg_for_in9Z(img,z0,z1,z) cimg_for_in9((img)._depth,z0,z1,z)
#define cimg_for_in9C(img,c0,c1,c) cimg_for_in9((img)._spectrum,c0,c1,c)
#define cimg_for_in9XY(img,x0,y0,x1,y1,x,y) cimg_for_in9Y(img,y0,y1,y) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9XZ(img,x0,z0,x1,z1,x,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9XC(img,x0,c0,x1,c1,x,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9YZ(img,y0,z0,y1,z1,y,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9Y(img,y0,y1,y)
#define cimg_for_in9YC(img,y0,c0,y1,c1,y,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9Y(img,y0,y1,y)
#define cimg_for_in9ZC(img,z0,c0,z1,c1,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9Z(img,z0,z1,z)
#define cimg_for_in9XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in9XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in9YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in9XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in9C(img,c0,c1,c) cimg_for_in9XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for2x2(img,x,y,z,c,I,T) \
  cimg_for2((img)._height,y) for (int x = 0, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(0,y,z,c)), \
   (I[2] = (T)(img)(0,_n1##y,z,c)), \
   1>=(img)._width?(img).width() - 1:1);  \
   (_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], \
   I[2] = I[3], \
   ++x, ++_n1##x)

#define cimg_for_in2x2(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in2((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _n1##x = (int)( \
   (I[0] = (T)(img)(x,y,z,c)), \
   (I[2] = (T)(img)(x,_n1##y,z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && (  \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], \
   I[2] = I[3], \
   ++x, ++_n1##x)

#define cimg_for3x3(img,x,y,z,c,I,T) \
  cimg_for3((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[3] = I[4] = (T)(img)(0,y,z,c)), \
   (I[6] = I[7] = (T)(img)(0,_n1##y,z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[1] = I[2], \
   I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], \
   _p1##x = x++, ++_n1##x)

#define cimg_for_in3x3(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in3((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[3] = (T)(img)(_p1##x,y,z,c)), \
   (I[6] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[1] = (T)(img)(x,_p1##y,z,c)), \
   (I[4] = (T)(img)(x,y,z,c)), \
   (I[7] = (T)(img)(x,_n1##y,z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x);	    \
   I[0] = I[1], I[1] = I[2], \
   I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], \
   _p1##x = x++, ++_n1##x)

#define cimg_for4x4(img,x,y,z,c,I,T) \
  cimg_for4((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[4] = I[5] = (T)(img)(0,y,z,c)), \
   (I[8] = I[9] = (T)(img)(0,_n1##y,z,c)), \
   (I[12] = I[13] = (T)(img)(0,_n2##y,z,c)), \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[6] = (T)(img)(_n1##x,y,z,c)), \
   (I[10] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_n2##y,z,c)), \
   2>=(img)._width?(img).width() - 1:2); \
   (_n2##x<(img).width() && ( \
   (I[3] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[7] = (T)(img)(_n2##x,y,z,c)), \
   (I[11] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], \
   I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for_in4x4(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in4((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[4] = (T)(img)(_p1##x,y,z,c)), \
   (I[8] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[1] = (T)(img)(x,_p1##y,z,c)), \
   (I[5] = (T)(img)(x,y,z,c)), \
   (I[9] = (T)(img)(x,_n1##y,z,c)), \
   (I[13] = (T)(img)(x,_n2##y,z,c)), \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[6] = (T)(img)(_n1##x,y,z,c)), \
   (I[10] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_n2##y,z,c)), \
   x + 2>=(int)(img)._width?(img).width() - 1:x + 2); \
   x<=(int)(x1) && ((_n2##x<(img).width() && ( \
   (I[3] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[7] = (T)(img)(_n2##x,y,z,c)), \
   (I[11] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], \
   I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for5x5(img,x,y,z,c,I,T) \
 cimg_for5((img)._height,y) for (int x = 0, \
   _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = (int)( \
   (I[0] = I[1] = I[2] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[5] = I[6] = I[7] = (T)(img)(0,_p1##y,z,c)), \
   (I[10] = I[11] = I[12] = (T)(img)(0,y,z,c)), \
   (I[15] = I[16] = I[17] = (T)(img)(0,_n1##y,z,c)), \
   (I[20] = I[21] = I[22] = (T)(img)(0,_n2##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_n1##x,y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_n2##y,z,c)),  \
   2>=(img)._width?(img).width() - 1:2); \
   (_n2##x<(img).width() && ( \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n2##x,y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], \
   I[5] = I[6], I[6] = I[7], I[7] = I[8], I[8] = I[9], \
   I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], \
   I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], \
   I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for_in5x5(img,x0,y0,x1,y1,x,y,z,c,I,T) \
 cimg_for_in5((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = (int)( \
   (I[0] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[5] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[10] = (T)(img)(_p2##x,y,z,c)), \
   (I[15] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[1] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[6] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[11] = (T)(img)(_p1##x,y,z,c)), \
   (I[16] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[21] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[2] = (T)(img)(x,_p2##y,z,c)), \
   (I[7] = (T)(img)(x,_p1##y,z,c)), \
   (I[12] = (T)(img)(x,y,z,c)), \
   (I[17] = (T)(img)(x,_n1##y,z,c)), \
   (I[22] = (T)(img)(x,_n2##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_n1##x,y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_n2##y,z,c)), \
   x + 2>=(int)(img)._width?(img).width() - 1:x + 2); \
   x<=(int)(x1) && ((_n2##x<(img).width() && ( \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n2##x,y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], \
   I[5] = I[6], I[6] = I[7], I[7] = I[8], I[8] = I[9], \
   I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], \
   I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], \
   I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for6x6(img,x,y,z,c,I,T) \
 cimg_for6((img)._height,y) for (int x = 0, \
   _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = 2>=(img)._width?(img).width() - 1:2, \
   _n3##x = (int)( \
   (I[0] = I[1] = I[2] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[6] = I[7] = I[8] = (T)(img)(0,_p1##y,z,c)), \
   (I[12] = I[13] = I[14] = (T)(img)(0,y,z,c)), \
   (I[18] = I[19] = I[20] = (T)(img)(0,_n1##y,z,c)), \
   (I[24] = I[25] = I[26] = (T)(img)(0,_n2##y,z,c)), \
   (I[30] = I[31] = I[32] = (T)(img)(0,_n3##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[15] = (T)(img)(_n1##x,y,z,c)), \
   (I[21] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[27] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[33] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[10] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[16] = (T)(img)(_n2##x,y,z,c)), \
   (I[22] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[28] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[34] = (T)(img)(_n2##x,_n3##y,z,c)), \
   3>=(img)._width?(img).width() - 1:3); \
   (_n3##x<(img).width() && ( \
   (I[5] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[11] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[17] = (T)(img)(_n3##x,y,z,c)), \
   (I[23] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[29] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[35] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3## x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], \
   I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], I[34] = I[35], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for_in6x6(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in6((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)x0, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(int)(img)._width?(img).width() - 1:x + 2, \
   _n3##x = (int)( \
   (I[0] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[6] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[12] = (T)(img)(_p2##x,y,z,c)), \
   (I[18] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[30] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[1] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[7] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_p1##x,y,z,c)), \
   (I[19] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[25] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[31] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[2] = (T)(img)(x,_p2##y,z,c)), \
   (I[8] = (T)(img)(x,_p1##y,z,c)), \
   (I[14] = (T)(img)(x,y,z,c)), \
   (I[20] = (T)(img)(x,_n1##y,z,c)), \
   (I[26] = (T)(img)(x,_n2##y,z,c)), \
   (I[32] = (T)(img)(x,_n3##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[15] = (T)(img)(_n1##x,y,z,c)), \
   (I[21] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[27] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[33] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[10] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[16] = (T)(img)(_n2##x,y,z,c)), \
   (I[22] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[28] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[34] = (T)(img)(_n2##x,_n3##y,z,c)), \
   x + 3>=(int)(img)._width?(img).width() - 1:x + 3); \
   x<=(int)(x1) && ((_n3##x<(img).width() && ( \
   (I[5] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[11] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[17] = (T)(img)(_n3##x,y,z,c)), \
   (I[23] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[29] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[35] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3## x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], \
   I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], I[34] = I[35], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for7x7(img,x,y,z,c,I,T) \
  cimg_for7((img)._height,y) for (int x = 0, \
   _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = 2>=(img)._width?(img).width() - 1:2, \
   _n3##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[7] = I[8] = I[9] = I[10] = (T)(img)(0,_p2##y,z,c)), \
   (I[14] = I[15] = I[16] = I[17] = (T)(img)(0,_p1##y,z,c)), \
   (I[21] = I[22] = I[23] = I[24] = (T)(img)(0,y,z,c)), \
   (I[28] = I[29] = I[30] = I[31] = (T)(img)(0,_n1##y,z,c)), \
   (I[35] = I[36] = I[37] = I[38] = (T)(img)(0,_n2##y,z,c)), \
   (I[42] = I[43] = I[44] = I[45] = (T)(img)(0,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[11] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_n1##x,y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[39] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[46] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_n2##x,y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[47] = (T)(img)(_n2##x,_n3##y,z,c)), \
   3>=(img)._width?(img).width() - 1:3); \
   (_n3##x<(img).width() && ( \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[27] = (T)(img)(_n3##x,y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], \
   I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], \
   I[14] = I[15], I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], \
   I[21] = I[22], I[22] = I[23], I[23] = I[24], I[24] = I[25], I[25] = I[26], I[26] = I[27], \
   I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], \
   I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], I[40] = I[41], \
   I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for_in7x7(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in7((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(int)(img)._width?(img).width() - 1:x + 2, \
   _n3##x = (int)( \
   (I[0] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[7] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[14] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[21] = (T)(img)(_p3##x,y,z,c)), \
   (I[28] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[35] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[42] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[1] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[8] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[15] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[22] = (T)(img)(_p2##x,y,z,c)), \
   (I[29] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[36] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[43] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[2] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[9] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[16] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[23] = (T)(img)(_p1##x,y,z,c)), \
   (I[30] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[37] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[44] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[3] = (T)(img)(x,_p3##y,z,c)), \
   (I[10] = (T)(img)(x,_p2##y,z,c)), \
   (I[17] = (T)(img)(x,_p1##y,z,c)), \
   (I[24] = (T)(img)(x,y,z,c)), \
   (I[31] = (T)(img)(x,_n1##y,z,c)), \
   (I[38] = (T)(img)(x,_n2##y,z,c)), \
   (I[45] = (T)(img)(x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[11] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_n1##x,y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[39] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[46] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_n2##x,y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[47] = (T)(img)(_n2##x,_n3##y,z,c)), \
   x + 3>=(int)(img)._width?(img).width() - 1:x + 3); \
   x<=(int)(x1) && ((_n3##x<(img).width() && ( \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[27] = (T)(img)(_n3##x,y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], \
   I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], \
   I[14] = I[15], I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], \
   I[21] = I[22], I[22] = I[23], I[23] = I[24], I[24] = I[25], I[25] = I[26], I[26] = I[27], \
   I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], \
   I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], I[40] = I[41], \
   I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for8x8(img,x,y,z,c,I,T) \
  cimg_for8((img)._height,y) for (int x = 0, \
   _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=((img)._width)?(img).width() - 1:1, \
   _n2##x = 2>=((img)._width)?(img).width() - 1:2, \
   _n3##x = 3>=((img)._width)?(img).width() - 1:3, \
   _n4##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[8] = I[9] = I[10] = I[11] = (T)(img)(0,_p2##y,z,c)), \
   (I[16] = I[17] = I[18] = I[19] = (T)(img)(0,_p1##y,z,c)), \
   (I[24] = I[25] = I[26] = I[27] = (T)(img)(0,y,z,c)), \
   (I[32] = I[33] = I[34] = I[35] = (T)(img)(0,_n1##y,z,c)), \
   (I[40] = I[41] = I[42] = I[43] = (T)(img)(0,_n2##y,z,c)), \
   (I[48] = I[49] = I[50] = I[51] = (T)(img)(0,_n3##y,z,c)), \
   (I[56] = I[57] = I[58] = I[59] = (T)(img)(0,_n4##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[28] = (T)(img)(_n1##x,y,z,c)), \
   (I[36] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[44] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[52] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[60] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[21] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[29] = (T)(img)(_n2##x,y,z,c)), \
   (I[37] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[45] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[53] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[61] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[14] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[22] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[30] = (T)(img)(_n3##x,y,z,c)), \
   (I[38] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[46] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[54] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[62] = (T)(img)(_n3##x,_n4##y,z,c)), \
   4>=((img)._width)?(img).width() - 1:4); \
   (_n4##x<(img).width() && ( \
   (I[7] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[15] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[23] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[31] = (T)(img)(_n4##x,y,z,c)), \
   (I[39] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[47] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[55] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[63] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[53] = I[54], I[54] = I[55], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[62] = I[63], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for_in8x8(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in8((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(img).width()?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(img).width()?(img).width() - 1:x + 2, \
   _n3##x = x + 3>=(img).width()?(img).width() - 1:x + 3, \
   _n4##x = (int)( \
   (I[0] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[8] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[16] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[24] = (T)(img)(_p3##x,y,z,c)), \
   (I[32] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[56] = (T)(img)(_p3##x,_n4##y,z,c)), \
   (I[1] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[9] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[17] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_p2##x,y,z,c)), \
   (I[33] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[49] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[57] = (T)(img)(_p2##x,_n4##y,z,c)), \
   (I[2] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[10] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_p1##x,y,z,c)), \
   (I[34] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[42] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[50] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[58] = (T)(img)(_p1##x,_n4##y,z,c)), \
   (I[3] = (T)(img)(x,_p3##y,z,c)), \
   (I[11] = (T)(img)(x,_p2##y,z,c)), \
   (I[19] = (T)(img)(x,_p1##y,z,c)), \
   (I[27] = (T)(img)(x,y,z,c)), \
   (I[35] = (T)(img)(x,_n1##y,z,c)), \
   (I[43] = (T)(img)(x,_n2##y,z,c)), \
   (I[51] = (T)(img)(x,_n3##y,z,c)), \
   (I[59] = (T)(img)(x,_n4##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[28] = (T)(img)(_n1##x,y,z,c)), \
   (I[36] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[44] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[52] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[60] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[21] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[29] = (T)(img)(_n2##x,y,z,c)), \
   (I[37] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[45] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[53] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[61] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[14] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[22] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[30] = (T)(img)(_n3##x,y,z,c)), \
   (I[38] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[46] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[54] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[62] = (T)(img)(_n3##x,_n4##y,z,c)), \
   x + 4>=(img).width()?(img).width() - 1:x + 4); \
   x<=(int)(x1) && ((_n4##x<(img).width() && ( \
   (I[7] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[15] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[23] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[31] = (T)(img)(_n4##x,y,z,c)), \
   (I[39] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[47] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[55] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[63] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[53] = I[54], I[54] = I[55], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[62] = I[63], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for9x9(img,x,y,z,c,I,T) \
  cimg_for9((img)._height,y) for (int x = 0, \
   _p4##x = 0, _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=((img)._width)?(img).width() - 1:1, \
   _n2##x = 2>=((img)._width)?(img).width() - 1:2, \
   _n3##x = 3>=((img)._width)?(img).width() - 1:3, \
   _n4##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = I[4] = (T)(img)(_p4##x,_p4##y,z,c)), \
   (I[9] = I[10] = I[11] = I[12] = I[13] = (T)(img)(0,_p3##y,z,c)), \
   (I[18] = I[19] = I[20] = I[21] = I[22] = (T)(img)(0,_p2##y,z,c)), \
   (I[27] = I[28] = I[29] = I[30] = I[31] = (T)(img)(0,_p1##y,z,c)), \
   (I[36] = I[37] = I[38] = I[39] = I[40] = (T)(img)(0,y,z,c)), \
   (I[45] = I[46] = I[47] = I[48] = I[49] = (T)(img)(0,_n1##y,z,c)), \
   (I[54] = I[55] = I[56] = I[57] = I[58] = (T)(img)(0,_n2##y,z,c)), \
   (I[63] = I[64] = I[65] = I[66] = I[67] = (T)(img)(0,_n3##y,z,c)), \
   (I[72] = I[73] = I[74] = I[75] = I[76] = (T)(img)(0,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,_p4##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[41] = (T)(img)(_n1##x,y,z,c)), \
   (I[50] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[59] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[68] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[77] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n2##x,_p4##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[42] = (T)(img)(_n2##x,y,z,c)), \
   (I[51] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[60] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[69] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[78] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[7] = (T)(img)(_n3##x,_p4##y,z,c)), \
   (I[16] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[25] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[43] = (T)(img)(_n3##x,y,z,c)), \
   (I[52] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[61] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[70] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[79] = (T)(img)(_n3##x,_n4##y,z,c)), \
   4>=((img)._width)?(img).width() - 1:4); \
   (_n4##x<(img).width() && ( \
   (I[8] = (T)(img)(_n4##x,_p4##y,z,c)), \
   (I[17] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[26] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[35] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[44] = (T)(img)(_n4##x,y,z,c)), \
   (I[53] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[62] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[71] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[80] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], \
   I[16] = I[17], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   I[24] = I[25], I[25] = I[26], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[54] = I[55], I[55] = I[56], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[63] = I[64], \
   I[64] = I[65], I[65] = I[66], I[66] = I[67], I[67] = I[68], I[68] = I[69], I[69] = I[70], I[70] = I[71], \
   I[72] = I[73], I[73] = I[74], I[74] = I[75], I[75] = I[76], I[76] = I[77], I[77] = I[78], I[78] = I[79], \
   I[79] = I[80], \
   _p4##x = _p3##x, _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for_in9x9(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in9((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p4##x = x - 4<0?0:x - 4, \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(img).width()?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(img).width()?(img).width() - 1:x + 2, \
   _n3##x = x + 3>=(img).width()?(img).width() - 1:x + 3, \
   _n4##x = (int)( \
   (I[0] = (T)(img)(_p4##x,_p4##y,z,c)), \
   (I[9] = (T)(img)(_p4##x,_p3##y,z,c)), \
   (I[18] = (T)(img)(_p4##x,_p2##y,z,c)), \
   (I[27] = (T)(img)(_p4##x,_p1##y,z,c)), \
   (I[36] = (T)(img)(_p4##x,y,z,c)), \
   (I[45] = (T)(img)(_p4##x,_n1##y,z,c)), \
   (I[54] = (T)(img)(_p4##x,_n2##y,z,c)), \
   (I[63] = (T)(img)(_p4##x,_n3##y,z,c)), \
   (I[72] = (T)(img)(_p4##x,_n4##y,z,c)), \
   (I[1] = (T)(img)(_p3##x,_p4##y,z,c)), \
   (I[10] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[19] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[28] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[37] = (T)(img)(_p3##x,y,z,c)), \
   (I[46] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[55] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[64] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[73] = (T)(img)(_p3##x,_n4##y,z,c)), \
   (I[2] = (T)(img)(_p2##x,_p4##y,z,c)), \
   (I[11] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[20] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[29] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[38] = (T)(img)(_p2##x,y,z,c)), \
   (I[47] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[56] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[65] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[74] = (T)(img)(_p2##x,_n4##y,z,c)), \
   (I[3] = (T)(img)(_p1##x,_p4##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[21] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[30] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[39] = (T)(img)(_p1##x,y,z,c)), \
   (I[48] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[57] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[66] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[75] = (T)(img)(_p1##x,_n4##y,z,c)), \
   (I[4] = (T)(img)(x,_p4##y,z,c)), \
   (I[13] = (T)(img)(x,_p3##y,z,c)), \
   (I[22] = (T)(img)(x,_p2##y,z,c)), \
   (I[31] = (T)(img)(x,_p1##y,z,c)), \
   (I[40] = (T)(img)(x,y,z,c)), \
   (I[49] = (T)(img)(x,_n1##y,z,c)), \
   (I[58] = (T)(img)(x,_n2##y,z,c)), \
   (I[67] = (T)(img)(x,_n3##y,z,c)), \
   (I[76] = (T)(img)(x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,_p4##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[41] = (T)(img)(_n1##x,y,z,c)), \
   (I[50] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[59] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[68] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[77] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n2##x,_p4##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[42] = (T)(img)(_n2##x,y,z,c)), \
   (I[51] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[60] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[69] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[78] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[7] = (T)(img)(_n3##x,_p4##y,z,c)), \
   (I[16] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[25] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[43] = (T)(img)(_n3##x,y,z,c)), \
   (I[52] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[61] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[70] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[79] = (T)(img)(_n3##x,_n4##y,z,c)), \
   x + 4>=(img).width()?(img).width() - 1:x + 4); \
   x<=(int)(x1) && ((_n4##x<(img).width() && ( \
   (I[8] = (T)(img)(_n4##x,_p4##y,z,c)), \
   (I[17] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[26] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[35] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[44] = (T)(img)(_n4##x,y,z,c)), \
   (I[53] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[62] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[71] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[80] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], \
   I[16] = I[17], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   I[24] = I[25], I[25] = I[26], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[54] = I[55], I[55] = I[56], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[63] = I[64], \
   I[64] = I[65], I[65] = I[66], I[66] = I[67], I[67] = I[68], I[68] = I[69], I[69] = I[70], I[70] = I[71], \
   I[72] = I[73], I[73] = I[74], I[74] = I[75], I[75] = I[76], I[76] = I[77], I[77] = I[78], I[78] = I[79], \
   I[79] = I[80], \
   _p4##x = _p3##x, _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for2x2x2(img,x,y,z,c,I,T) \
 cimg_for2((img)._depth,z) cimg_for2((img)._height,y) for (int x = 0, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(0,y,z,c)), \
   (I[2] = (T)(img)(0,_n1##y,z,c)), \
   (I[4] = (T)(img)(0,y,_n1##z,c)), \
   (I[6] = (T)(img)(0,_n1##y,_n1##z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[2] = I[3], I[4] = I[5], I[6] = I[7], \
   ++x, ++_n1##x)

#define cimg_for_in2x2x2(img,x0,y0,z0,x1,y1,z1,x,y,z,c,I,T) \
 cimg_for_in2((img)._depth,z0,z1,z) cimg_for_in2((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _n1##x = (int)( \
   (I[0] = (T)(img)(x,y,z,c)), \
   (I[2] = (T)(img)(x,_n1##y,z,c)), \
   (I[4] = (T)(img)(x,y,_n1##z,c)), \
   (I[6] = (T)(img)(x,_n1##y,_n1##z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], I[2] = I[3], I[4] = I[5], I[6] = I[7], \
   ++x, ++_n1##x)

#define cimg_for3x3x3(img,x,y,z,c,I,T) \
 cimg_for3((img)._depth,z) cimg_for3((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,_p1##z,c)), \
   (I[3] = I[4] = (T)(img)(0,y,_p1##z,c)),  \
   (I[6] = I[7] = (T)(img)(0,_n1##y,_p1##z,c)), \
   (I[9] = I[10] = (T)(img)(0,_p1##y,z,c)), \
   (I[12] = I[13] = (T)(img)(0,y,z,c)), \
   (I[15] = I[16] = (T)(img)(0,_n1##y,z,c)), \
   (I[18] = I[19] = (T)(img)(0,_p1##y,_n1##z,c)), \
   (I[21] = I[22] = (T)(img)(0,y,_n1##z,c)), \
   (I[24] = I[25] = (T)(img)(0,_n1##y,_n1##z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_p1##z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c)), \
   (I[11] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,y,z,c)), \
   (I[17] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c)), \
   (I[23] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[1] = I[2], I[3] = I[4], I[4] = I[5], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[12] = I[13], I[13] = I[14], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[21] = I[22], I[22] = I[23], I[24] = I[25], I[25] = I[26], \
   _p1##x = x++, ++_n1##x)

#define cimg_for_in3x3x3(img,x0,y0,z0,x1,y1,z1,x,y,z,c,I,T) \
 cimg_for_in3((img)._depth,z0,z1,z) cimg_for_in3((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,_p1##z,c)), \
   (I[3] = (T)(img)(_p1##x,y,_p1##z,c)),  \
   (I[6] = (T)(img)(_p1##x,_n1##y,_p1##z,c)), \
   (I[9] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,y,z,c)), \
   (I[15] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[18] = (T)(img)(_p1##x,_p1##y,_n1##z,c)), \
   (I[21] = (T)(img)(_p1##x,y,_n1##z,c)), \
   (I[24] = (T)(img)(_p1##x,_n1##y,_n1##z,c)), \
   (I[1] = (T)(img)(x,_p1##y,_p1##z,c)), \
   (I[4] = (T)(img)(x,y,_p1##z,c)),  \
   (I[7] = (T)(img)(x,_n1##y,_p1##z,c)), \
   (I[10] = (T)(img)(x,_p1##y,z,c)), \
   (I[13] = (T)(img)(x,y,z,c)), \
   (I[16] = (T)(img)(x,_n1##y,z,c)), \
   (I[19] = (T)(img)(x,_p1##y,_n1##z,c)), \
   (I[22] = (T)(img)(x,y,_n1##z,c)), \
   (I[25] = (T)(img)(x,_n1##y,_n1##z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_p1##z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c)), \
   (I[11] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,y,z,c)), \
   (I[17] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c)), \
   (I[23] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], I[1] = I[2], I[3] = I[4], I[4] = I[5], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[12] = I[13], I[13] = I[14], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[21] = I[22], I[22] = I[23], I[24] = I[25], I[25] = I[26], \
   _p1##x = x++, ++_n1##x)

#define cimglist_for(list,l) for (int l = 0; l<(int)(list)._width; ++l)
#define cimglist_for_in(list,l0,l1,l) \
  for (int l = (int)(l0)<0?0:(int)(l0), _max##l = (unsigned int)l1<(list)._width?(int)(l1):(int)(list)._width - 1; \
  l<=_max##l; ++l)

#define cimglist_apply(list,fn) cimglist_for(list,__##fn) (list)[__##fn].fn

// Macros used to display error messages when exceptions are thrown.
// You should not use these macros is your own code.
#define _cimgdisplay_instance "[instance(%u,%u,%u,%c%s%c)] CImgDisplay::"
#define cimgdisplay_instance _width,_height,_normalization,_title?'\"':'[',_title?_title:"untitled",_title?'\"':']'
#define _cimg_instance "[instance(%u,%u,%u,%u,%p,%sshared)] CImg<%s>::"
#define cimg_instance _width,_height,_depth,_spectrum,_data,_is_shared?"":"non-",pixel_type()
#define _cimglist_instance "[instance(%u,%u,%p)] CImgList<%s>::"
#define cimglist_instance _width,_allocated_width,_data,pixel_type()

/*------------------------------------------------
 #
 #
 #  Define cimg_library:: namespace
 #
 #
 -------------------------------------------------*/
//! Contains <i>all classes and functions</i> of the \CImg library.
/**
   This namespace is defined to avoid functions and class names collisions
   that could happen with the inclusion of other C++ header files.
   Anyway, it should not happen often and you should reasonnably start most of your
   \CImg-based programs with
   \code
   #include "CImg.h"
   using namespace cimg_library;
   \endcode
   to simplify the declaration of \CImg Library objects afterwards.
**/
namespace cimg_library_suffixed {

// Declare the four classes of the CImg Library.
template<typename T=float> struct CImg;
template<typename T=float> struct CImgList;
struct CImgDisplay;
struct CImgException;

// Declare cimg:: namespace.
// This is an uncomplete namespace definition here. It only contains some
// necessary stuff to ensure a correct declaration order of the classes and functions
// defined afterwards.
namespace cimg {

// Define Ascii sequences for colored terminal output.
#ifdef cimg_use_vt100
static const char t_normal[] = { 0x1b, '[', '0', ';', '0', ';', '0', 'm', 0 };
static const char t_black[] = { 0x1b, '[', '0', ';', '3', '0', ';', '5', '9', 'm', 0 };
static const char t_red[] = { 0x1b, '[', '0', ';', '3', '1', ';', '5', '9', 'm', 0 };
static const char t_green[] = { 0x1b, '[', '0', ';', '3', '2', ';', '5', '9', 'm', 0 };
static const char t_yellow[] = { 0x1b, '[', '0', ';', '3', '3', ';', '5', '9', 'm', 0 };
static const char t_blue[] = { 0x1b, '[', '0', ';', '3', '4', ';', '5', '9', 'm', 0 };
static const char t_magenta[] = { 0x1b, '[', '0', ';', '3', '5', ';', '5', '9', 'm', 0 };
static const char t_cyan[] = { 0x1b, '[', '0', ';', '3', '6', ';', '5', '9', 'm', 0 };
static const char t_white[] = { 0x1b, '[', '0', ';', '3', '7', ';', '5', '9', 'm', 0 };
static const char t_bold[] = { 0x1b, '[', '1', 'm', 0 };
static const char t_underscore[] = { 0x1b, '[', '4', 'm', 0 };
#else
static const char t_normal[] = { 0 };
static const char *const t_black = cimg::t_normal,
*const t_red = cimg::t_normal,
*const t_green = cimg::t_normal,
*const t_yellow = cimg::t_normal,
*const t_blue = cimg::t_normal,
*const t_magenta = cimg::t_normal,
*const t_cyan = cimg::t_normal,
*const t_white = cimg::t_normal,
*const t_bold = cimg::t_normal,
*const t_underscore = cimg::t_normal;
#endif

inline std::FILE* output(std::FILE *file=0);
inline void info();

//! Avoid warning messages due to unused parameters. Do nothing actually.
template<typename T>
inline void unused(const T&, ...) {}

// [internal] Lock/unlock a mutex for managing concurrent threads.
// 'lock_mode' can be { 0=unlock | 1=lock | 2=trylock }.
// 'n' can be in [0,31] but mutex range [0,15] is reserved by CImg.
inline int mutex(const unsigned int n, const int lock_mode=1);

inline unsigned int& exception_mode(const unsigned int value, const bool is_set) {
static unsigned int mode = cimg_verbosity;
if (is_set) { cimg::mutex(0); mode = value<4?value:4; cimg::mutex(0,0); }
return mode;
}

// Functions to return standard streams 'stdin', 'stdout' and 'stderr'.
inline FILE* _stdin(const bool throw_exception=true);
inline FILE* _stdout(const bool throw_exception=true);
inline FILE* _stderr(const bool throw_exception=true);

// Mandatory because Microsoft's _snprintf() and _vsnprintf() do not add the '\0' character
// at the end of the string.
#if cimg_OS==2 && defined(_MSC_VER)
inline int _snprintf(char *const s, const size_t size, const char *const format, ...) {
va_list ap;
va_start(ap,format);
const int result = _vsnprintf(s,size,format,ap);
va_end(ap);
return result;
}

inline int _vsnprintf(char *const s, const size_t size, const char *const format, va_list ap) {
int result = -1;
cimg::mutex(6);
if (size) result = _vsnprintf_s(s,size,_TRUNCATE,format,ap);
if (result==-1) result = _vscprintf(format,ap);
cimg::mutex(6,0);
return result;
}

// Mutex-protected version of sscanf, sprintf and snprintf.
// Used only MacOSX, as it seems those functions are not re-entrant on MacOSX.
#elif defined(__MACOSX__) || defined(__APPLE__)
inline int _sscanf(const char *const s, const char *const format, ...) {
cimg::mutex(6);
va_list args;
va_start(args,format);
const int result = std::vsscanf(s,format,args);
va_end(args);
cimg::mutex(6,0);
return result;
}

inline int _sprintf(char *const s, const char *const format, ...) {
cimg::mutex(6);
va_list args;
va_start(args,format);
const int result = std::vsprintf(s,format,args);
va_end(args);
cimg::mutex(6,0);
return result;
}

inline int _snprintf(char *const s, const size_t n, const char *const format, ...) {
cimg::mutex(6);
va_list args;
va_start(args,format);
const int result = std::vsnprintf(s,n,format,args);
va_end(args);
cimg::mutex(6,0);
return result;
}

inline int _vsnprintf(char *const s, const size_t size, const char* format, va_list ap) {
cimg::mutex(6);
const int result = std::vsnprintf(s,size,format,ap);
cimg::mutex(6,0);
return result;
}
#endif

//! Set current \CImg exception mode.
/**
       The way error messages are handled by \CImg can be changed dynamically, using this function.
       \param mode Desired exception mode. Possible values are:
       - \c 0: Hide library messages (quiet mode).
       - \c 1: Print library messages on the console.
       - \c 2: Display library messages on a dialog window.
       - \c 3: Do as \c 1 + add extra debug warnings (slow down the code!).
       - \c 4: Do as \c 2 + add extra debug warnings (slow down the code!).
     **/
inline unsigned int& exception_mode(const unsigned int mode) {
return exception_mode(mode,true);
}

//! Return current \CImg exception mode.
/**
       \note By default, return the value of configuration macro \c cimg_verbosity
    **/
inline unsigned int& exception_mode() {
return exception_mode(0,false);
}

inline unsigned int openmp_mode(const unsigned int value, const bool is_set) {
static unsigned int mode = 2;
if (is_set)  { cimg::mutex(0); mode = value<2?value:2; cimg::mutex(0,0); }
return mode;
}

//! Set current \CImg openmp mode.
/**
       The way openmp-based methods are handled by \CImg can be changed dynamically, using this function.
       \param mode Desired openmp mode. Possible values are:
       - \c 0: Never parallelize.
       - \c 1: Always parallelize.
       - \c 2: Adaptive parallelization mode (default behavior).
     **/
inline unsigned int openmp_mode(const unsigned int mode) {
return openmp_mode(mode,true);
}

//! Return current \CImg openmp mode.
inline unsigned int openmp_mode() {
return openmp_mode(0,false);
}

#ifndef cimg_openmp_sizefactor
#define cimg_openmp_sizefactor 1
#endif
#define cimg_openmp_if(cond) if ((cimg::openmp_mode()==1 || (cimg::openmp_mode()>1 && (cond))))
#define cimg_openmp_if_size(size,min_size) cimg_openmp_if((size)>=(cimg_openmp_sizefactor)*(min_size))
#ifdef _MSC_VER
// Disable 'collapse()' directive for MSVC (supports only OpenMP 2.0).
#define cimg_openmp_collapse(k)
#else
#define cimg_openmp_collapse(k) collapse(k)
#endif

#if cimg_OS==2
// Disable parallelization of simple loops on Windows, due to noticed performance drop.
#define cimg_openmp_for(instance,expr,min_size) cimg_rof((instance),ptr,T) *ptr = (T)(expr);
#else
#define cimg_openmp_for(instance,expr,min_size) \
    cimg_pragma_openmp(parallel for cimg_openmp_if_size((instance).size(),min_size)) \
      cimg_rof((instance),ptr,T) *ptr = (T)(expr);
#endif

// Display a simple dialog box, and wait for the user's response.
inline int dialog(const char *const title, const char *const msg, const char *const button1_label="OK",
const char *const button2_label=0, const char *const button3_label=0,
const char *const button4_label=0, const char *const button5_label=0,
const char *const button6_label=0, const bool centering=false);

// Evaluate math expression.
inline double eval(const char *const expression,
const double x=0, const double y=0, const double z=0, const double c=0);

}

/*---------------------------------------
    #
    # Define the CImgException structures
    #
    --------------------------------------*/
//! Instances of \c CImgException are thrown when errors are encountered in a \CImg function call.
/**
     \par Overview

      CImgException is the base class of all exceptions thrown by \CImg (except \b CImgAbortException).
      CImgException is never thrown itself. Derived classes that specify the type of errord are thrown instead.
      These classes can be:

      - \b CImgAbortException: Thrown when a computationally-intensive function is aborted by an external signal.
        This is the only \c non-derived exception class.

      - \b CImgArgumentException: Thrown when one argument of a called \CImg function is invalid.
      This is probably one of the most thrown exception by \CImg.
      For instance, the following example throws a \c CImgArgumentException:
      \code
      CImg<float> img(100,100,1,3); // Define a 100x100 color image with float-valued pixels
      img.mirror('e');              // Try to mirror image along the (non-existing) 'e'-axis
      \endcode

      - \b CImgDisplayException: Thrown when something went wrong during the display of images in CImgDisplay instances.

      - \b CImgInstanceException: Thrown when an instance associated to a called \CImg method does not fit
      the function requirements. For instance, the following example throws a \c CImgInstanceException:
      \code
      const CImg<float> img;           // Define an empty image
      const float value = img.at(0);   // Try to read first pixel value (does not exist)
      \endcode

      - \b CImgIOException: Thrown when an error occured when trying to load or save image files.
      This happens when trying to read files that do not exist or with invalid formats.
      For instance, the following example throws a \c CImgIOException:
      \code
      const CImg<float> img("missing_file.jpg");  // Try to load a file that does not exist
      \endcode

      - \b CImgWarningException: Thrown only if configuration macro \c cimg_strict_warnings is set, and
      when a \CImg function has to display a warning message (see cimg::warn()).

      It is not recommended to throw CImgException instances by yourself,
      since they are expected to be thrown only by \CImg.
      When an error occurs in a library function call, \CImg may display error messages on the screen or on the
      standard output, depending on the current \CImg exception mode.
      The \CImg exception mode can be get and set by functions cimg::exception_mode() and
      cimg::exception_mode(unsigned int).

      \par Exceptions handling

      In all cases, when an error occurs in \CImg, an instance of the corresponding exception class is thrown.
      This may lead the program to break (this is the default behavior), but you can bypass this behavior by
      handling the exceptions by yourself,
      using a usual <tt>try { ... } catch () { ... }</tt> bloc, as in the following example:
      \code
      #define "CImg.h"
      using namespace cimg_library;
      int main() {
        cimg::exception_mode(0);                                    // Enable quiet exception mode
        try {
          ...                                                       // Here, do what you want to stress CImg
        } catch (CImgException& e) {                                // You succeeded: something went wrong!
          std::fprintf(stderr,"CImg Library Error: %s",e.what());   // Display your custom error message
          ...                                                       // Do what you want now to save the ship!
          }
        }
      \endcode
  **/
struct CImgException : public std::exception {
#define _cimg_exception_err(etype,disp_flag) \
  std::va_list ap, ap2; \
  va_start(ap,format); va_start(ap2,format); \
  int size = cimg_vsnprintf(0,0,format,ap2); \
  if (size++>=0) { \
    delete[] _message; \
    _message = new char[size]; \
    cimg_vsnprintf(_message,size,format,ap); \
    if (cimg::exception_mode()) { \
      std::fprintf(cimg::output(),"\n%s[CImg] *** %s ***%s %s\n",cimg::t_red,etype,cimg::t_normal,_message); \
      if (cimg_display && disp_flag && !(cimg::exception_mode()%2)) try { cimg::dialog(etype,_message,"Abort"); } \
      catch (CImgException&) {} \
      if (cimg::exception_mode()>=3) cimg_library_suffixed::cimg::info(); \
    } \
  } \
  va_end(ap); va_end(ap2); \

char *_message;
CImgException() { _message = new char[1]; *_message = 0; }
CImgException(const char *const format, ...):_message(0) { _cimg_exception_err("CImgException",true); }
CImgException(const CImgException& e):std::exception(e) {
const size_t size = std::strlen(e._message);
_message = new char[size + 1];
std::strncpy(_message,e._message,size);
_message[size] = 0;
}
~CImgException() throw() { delete[] _message; }
CImgException& operator=(const CImgException& e) {
const size_t size = std::strlen(e._message);
_message = new char[size + 1];
std::strncpy(_message,e._message,size);
_message[size] = 0;
return *this;
}
//! Return a C-string containing the error message associated to the thrown exception.
const char *what() const throw() { return _message; }
};

// The CImgAbortException class is used to throw an exception when
// a computationally-intensive function has been aborted by an external signal.
struct CImgAbortException : public std::exception {
char *_message;
CImgAbortException() { _message = new char[1]; *_message = 0; }
CImgAbortException(const char *const format, ...):_message(0) { _cimg_exception_err("CImgAbortException",true); }
CImgAbortException(const CImgAbortException& e):std::exception(e) {
const size_t size = std::strlen(e._message);
_message = new char[size + 1];
std::strncpy(_message,e._message,size);
_message[size] = 0;
}
~CImgAbortException() throw() { delete[] _message; }
CImgAbortException& operator=(const CImgAbortException& e) {
const size_t size = std::strlen(e._message);
_message = new char[size + 1];
std::strncpy(_message,e._message,size);
_message[size] = 0;
return *this;
}
//! Return a C-string containing the error message associated to the thrown exception.
const char *what() const throw() { return _message; }
};

// The CImgArgumentException class is used to throw an exception related
// to invalid arguments encountered in a library function call.
struct CImgArgumentException : public CImgException {
CImgArgumentException(const char *const format, ...) { _cimg_exception_err("CImgArgumentException",true); }
};

// The CImgDisplayException class is used to throw an exception related
// to display problems encountered in a library function call.
struct CImgDisplayException : public CImgException {
CImgDisplayException(const char *const format, ...) { _cimg_exception_err("CImgDisplayException",false); }
};

// The CImgInstanceException class is used to throw an exception related
// to an invalid instance encountered in a library function call.
struct CImgInstanceException : public CImgException {
CImgInstanceException(const char *const format, ...) { _cimg_exception_err("CImgInstanceException",true); }
};

// The CImgIOException class is used to throw an exception related
// to input/output file problems encountered in a library function call.
struct CImgIOException : public CImgException {
CImgIOException(const char *const format, ...) { _cimg_exception_err("CImgIOException",true); }
};

// The CImgWarningException class is used to throw an exception for warnings
// encountered in a library function call.
struct CImgWarningException : public CImgException {
CImgWarningException(const char *const format, ...) { _cimg_exception_err("CImgWarningException",false); }
};

/*-------------------------------------
    #
    # Define cimg:: namespace
    #
    -----------------------------------*/
//! Contains \a low-level functions and variables of the \CImg Library.
/**
     Most of the functions and variables within this namespace are used by the \CImg library for low-level operations.
     You may use them to access specific const values or environment variables internally used by \CImg.
     \warning Never write <tt>using namespace cimg_library::cimg;</tt> in your source code. Lot of functions in the
     <tt>cimg:: namespace</tt> have the same names as standard C functions that may be defined in the global
     namespace <tt>::</tt>.
  **/
namespace cimg {

// Define traits that will be used to determine the best data type to work in CImg functions.
//
template<typename T> struct type {
static const char* string() {
static const char* s[] = { "unknown",   "unknown8",   "unknown16",  "unknown24",
"unknown32", "unknown40",  "unknown48",  "unknown56",
"unknown64", "unknown72",  "unknown80",  "unknown88",
"unknown96", "unknown104", "unknown112", "unknown120",
"unknown128" };
return s[(sizeof(T)<17)?sizeof(T):0];
}
static bool is_float() { return false; }
static bool is_inf(const T) { return false; }
static bool is_nan(const T) { return false; }
static T min() { return ~max(); }
static T max() { return (T)1<<(8*sizeof(T) - 1); }
static T inf() { return max(); }
static T cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(T)val; }
static const char* format() { return "%s"; }
static const char* format_s() { return "%s"; }
static const char* format(const T& val) { static const char *const s = "unknown"; cimg::unused(val); return s; }
};

template<> struct type<bool> {
static const char* string() { static const char *const s = "bool"; return s; }
static bool is_float() { return false; }
static bool is_inf(const bool) { return false; }
static bool is_nan(const bool) { return false; }
static bool min() { return false; }
static bool max() { return true; }
static bool inf() { return max(); }
static bool is_inf() { return false; }
static bool cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(bool)val; }
static const char* format() { return "%s"; }
static const char* format_s() { return "%s"; }
static const char* format(const bool val) { static const char* s[] = { "false", "true" }; return s[val?1:0]; }
};

template<> struct type<unsigned char> {
static const char* string() { static const char *const s = "unsigned char"; return s; }
static bool is_float() { return false; }
static bool is_inf(const unsigned char) { return false; }
static bool is_nan(const unsigned char) { return false; }
static unsigned char min() { return 0; }
static unsigned char max() { return (unsigned char)-1; }
static unsigned char inf() { return max(); }
static unsigned char cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(unsigned char)val; }
static const char* format() { return "%u"; }
static const char* format_s() { return "%u"; }
static unsigned int format(const unsigned char val) { return (unsigned int)val; }
};

#if defined(CHAR_MAX) && CHAR_MAX==255
template<> struct type<char> {
static const char* string() { static const char *const s = "char"; return s; }
static bool is_float() { return false; }
static bool is_inf(const char) { return false; }
static bool is_nan(const char) { return false; }
static char min() { return 0; }
static char max() { return (char)-1; }
static char inf() { return max(); }
static char cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(unsigned char)val; }
static const char* format() { return "%u"; }
static const char* format_s() { return "%u"; }
static unsigned int format(const char val) { return (unsigned int)val; }
};
#else
template<> struct type<char> {
static const char* string() { static const char *const s = "char"; return s; }
static bool is_float() { return false; }
static bool is_inf(const char) { return false; }
static bool is_nan(const char) { return false; }
static char min() { return ~max(); }
static char max() { return (char)((unsigned char)-1>>1); }
static char inf() { return max(); }
static char cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(char)val; }
static const char* format() { return "%d"; }
static const char* format_s() { return "%d"; }
static int format(const char val) { return (int)val; }
};
#endif

template<> struct type<signed char> {
static const char* string() { static const char *const s = "signed char"; return s; }
static bool is_float() { return false; }
static bool is_inf(const signed char) { return false; }
static bool is_nan(const signed char) { return false; }
static signed char min() { return ~max(); }
static signed char max() { return (signed char)((unsigned char)-1>>1); }
static signed char inf() { return max(); }
static signed char cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(signed char)val; }
static const char* format() { return "%d"; }
static const char* format_s() { return "%d"; }
static int format(const signed char val) { return (int)val; }
};

template<> struct type<unsigned short> {
static const char* string() { static const char *const s = "unsigned short"; return s; }
static bool is_float() { return false; }
static bool is_inf(const unsigned short) { return false; }
static bool is_nan(const unsigned short) { return false; }
static unsigned short min() { return 0; }
static unsigned short max() { return (unsigned short)-1; }
static unsigned short inf() { return max(); }
static unsigned short cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(unsigned short)val; }
static const char* format() { return "%u"; }
static const char* format_s() { return "%u"; }
static unsigned int format(const unsigned short val) { return (unsigned int)val; }
};

template<> struct type<short> {
static const char* string() { static const char *const s = "short"; return s; }
static bool is_float() { return false; }
static bool is_inf(const short) { return false; }
static bool is_nan(const short) { return false; }
static short min() { return ~max(); }
static short max() { return (short)((unsigned short)-1>>1); }
static short inf() { return max(); }
static short cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(short)val; }
static const char* format() { return "%d"; }
static const char* format_s() { return "%d"; }
static int format(const short val) { return (int)val; }
};

template<> struct type<unsigned int> {
static const char* string() { static const char *const s = "unsigned int"; return s; }
static bool is_float() { return false; }
static bool is_inf(const unsigned int) { return false; }
static bool is_nan(const unsigned int) { return false; }
static unsigned int min() { return 0; }
static unsigned int max() { return (unsigned int)-1; }
static unsigned int inf() { return max(); }
static unsigned int cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(unsigned int)val; }
static const char* format() { return "%u"; }
static const char* format_s() { return "%u"; }
static unsigned int format(const unsigned int val) { return val; }
};

template<> struct type<int> {
static const char* string() { static const char *const s = "int"; return s; }
static bool is_float() { return false; }
static bool is_inf(const int) { return false; }
static bool is_nan(const int) { return false; }
static int min() { return ~max(); }
static int max() { return (int)((unsigned int)-1>>1); }
static int inf() { return max(); }
static int cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(int)val; }
static const char* format() { return "%d"; }
static const char* format_s() { return "%d"; }
static int format(const int val) { return val; }
};

template<> struct type<cimg_uint64> {
static const char* string() { static const char *const s = "unsigned int64"; return s; }
static bool is_float() { return false; }
static bool is_inf(const cimg_uint64) { return false; }
static bool is_nan(const cimg_uint64) { return false; }
static cimg_uint64 min() { return 0; }
static cimg_uint64 max() { return (cimg_uint64)-1; }
static cimg_uint64 inf() { return max(); }
static cimg_uint64 cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(cimg_uint64)val; }
static const char* format() { return cimg_fuint64; }
static const char* format_s() { return cimg_fuint64; }
static unsigned long format(const cimg_uint64 val) { return (unsigned long)val; }
};

template<> struct type<cimg_int64> {
static const char* string() { static const char *const s = "int64"; return s; }
static bool is_float() { return false; }
static bool is_inf(const cimg_int64) { return false; }
static bool is_nan(const cimg_int64) { return false; }
static cimg_int64 min() { return ~max(); }
static cimg_int64 max() { return (cimg_int64)((cimg_uint64)-1>>1); }
static cimg_int64 inf() { return max(); }
static cimg_int64 cut(const double val) {
return val<(double)min()?min():val>(double)max()?max():(cimg_int64)val;
}
static const char* format() { return cimg_fint64; }
static const char* format_s() { return cimg_fint64; }
static long format(const long val) { return (long)val; }
};

template<> struct type<double> {
static const char* string() { static const char *const s = "double"; return s; }
static bool is_float() { return true; }
static bool is_inf(const double val) {
#ifdef isinf
return (bool)isinf(val);
#else
return !is_nan(val) && (val<cimg::type<double>::min() || val>cimg::type<double>::max());
#endif
}
static bool is_nan(const double val) { // Custom version that works with '-ffast-math'
if (sizeof(double)==8) {
cimg_uint64 u;
std::memcpy(&u,&val,sizeof(double));
return ((unsigned int)(u>>32)&0x7fffffff) + ((unsigned int)u!=0)>0x7ff00000;
}
#ifdef isnan
return (bool)isnan(val);
#else
return !(val==val);
#endif
}
static double min() { return -DBL_MAX; }
static double max() { return DBL_MAX; }
static double inf() {
#ifdef INFINITY
return (double)INFINITY;
#else
return max()*max();
#endif
}
static double nan() {
#ifdef NAN
return (double)NAN;
#else
const double val_nan = -std::sqrt(-1.); return val_nan;
#endif
}
static double cut(const double val) { return val; }
static const char* format() { return "%.17g"; }
static const char* format_s() { return "%g"; }
static double format(const double val) { return val; }
};

template<> struct type<float> {
static const char* string() { static const char *const s = "float"; return s; }
static bool is_float() { return true; }
static bool is_inf(const float val) {
#ifdef isinf
return (bool)isinf(val);
#else
return !is_nan(val) && (val<cimg::type<float>::min() || val>cimg::type<float>::max());
#endif
}
static bool is_nan(const float val) { // Custom version that works with '-ffast-math'
if (sizeof(float)==4) {
unsigned int u;
std::memcpy(&u,&val,sizeof(float));
return (u&0x7fffffff)>0x7f800000;
}
#ifdef isnan
return (bool)isnan(val);
#else
return !(val==val);
#endif
}
static float min() { return -FLT_MAX; }
static float max() { return FLT_MAX; }
static float inf() { return (float)cimg::type<double>::inf(); }
static float nan() { return (float)cimg::type<double>::nan(); }
static float cut(const double val) { return (float)val; }
static float cut(const float val) { return (float)val; }
static const char* format() { return "%.9g"; }
static const char* format_s() { return "%g"; }
static double format(const float val) { return (double)val; }
};

template<> struct type<long double> {
static const char* string() { static const char *const s = "long double"; return s; }
static bool is_float() { return true; }
static bool is_inf(const long double val) {
#ifdef isinf
return (bool)isinf(val);
#else
return !is_nan(val) && (val<cimg::type<long double>::min() || val>cimg::type<long double>::max());
#endif
}
static bool is_nan(const long double val) {
#ifdef isnan
return (bool)isnan(val);
#else
return !(val==val);
#endif
}
static long double min() { return -LDBL_MAX; }
static long double max() { return LDBL_MAX; }
static long double inf() { return max()*max(); }
static long double nan() { const long double val_nan = -std::sqrt(-1.L); return val_nan; }
static long double cut(const long double val) { return val; }
static const char* format() { return "%.17g"; }
static const char* format_s() { return "%g"; }
static double format(const long double val) { return (double)val; }
};

#ifdef cimg_use_half
template<> struct type<half> {
static const char* string() { static const char *const s = "half"; return s; }
static bool is_float() { return true; }
static bool is_inf(const long double val) {
#ifdef isinf
return (bool)isinf(val);
#else
return !is_nan(val) && (val<cimg::type<half>::min() || val>cimg::type<half>::max());
#endif
}
static bool is_nan(const half val) { // Custom version that works with '-ffast-math'
if (sizeof(half)==2) {
short u;
std::memcpy(&u,&val,sizeof(short));
return (bool)((u&0x7fff)>0x7c00);
}
return cimg::type<float>::is_nan((float)val);
}
static half min() { return (half)-65504; }
static half max() { return (half)65504; }
static half inf() { return max()*max(); }
static half nan() { const half val_nan = (half)-std::sqrt(-1.); return val_nan; }
static half cut(const double val) { return (half)val; }
static const char* format() { return "%.9g"; }
static const char* format_s() { return "%g"; }
static double format(const half val) { return (double)val; }
};
#endif

template<typename T, typename t> struct superset { typedef T type; };
template<> struct superset<bool,unsigned char> { typedef unsigned char type; };
template<> struct superset<bool,char> { typedef char type; };
template<> struct superset<bool,signed char> { typedef signed char type; };
template<> struct superset<bool,unsigned short> { typedef unsigned short type; };
template<> struct superset<bool,short> { typedef short type; };
template<> struct superset<bool,unsigned int> { typedef unsigned int type; };
template<> struct superset<bool,int> { typedef int type; };
template<> struct superset<bool,cimg_uint64> { typedef cimg_uint64 type; };
template<> struct superset<bool,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<bool,float> { typedef float type; };
template<> struct superset<bool,double> { typedef double type; };
template<> struct superset<unsigned char,char> { typedef short type; };
template<> struct superset<unsigned char,signed char> { typedef short type; };
template<> struct superset<unsigned char,unsigned short> { typedef unsigned short type; };
template<> struct superset<unsigned char,short> { typedef short type; };
template<> struct superset<unsigned char,unsigned int> { typedef unsigned int type; };
template<> struct superset<unsigned char,int> { typedef int type; };
template<> struct superset<unsigned char,cimg_uint64> { typedef cimg_uint64 type; };
template<> struct superset<unsigned char,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<unsigned char,float> { typedef float type; };
template<> struct superset<unsigned char,double> { typedef double type; };
template<> struct superset<signed char,unsigned char> { typedef short type; };
template<> struct superset<signed char,char> { typedef short type; };
template<> struct superset<signed char,unsigned short> { typedef int type; };
template<> struct superset<signed char,short> { typedef short type; };
template<> struct superset<signed char,unsigned int> { typedef cimg_int64 type; };
template<> struct superset<signed char,int> { typedef int type; };
template<> struct superset<signed char,cimg_uint64> { typedef cimg_int64 type; };
template<> struct superset<signed char,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<signed char,float> { typedef float type; };
template<> struct superset<signed char,double> { typedef double type; };
template<> struct superset<char,unsigned char> { typedef short type; };
template<> struct superset<char,signed char> { typedef short type; };
template<> struct superset<char,unsigned short> { typedef int type; };
template<> struct superset<char,short> { typedef short type; };
template<> struct superset<char,unsigned int> { typedef cimg_int64 type; };
template<> struct superset<char,int> { typedef int type; };
template<> struct superset<char,cimg_uint64> { typedef cimg_int64 type; };
template<> struct superset<char,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<char,float> { typedef float type; };
template<> struct superset<char,double> { typedef double type; };
template<> struct superset<unsigned short,char> { typedef int type; };
template<> struct superset<unsigned short,signed char> { typedef int type; };
template<> struct superset<unsigned short,short> { typedef int type; };
template<> struct superset<unsigned short,unsigned int> { typedef unsigned int type; };
template<> struct superset<unsigned short,int> { typedef int type; };
template<> struct superset<unsigned short,cimg_uint64> { typedef cimg_uint64 type; };
template<> struct superset<unsigned short,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<unsigned short,float> { typedef float type; };
template<> struct superset<unsigned short,double> { typedef double type; };
template<> struct superset<short,unsigned short> { typedef int type; };
template<> struct superset<short,unsigned int> { typedef cimg_int64 type; };
template<> struct superset<short,int> { typedef int type; };
template<> struct superset<short,cimg_uint64> { typedef cimg_int64 type; };
template<> struct superset<short,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<short,float> { typedef float type; };
template<> struct superset<short,double> { typedef double type; };
template<> struct superset<unsigned int,char> { typedef cimg_int64 type; };
template<> struct superset<unsigned int,signed char> { typedef cimg_int64 type; };
template<> struct superset<unsigned int,short> { typedef cimg_int64 type; };
template<> struct superset<unsigned int,int> { typedef cimg_int64 type; };
template<> struct superset<unsigned int,cimg_uint64> { typedef cimg_uint64 type; };
template<> struct superset<unsigned int,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<unsigned int,float> { typedef float type; };
template<> struct superset<unsigned int,double> { typedef double type; };
template<> struct superset<int,unsigned int> { typedef cimg_int64 type; };
template<> struct superset<int,cimg_uint64> { typedef cimg_int64 type; };
template<> struct superset<int,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<int,float> { typedef float type; };
template<> struct superset<int,double> { typedef double type; };
template<> struct superset<cimg_uint64,char> { typedef cimg_int64 type; };
template<> struct superset<cimg_uint64,signed char> { typedef cimg_int64 type; };
template<> struct superset<cimg_uint64,short> { typedef cimg_int64 type; };
template<> struct superset<cimg_uint64,int> { typedef cimg_int64 type; };
template<> struct superset<cimg_uint64,cimg_int64> { typedef cimg_int64 type; };
template<> struct superset<cimg_uint64,float> { typedef double type; };
template<> struct superset<cimg_uint64,double> { typedef double type; };
template<> struct superset<cimg_int64,float> { typedef double type; };
template<> struct superset<cimg_int64,double> { typedef double type; };
template<> struct superset<float,double> { typedef double type; };

#ifdef cimg_use_half
template<> struct superset<half,unsigned short> { typedef float type; };
template<> struct superset<half,short> { typedef float type; };
template<> struct superset<half,unsigned int> { typedef float type; };
template<> struct superset<half,int> { typedef float type; };
template<> struct superset<half,cimg_uint64> { typedef float type; };
template<> struct superset<half,cimg_int64> { typedef float type; };
template<> struct superset<half,float> { typedef float type; };
template<> struct superset<half,double> { typedef double type; };
#endif

template<typename t1, typename t2, typename t3> struct superset2 {
typedef typename superset<t1, typename superset<t2,t3>::type>::type type;
};

template<typename t1, typename t2, typename t3, typename t4> struct superset3 {
typedef typename superset<t1, typename superset2<t2,t3,t4>::type>::type type;
};

template<typename t1, typename t2> struct last { typedef t2 type; };

#define _cimg_Tt typename cimg::superset<T,t>::type
#define _cimg_Tfloat typename cimg::superset<T,float>::type
#define _cimg_Ttfloat typename cimg::superset2<T,t,float>::type
#define _cimg_Ttdouble typename cimg::superset2<T,t,double>::type

// Define variables used internally by CImg.
#if cimg_display==1
struct X11_info {
unsigned int nb_wins;
pthread_t *events_thread;
pthread_cond_t wait_event;
pthread_mutex_t wait_event_mutex;
CImgDisplay **wins;
Display *display;
unsigned int nb_bits;
bool is_blue_first;
bool is_shm_enabled;
bool byte_order;

#ifdef cimg_use_xrandr
XRRScreenSize *resolutions;
Rotation curr_rotation;
unsigned int curr_resolution;
unsigned int nb_resolutions;
#endif
X11_info():nb_wins(0),events_thread(0),display(0),
nb_bits(0),is_blue_first(false),is_shm_enabled(false),byte_order(false) {
#ifdef __FreeBSD__
XInitThreads();
#endif
wins = new CImgDisplay*[1024];
pthread_mutex_init(&wait_event_mutex,0);
pthread_cond_init(&wait_event,0);

#ifdef cimg_use_xrandr
resolutions = 0;
curr_rotation = 0;
curr_resolution = nb_resolutions = 0;
#endif
}

~X11_info() {
delete[] wins;
/*
          if (events_thread) {
          pthread_cancel(*events_thread);
          delete events_thread;
          }
          if (display) { } // XCloseDisplay(display); }
          pthread_cond_destroy(&wait_event);
          pthread_mutex_unlock(&wait_event_mutex);
          pthread_mutex_destroy(&wait_event_mutex);
        */
}
};
#if defined(cimg_module)
X11_info& X11_attr();
#elif defined(cimg_main)
X11_info& X11_attr() { static X11_info val; return val; }
#else
inline X11_info& X11_attr() { static X11_info val; return val; }
#endif

#elif cimg_display==2
struct Win32_info {
HANDLE wait_event;
Win32_info() { wait_event = CreateEvent(0,FALSE,FALSE,0); }
};
#if defined(cimg_module)
Win32_info& Win32_attr();
#elif defined(cimg_main)
Win32_info& Win32_attr() { static Win32_info val; return val; }
#else
inline Win32_info& Win32_attr() { static Win32_info val; return val; }
#endif
#endif
#define cimg_lock_display() cimg::mutex(15)
#define cimg_unlock_display() cimg::mutex(15,0)

struct Mutex_info {
#ifdef _PTHREAD_H
pthread_mutex_t mutex[32];
Mutex_info() { for (unsigned int i = 0; i<32; ++i) pthread_mutex_init(&mutex[i],0); }
void lock(const unsigned int n) { pthread_mutex_lock(&mutex[n]); }
void unlock(const unsigned int n) { pthread_mutex_unlock(&mutex[n]); }
int trylock(const unsigned int n) { return pthread_mutex_trylock(&mutex[n]); }
#elif cimg_OS==2
HANDLE mutex[32];
Mutex_info() { for (unsigned int i = 0; i<32; ++i) mutex[i] = CreateMutex(0,FALSE,0); }
void lock(const unsigned int n) { WaitForSingleObject(mutex[n],INFINITE); }
void unlock(const unsigned int n) { ReleaseMutex(mutex[n]); }
int trylock(const unsigned int) { return 0; }
#else
Mutex_info() {}
void lock(const unsigned int) {}
void unlock(const unsigned int) {}
int trylock(const unsigned int) { return 0; }
#endif
};
#if defined(cimg_module)
Mutex_info& Mutex_attr();
#elif defined(cimg_main)
Mutex_info& Mutex_attr() { static Mutex_info val; return val; }
#else
inline Mutex_info& Mutex_attr() { static Mutex_info val; return val; }
#endif

#if defined(cimg_use_magick)
static struct Magick_info {
Magick_info() {
Magick::InitializeMagick("");
}
} _Magick_info;
#endif

#if defined(cimg_use_fftw3)
static struct FFTW3_info {
FFTW3_info() {
fftw_init_threads();
}
} _FFTW3_info;
#endif

#if cimg_display==1
// Define keycodes for X11-based graphical systems.
const unsigned int keyESC        = XK_Escape;
const unsigned int keyF1         = XK_F1;
const unsigned int keyF2         = XK_F2;
const unsigned int keyF3         = XK_F3;
const unsigned int keyF4         = XK_F4;
const unsigned int keyF5         = XK_F5;
const unsigned int keyF6         = XK_F6;
const unsigned int keyF7         = XK_F7;
const unsigned int keyF8         = XK_F8;
const unsigned int keyF9         = XK_F9;
const unsigned int keyF10        = XK_F10;
const unsigned int keyF11        = XK_F11;
const unsigned int keyF12        = XK_F12;
const unsigned int keyPAUSE      = XK_Pause;
const unsigned int key1          = XK_1;
const unsigned int key2          = XK_2;
const unsigned int key3          = XK_3;
const unsigned int key4          = XK_4;
const unsigned int key5          = XK_5;
const unsigned int key6          = XK_6;
const unsigned int key7          = XK_7;
const unsigned int key8          = XK_8;
const unsigned int key9          = XK_9;
const unsigned int key0          = XK_0;
const unsigned int keyBACKSPACE  = XK_BackSpace;
const unsigned int keyINSERT     = XK_Insert;
const unsigned int keyHOME       = XK_Home;
const unsigned int keyPAGEUP     = XK_Page_Up;
const unsigned int keyTAB        = XK_Tab;
const unsigned int keyQ          = XK_q;
const unsigned int keyW          = XK_w;
const unsigned int keyE          = XK_e;
const unsigned int keyR          = XK_r;
const unsigned int keyT          = XK_t;
const unsigned int keyY          = XK_y;
const unsigned int keyU          = XK_u;
const unsigned int keyI          = XK_i;
const unsigned int keyO          = XK_o;
const unsigned int keyP          = XK_p;
const unsigned int keyDELETE     = XK_Delete;
const unsigned int keyEND        = XK_End;
const unsigned int keyPAGEDOWN   = XK_Page_Down;
const unsigned int keyCAPSLOCK   = XK_Caps_Lock;
const unsigned int keyA          = XK_a;
const unsigned int keyS          = XK_s;
const unsigned int keyD          = XK_d;
const unsigned int keyF          = XK_f;
const unsigned int keyG          = XK_g;
const unsigned int keyH          = XK_h;
const unsigned int keyJ          = XK_j;
const unsigned int keyK          = XK_k;
const unsigned int keyL          = XK_l;
const unsigned int keyENTER      = XK_Return;
const unsigned int keySHIFTLEFT  = XK_Shift_L;
const unsigned int keyZ          = XK_z;
const unsigned int keyX          = XK_x;
const unsigned int keyC          = XK_c;
const unsigned int keyV          = XK_v;
const unsigned int keyB          = XK_b;
const unsigned int keyN          = XK_n;
const unsigned int keyM          = XK_m;
const unsigned int keySHIFTRIGHT = XK_Shift_R;
const unsigned int keyARROWUP    = XK_Up;
const unsigned int keyCTRLLEFT   = XK_Control_L;
const unsigned int keyAPPLEFT    = XK_Super_L;
const unsigned int keyALT        = XK_Alt_L;
const unsigned int keySPACE      = XK_space;
const unsigned int keyALTGR      = XK_Alt_R;
const unsigned int keyAPPRIGHT   = XK_Super_R;
const unsigned int keyMENU       = XK_Menu;
const unsigned int keyCTRLRIGHT  = XK_Control_R;
const unsigned int keyARROWLEFT  = XK_Left;
const unsigned int keyARROWDOWN  = XK_Down;
const unsigned int keyARROWRIGHT = XK_Right;
const unsigned int keyPAD0       = XK_KP_0;
const unsigned int keyPAD1       = XK_KP_1;
const unsigned int keyPAD2       = XK_KP_2;
const unsigned int keyPAD3       = XK_KP_3;
const unsigned int keyPAD4       = XK_KP_4;
const unsigned int keyPAD5       = XK_KP_5;
const unsigned int keyPAD6       = XK_KP_6;
const unsigned int keyPAD7       = XK_KP_7;
const unsigned int keyPAD8       = XK_KP_8;
const unsigned int keyPAD9       = XK_KP_9;
const unsigned int keyPADADD     = XK_KP_Add;
const unsigned int keyPADSUB     = XK_KP_Subtract;
const unsigned int keyPADMUL     = XK_KP_Multiply;
const unsigned int keyPADDIV     = XK_KP_Divide;

#elif cimg_display==2
// Define keycodes for Windows.
const unsigned int keyESC        = VK_ESCAPE;
const unsigned int keyF1         = VK_F1;
const unsigned int keyF2         = VK_F2;
const unsigned int keyF3         = VK_F3;
const unsigned int keyF4         = VK_F4;
const unsigned int keyF5         = VK_F5;
const unsigned int keyF6         = VK_F6;
const unsigned int keyF7         = VK_F7;
const unsigned int keyF8         = VK_F8;
const unsigned int keyF9         = VK_F9;
const unsigned int keyF10        = VK_F10;
const unsigned int keyF11        = VK_F11;
const unsigned int keyF12        = VK_F12;
const unsigned int keyPAUSE      = VK_PAUSE;
const unsigned int key1          = '1';
const unsigned int key2          = '2';
const unsigned int key3          = '3';
const unsigned int key4          = '4';
const unsigned int key5          = '5';
const unsigned int key6          = '6';
const unsigned int key7          = '7';
const unsigned int key8          = '8';
const unsigned int key9          = '9';
const unsigned int key0          = '0';
const unsigned int keyBACKSPACE  = VK_BACK;
const unsigned int keyINSERT     = VK_INSERT;
const unsigned int keyHOME       = VK_HOME;
const unsigned int keyPAGEUP     = VK_PRIOR;
const unsigned int keyTAB        = VK_TAB;
const unsigned int keyQ          = 'Q';
const unsigned int keyW          = 'W';
const unsigned int keyE          = 'E';
const unsigned int keyR          = 'R';
const unsigned int keyT          = 'T';
const unsigned int keyY          = 'Y';
const unsigned int keyU          = 'U';
const unsigned int keyI          = 'I';
const unsigned int keyO          = 'O';
const unsigned int keyP          = 'P';
const unsigned int keyDELETE     = VK_DELETE;
const unsigned int keyEND        = VK_END;
const unsigned int keyPAGEDOWN   = VK_NEXT;
const unsigned int keyCAPSLOCK   = VK_CAPITAL;
const unsigned int keyA          = 'A';
const unsigned int keyS          = 'S';
const unsigned int keyD          = 'D';
const unsigned int keyF          = 'F';
const unsigned int keyG          = 'G';
const unsigned int keyH          = 'H';
const unsigned int keyJ          = 'J';
const unsigned int keyK          = 'K';
const unsigned int keyL          = 'L';
const unsigned int keyENTER      = VK_RETURN;
const unsigned int keySHIFTLEFT  = VK_SHIFT;
const unsigned int keyZ          = 'Z';
const unsigned int keyX          = 'X';
const unsigned int keyC          = 'C';
const unsigned int keyV          = 'V';
const unsigned int keyB          = 'B';
const unsigned int keyN          = 'N';
const unsigned int keyM          = 'M';
const unsigned int keySHIFTRIGHT = VK_SHIFT;
const unsigned int keyARROWUP    = VK_UP;
const unsigned int keyCTRLLEFT   = VK_CONTROL;
const unsigned int keyAPPLEFT    = VK_LWIN;
const unsigned int keyALT        = VK_LMENU;
const unsigned int keySPACE      = VK_SPACE;
const unsigned int keyALTGR      = VK_CONTROL;
const unsigned int keyAPPRIGHT   = VK_RWIN;
const unsigned int keyMENU       = VK_APPS;
const unsigned int keyCTRLRIGHT  = VK_CONTROL;
const unsigned int keyARROWLEFT  = VK_LEFT;
const unsigned int keyARROWDOWN  = VK_DOWN;
const unsigned int keyARROWRIGHT = VK_RIGHT;
const unsigned int keyPAD0       = 0x60;
const unsigned int keyPAD1       = 0x61;
const unsigned int keyPAD2       = 0x62;
const unsigned int keyPAD3       = 0x63;
const unsigned int keyPAD4       = 0x64;
const unsigned int keyPAD5       = 0x65;
const unsigned int keyPAD6       = 0x66;
const unsigned int keyPAD7       = 0x67;
const unsigned int keyPAD8       = 0x68;
const unsigned int keyPAD9       = 0x69;
const unsigned int keyPADADD     = VK_ADD;
const unsigned int keyPADSUB     = VK_SUBTRACT;
const unsigned int keyPADMUL     = VK_MULTIPLY;
const unsigned int keyPADDIV     = VK_DIVIDE;

#else
// Define random keycodes when no display is available.
// (should rarely be used then!).
const unsigned int keyESC        = 1U;   //!< Keycode for the \c ESC key (architecture-dependent)
const unsigned int keyF1         = 2U;   //!< Keycode for the \c F1 key (architecture-dependent)
const unsigned int keyF2         = 3U;   //!< Keycode for the \c F2 key (architecture-dependent)
const unsigned int keyF3         = 4U;   //!< Keycode for the \c F3 key (architecture-dependent)
const unsigned int keyF4         = 5U;   //!< Keycode for the \c F4 key (architecture-dependent)
const unsigned int keyF5         = 6U;   //!< Keycode for the \c F5 key (architecture-dependent)
const unsigned int keyF6         = 7U;   //!< Keycode for the \c F6 key (architecture-dependent)
const unsigned int keyF7         = 8U;   //!< Keycode for the \c F7 key (architecture-dependent)
const unsigned int keyF8         = 9U;   //!< Keycode for the \c F8 key (architecture-dependent)
const unsigned int keyF9         = 10U;  //!< Keycode for the \c F9 key (architecture-dependent)
const unsigned int keyF10        = 11U;  //!< Keycode for the \c F10 key (architecture-dependent)
const unsigned int keyF11        = 12U;  //!< Keycode for the \c F11 key (architecture-dependent)
const unsigned int keyF12        = 13U;  //!< Keycode for the \c F12 key (architecture-dependent)
const unsigned int keyPAUSE      = 14U;  //!< Keycode for the \c PAUSE key (architecture-dependent)
const unsigned int key1          = 15U;  //!< Keycode for the \c 1 key (architecture-dependent)
const unsigned int key2          = 16U;  //!< Keycode for the \c 2 key (architecture-dependent)
const unsigned int key3          = 17U;  //!< Keycode for the \c 3 key (architecture-dependent)
const unsigned int key4          = 18U;  //!< Keycode for the \c 4 key (architecture-dependent)
const unsigned int key5          = 19U;  //!< Keycode for the \c 5 key (architecture-dependent)
const unsigned int key6          = 20U;  //!< Keycode for the \c 6 key (architecture-dependent)
const unsigned int key7          = 21U;  //!< Keycode for the \c 7 key (architecture-dependent)
const unsigned int key8          = 22U;  //!< Keycode for the \c 8 key (architecture-dependent)
const unsigned int key9          = 23U;  //!< Keycode for the \c 9 key (architecture-dependent)
const unsigned int key0          = 24U;  //!< Keycode for the \c 0 key (architecture-dependent)
const unsigned int keyBACKSPACE  = 25U;  //!< Keycode for the \c BACKSPACE key (architecture-dependent)
const unsigned int keyINSERT     = 26U;  //!< Keycode for the \c INSERT key (architecture-dependent)
const unsigned int keyHOME       = 27U;  //!< Keycode for the \c HOME key (architecture-dependent)
const unsigned int keyPAGEUP     = 28U;  //!< Keycode for the \c PAGEUP key (architecture-dependent)
const unsigned int keyTAB        = 29U;  //!< Keycode for the \c TAB key (architecture-dependent)
const unsigned int keyQ          = 30U;  //!< Keycode for the \c Q key (architecture-dependent)
const unsigned int keyW          = 31U;  //!< Keycode for the \c W key (architecture-dependent)
const unsigned int keyE          = 32U;  //!< Keycode for the \c E key (architecture-dependent)
const unsigned int keyR          = 33U;  //!< Keycode for the \c R key (architecture-dependent)
const unsigned int keyT          = 34U;  //!< Keycode for the \c T key (architecture-dependent)
const unsigned int keyY          = 35U;  //!< Keycode for the \c Y key (architecture-dependent)
const unsigned int keyU          = 36U;  //!< Keycode for the \c U key (architecture-dependent)
const unsigned int keyI          = 37U;  //!< Keycode for the \c I key (architecture-dependent)
const unsigned int keyO          = 38U;  //!< Keycode for the \c O key (architecture-dependent)
const unsigned int keyP          = 39U;  //!< Keycode for the \c P key (architecture-dependent)
const unsigned int keyDELETE     = 40U;  //!< Keycode for the \c DELETE key (architecture-dependent)
const unsigned int keyEND        = 41U;  //!< Keycode for the \c END key (architecture-dependent)
const unsigned int keyPAGEDOWN   = 42U;  //!< Keycode for the \c PAGEDOWN key (architecture-dependent)
const unsigned int keyCAPSLOCK   = 43U;  //!< Keycode for the \c CAPSLOCK key (architecture-dependent)
const unsigned int keyA          = 44U;  //!< Keycode for the \c A key (architecture-dependent)
const unsigned int keyS          = 45U;  //!< Keycode for the \c S key (architecture-dependent)
const unsigned int keyD          = 46U;  //!< Keycode for the \c D key (architecture-dependent)
const unsigned int keyF          = 47U;  //!< Keycode for the \c F key (architecture-dependent)
const unsigned int keyG          = 48U;  //!< Keycode for the \c G key (architecture-dependent)
const unsigned int keyH          = 49U;  //!< Keycode for the \c H key (architecture-dependent)
const unsigned int keyJ          = 50U;  //!< Keycode for the \c J key (architecture-dependent)
const unsigned int keyK          = 51U;  //!< Keycode for the \c K key (architecture-dependent)
const unsigned int keyL          = 52U;  //!< Keycode for the \c L key (architecture-dependent)
const unsigned int keyENTER      = 53U;  //!< Keycode for the \c ENTER key (architecture-dependent)
const unsigned int keySHIFTLEFT  = 54U;  //!< Keycode for the \c SHIFTLEFT key (architecture-dependent)
const unsigned int keyZ          = 55U;  //!< Keycode for the \c Z key (architecture-dependent)
const unsigned int keyX          = 56U;  //!< Keycode for the \c X key (architecture-dependent)
const unsigned int keyC          = 57U;  //!< Keycode for the \c C key (architecture-dependent)
const unsigned int keyV          = 58U;  //!< Keycode for the \c V key (architecture-dependent)
const unsigned int keyB          = 59U;  //!< Keycode for the \c B key (architecture-dependent)
const unsigned int keyN          = 60U;  //!< Keycode for the \c N key (architecture-dependent)
const unsigned int keyM          = 61U;  //!< Keycode for the \c M key (architecture-dependent)
const unsigned int keySHIFTRIGHT = 62U;  //!< Keycode for the \c SHIFTRIGHT key (architecture-dependent)
const unsigned int keyARROWUP    = 63U;  //!< Keycode for the \c ARROWUP key (architecture-dependent)
const unsigned int keyCTRLLEFT   = 64U;  //!< Keycode for the \c CTRLLEFT key (architecture-dependent)
const unsigned int keyAPPLEFT    = 65U;  //!< Keycode for the \c APPLEFT key (architecture-dependent)
const unsigned int keyALT        = 66U;  //!< Keycode for the \c ALT key (architecture-dependent)
const unsigned int keySPACE      = 67U;  //!< Keycode for the \c SPACE key (architecture-dependent)
const unsigned int keyALTGR      = 68U;  //!< Keycode for the \c ALTGR key (architecture-dependent)
const unsigned int keyAPPRIGHT   = 69U;  //!< Keycode for the \c APPRIGHT key (architecture-dependent)
const unsigned int keyMENU       = 70U;  //!< Keycode for the \c MENU key (architecture-dependent)
const unsigned int keyCTRLRIGHT  = 71U;  //!< Keycode for the \c CTRLRIGHT key (architecture-dependent)
const unsigned int keyARROWLEFT  = 72U;  //!< Keycode for the \c ARROWLEFT key (architecture-dependent)
const unsigned int keyARROWDOWN  = 73U;  //!< Keycode for the \c ARROWDOWN key (architecture-dependent)
const unsigned int keyARROWRIGHT = 74U;  //!< Keycode for the \c ARROWRIGHT key (architecture-dependent)
const unsigned int keyPAD0       = 75U;  //!< Keycode for the \c PAD0 key (architecture-dependent)
const unsigned int keyPAD1       = 76U;  //!< Keycode for the \c PAD1 key (architecture-dependent)
const unsigned int keyPAD2       = 77U;  //!< Keycode for the \c PAD2 key (architecture-dependent)
const unsigned int keyPAD3       = 78U;  //!< Keycode for the \c PAD3 key (architecture-dependent)
const unsigned int keyPAD4       = 79U;  //!< Keycode for the \c PAD4 key (architecture-dependent)
const unsigned int keyPAD5       = 80U;  //!< Keycode for the \c PAD5 key (architecture-dependent)
const unsigned int keyPAD6       = 81U;  //!< Keycode for the \c PAD6 key (architecture-dependent)
const unsigned int keyPAD7       = 82U;  //!< Keycode for the \c PAD7 key (architecture-dependent)
const unsigned int keyPAD8       = 83U;  //!< Keycode for the \c PAD8 key (architecture-dependent)
const unsigned int keyPAD9       = 84U;  //!< Keycode for the \c PAD9 key (architecture-dependent)
const unsigned int keyPADADD     = 85U;  //!< Keycode for the \c PADADD key (architecture-dependent)
const unsigned int keyPADSUB     = 86U;  //!< Keycode for the \c PADSUB key (architecture-dependent)
const unsigned int keyPADMUL     = 87U;  //!< Keycode for the \c PADMUL key (architecture-dependent)
const unsigned int keyPADDIV     = 88U;  //!< Keycode for the \c PADDDIV key (architecture-dependent)
#endif

const double PI = 3.14159265358979323846;   //!< Value of the mathematical constant PI

// Define a 10x13 binary font (small sans).
static const char *const data_font_small[] = {
"                      UwlwnwoyuwHwlwmwcwlwnw[xuwowlwmwoyuwRwlwnxcw     Mw                    (wnwnwuwpwuypwuwoy"
"ZwnwmwuwowuwmwnwnwuwowuwfwuxnwnwmwuwpwuypwuwZwnwnwtwpwtwow'y    Hw   cwnw  >{ jw %xdxZwdw_wexfwYwkw 7yowoyFx=w "
"ry    qw %wuw  !xnwkwnwoyuwfwuw[wkwnwcwowrwpwdwuwoxuwpwkwnwoyuwRwkwnwbwpwNyoyoyoyoy;wdwnxpxtxowG|!ydwnwuwowtwow"
"pxswqxlwnxnxmwDwoyoxnyoymwp{oyq{pyoy>ypwqwpwp{oyqzo{q{pzrwrwowlwqwswpwnwqwsxswpypzoyqzozq}swrwrwqwtwswswtxsxswq"
"ws}qwnwkwnydwew_wfwdwkwmwowkw(w0wmwmwGwtwdxQw swuwnwo{q{pynwp|rwtwtwqydwcwcwcwmwmxgwqwpwnzpwuwpzoyRzoyoyexnynwd"
"z\\xnxgxrwsxrwsyswowmwmwmwmwmwmwo}ryp{q{q{q{nwmwnwmwozqxswpyoyoyoyoyeyuwswrwrwrwrwrwrwrwrwqwrwmwtwnwmwnwuwpwuyp"
"wuwoyZwmwnwuwowuwmwqwkwuwowuwoxnwuxowmwnwuwpwuypwuwZwmwnwuwowuwnwowmwtw\\wuwuwqwswqwswqwswqwswEwqwtweypzr~qyIw "
"rwswewnwuwowuwozswtwuwqwtwmwnwlwowuwuwowOxpxuxqwuwowswqwswoxpwlwjwqwswqwsw<wrwowrwuwqwrwqwswrwswpwmwmwrwswrwowl"
"wqwtwownxsxsxswqwswqwswqwswrwswqwrwowpwrwrwqwtwswswswswqwswmwpwmwlwoxuxSw_wfwdwYwkw(w0wmwmwGwtwoxnwNw uwswpwuwp"
"wmwmwswq{rwrwrwtwtwrwswfydwdyZwnwtwrwqwrwswowowdwrwqxuwSwrwfwuwnwlwnw[yuw[wowtwgwswqwswqwswewuwowuwowuwowuwowuw"
"nwowuwowswqwmwmwmwjwmwnwmwowswrxswqwswqwswqwswqwswqwswrwrwqwswrwrwrwrwrwrwrwrwqwswqzpwtw #w DwPwtwtwswqwswuwuwu"
"wswswuwswqwGwqxtwf{qzr~r{qzqwrwpxowtwrw rzcwnwuwq}rwuwqwtwuwqwtwmwnwlwnynwOwowswowkwmwpwuwpwmwjwpwswqwswowmwjwi"
"wjxswsytwrwuwqwrwrwmwrwqwmwnwmwrwowlwqwuwnwnxsxswuwtwrwqwrwswrwqwswswqwjwpwrwqwswrwtwtwqwuwowuwmwowmwlwpxsx]ypz"
"oyozpypzozqznwmwowtwnwqzuyrzoypzozqwuxoypzpwswrwrwrwtwtwswrwrwrwq{owmwmwQyuwqwtwmwoxnypzqxswowowswqwswqwtxr|rwt"
"wtwqyp{q{qwswpwuwownwnwqwsxuwuxswrwrwtwtwswqwrwmwuwuwnwnwowtwpwuwuwewnzpwn{pwuwnwnxgwtxtwrwtwowtw_wuytwgynwmwlw"
"gwswpyuw[wowtwqwtwpwtwpwtwowuwmwnwuwowuwowuwowuwowuwowuwqxuwpwlwmwmwmwjwmwnwmwowrwswuwtwrwqwswqwswqwswqwswqwrwt"
"wqwswuwswrwrwrwrwrwrwrwpwuwpwswqwuwnyoyoyoyoyoyqyuyqyoyoyoyoymwqwjwmwnypzoyoyoyoyoynwnzqwswqwswqwswqwswrwrwqzqw"
"rw^}s}swtwtwswtwtwswtwtwK}rwuwe{s~t~s}rwtwqwrwpxowtwrw qwawewtwpwuwpxuwpycwlwnynwOwowswowkwpypwtwpzpzmwoypwsw[y"
"r}rymwrwtwtwtwrwuwq{qwmwrwq{q{rwm|owlwqxmwnwuwuwuwswuwtwrwqwrwswrwqwswswqylwpwrwqwswrwuwuwuwpwmwmwnwmwlwMwqwswq"
"wmwswqwswpwnwswqwswowmwowuwmwqwswswswswqwswqwswqwswqxnwswpwnwswrwrwrwtwtwrwtwqwrwmwqxlwlx]xuxrwtyqwuwlwpwtwpwmw"
"swqwtxpxowswrwqwswtwuxrwtwqwtwtwrwswrwswnwo{pwuwnxpwnwqwswtwtwswrwrwtwtwswuyuwswjwkwowpwrwowcwowuwnwnwswqxuxowo"
"wtwhwuwrwrzpwtwq}jwuwtwuw_}qyoxfwswpyuwowdyoxowtwryuwqyuwqyuwmwnwuwowuwowuwowuwowuwowuwqwt{twl{q{q{q{nwmwnwmwpz"
"twswuwtwrwqwswqwswqwswqwswqwqxpwtwtwswrwrwrwrwrwrwrwowowswqwuwkwmwmwmwmwmwowswswmwswqwswqwswqwswnwqwjwmwowswqws"
"wqwswqwswqwswqwswqwswgwtxqwswqwswqwswqwswrwrwqwswrwrw^wtwtwswqwswuwuwuwswuwswswqwHwowuwf}t~s|r}swrwrwrwqwtwpwtw"
"r~#zcwewtwoynwuxtwtwswgwlwowuwuwr}gyexowswowlwlwrwswlwqwswowowswpz^yayqwqwtwtwuwrwswrwrwrwmwrwqwmwnwsyswrwowlwq"
"wuwnwnwuwuwuwswtwuwrwqwrzqwqwszmyowpwrwpwuwqwuwuwuwpwmwmwnwlwmwPzqwswqwmwswq{pwnwswqwswowmwoxlwqwswswswswqwswqw"
"swqwswqwlxnwnwswqwtwqwuwuwuwqxowtwmwnwmwmwoytwiwtwtwswswpwtxqzpwswpxowswpwuwowuwpwswrwtwtwswtwtwrwtwqwtwtwrwswr"
"wswnwowswqwswowownwqwswtwtwswrwqwuwuwrwuyuwt~pwq~pwq~pwcwowuwozpwswowewswiwuwrwiwtwjwjwuytw\\wRwswoxuwHwtwpwswq"
"wtxqwswqxowswqwswqwswqwswqwswqwswrwtwpwlwmwmwmwjwmwnwmwowrwswtwuwrwqwswqwswqwswqwswqwqxpwtwtwswrwrwrwrwrwrwrwow"
"owswqwtwozpzpzpzpzpzr~swm{q{q{q{nwqwjwmwowswqwswqwswqwswqwswqwswqwswr}rwuwuwqwswqwswqwswqwswqwtwpwswqwtw\\wuwuw"
"qwswqwswqwswqwswJ}qxf}t~rzp{rwrwrwrwqwtwpwtwrw qwawg}owuwpwuwtwuwswuwfwlwmwmwPwnwswowmwkwr|mwqwswowowswmw^yo}oy"
"qwqwszq{rwrwrwmwrwqwmwnwqwswrwowlwqwtwownwtwtwswtwuwrwqwrwnwqwswtwkwowpwrwpwuwqwuwuwuwqwuwnwnwmwlwmwQwswqwswqwm"
"wswqwlwnwswqwswowmwowuwmwqwswswswswqwswqwswqwswqwjwownwswqwtwqwuwuwuwqxowtwnwmwmwmwpwtyhwtwtwswswpwswqwtwpwswqw"
"mwswpwuwpwtwpwswrwtwtwswtwtwrwtwqwtwtwrwswrwswnwowswqwswpwnwnwqwsxuwuxswrwpyqwqwswjwkwqwuwuwrwrwqwuwuwewowuwnwn"
"wswq{ownxuwiwtxtwrzpwtwkwjwuwtwuw\\wRwswnwuwSzpwtwowtxqwrwrwtxrxn{q{q{q{q{q{s{pwlwmwmwmwjwmwnwmwowrwswtwuwrwqws"
"wqwswqwswqwswqwrwtwqwuwswswrwrwrwrwrwrwrwowozpwswqwswqwswqwswqwswqwswqwswswswowmwmwmwmwjwqwjwmwowswqwswqwswqwsw"
"qwswqwswqwswgwuwuwqwswqwswqwswqwswqwtwpwswqwtw[yoyoyoyoyGwmwdwuwuwpxnxnyqwrwqwtwpwtwoxpw rwswSwuwmwuwpwuwtwuxsw"
"ewlwcwPwnxuxownwnwswnwlwqwswowowswnwZygygwkwswrwrwqwswrwswpwmwmwrwswrwowlwqwswpwnwqwswsxqwswqwmwswrwswqwrwowpxt"
"xowowswqwswowowlwlwmwQwswqwswqwmwswqwswpwnwswqwswowmwowtwnwqwswswswswqwswqwswqwswqwmwswpwnwswpxowswqwtwoxnwlwmw"
"mw[xuxrwtxpwswqwtwpwswqwmwswpypwtwpwswrwtwtwsxuwuxrwtwqwtwtwrwswrwswnwnwuwpwswqwmwmwswq{rwrwowowswqwkwlwoypwtwo"
"ydwowuwnwn{owmwlwgwrwfwtw^wrw6wswnwuwJwtwowtzswrwrwtzswmwswqwswqwswqwswqwswqwswswswowswqwmwmwmwjwmwnwmwowswrwsx"
"qwswqwswqwswqwswqwswrwrwqwswrxtxrxtxrxtxrxtxowowmwswqwswqwswqwswqwswqwswqwswswtxowmwswqwswqwswqwswnwqwjwmwowswq"
"wswqwswqwswqwswqwswqwswowoxtwqwswqwswqwswqwswpxowswpx Wwlwbwnxcwpwrwqzpwtwoxo|!ydwfwtwozpwsxszuxgxnxcwmwcwoxmyp"
"{q{pymwpzoyowmypymwmwjwiwkwowrwrwqws{oyqzo{qwlzrwrwowlwqwrwq{rwqwswsxpypwlyqwrwqznwoznwowswrxsxpwp}qwkwnwPzqzoy"
"ozpyowmzqwswowmwowswowqwswswswswpypzozqwlynxozpxowswrwrwpwn{owmwmwQxuxqzoxnyoypwswowpwrwqzpxuxq{qwtxq{qzpylwoyq"
"}r{qwnyuypwpwrwownydwcwcwcwnzq{rwqwpwmwkwgzHz]}U|owuw@wqwswrytwqwqyqwqwswqwswqwswqwswqwswqwuwr{ryp{q{q{q{nwmwnw"
"mwozqwsxpyoyoyoyoygwuypzpzpzpznwowmwuypzpzpzpzpzpzryuzryoyoyoyoymwqwjwmwnypwswpyoyoyoyoyfzozpzpzpzpwnzow    \\w"
"OwnwXw[w SwGz kx0x lxdx gw[w=wiw*wbyowoyGwKwowewawcwow  YwOwoz Ewjwuwdw 7w   9w  Iwnwlw    \\w      0|*y[x=wiw,"
"xWw=wKwowewawcwow  Yw  hwVx 8w   9w  Jxmwnxp" };

// Define a 26x32 font (normal sans).
static const char *const data_font_normal[] = {
"                                                      #{}~}a{|y~f{|y~}f{|}|x{}|j{|y}y{|y}g{}y~}|2y~|a{}~}f{}y~|"
"gy}|yy}|i{}~}a{}~}f{}y~}gy}|yx}N{|}|x{}|hy~|ay~|fx~|g{}y~|y{}~j{|y~|yy~}5{}~}a{}~}f{}y~}gy~}yy~}e{|y~          "
"                                                      2{}~}c{|y~f{|y~}~}h{}w~y}~|j{}y~y{}y~h{}~y}y~|2y~|c{}~}f{"
"}~y}~|hy~}yy~}hy~|c{|~}f{|~y}~|hy~}y{}y~O{}w~y}~|gy~|cy~|fy~|}~|i{|~y}y~}~}j{|y~|yy~}4{}~|c{}~}f{}~|}~}hy~}yy~}"
"ey~|  g{|}y~}                                                              J{}~|dy~|fy~y{}~|i{~}{|}y~}i{}y~y{}y"
"~i{|~}x{~}2{|y~d{|~}f{|~}yy~hy~}yy~}gy~cy~f{|~}y{}~|iy~}y{}y~P{|~}{|}y~|ey~d{}~|fy~x{}~|j{}~y{|}~}i{|y}|yy}|3{}"
"~|e{}~}f{}~|y{|~|iy}|yx}f{}~|  fy~y}~}           k{|y~|                       /{|y~|                        y{}"
"~}   Xy|e{|}|f{|}wy|5{|~|x{}~1{|}|ey|ey|wy|M{|}|e{|}|fy|wy|    g{|}|3{|y~|_{}~}g{|y~2{}~|y{}~|5{|y~^y~}g{}y~N{|"
"}|^{|}|g{|}| s{}~}_{|y~|gy~} Z{}~}_{|y~|gy~}    )y}|                       -{|y~                    Jy}|yy}|   "
"X{}y~    4{|~}y{|~}     P{|  n{|y~`{|y~fx~}3{}~x{|~|4{}~}`{}~}g{|x~}N{}~}`{|y~|gx~| sy~|`y~|g{}x~| Z{}~}`y~}g{}"
"x~|I{}y~  1{|x~|oi| r{|~|O{|d{|y}|j{|y}|u{|y}|h{|   \"{|}x~}|Ny~}g{|y~y{|~}g{|~}x{|~}i{|~l{|}y~}|s{|~}l{|}x~}|e"
"{|y~by~g{}~}b{~} S{|y~i{|}x~}|i{|y}x~|i{|y}x~y}i{|y}w~}|d{}x~kq~|i{|}w~}|m{}o~k{|}x~y}h{|}x~}| B{|}w~}L{|x~j{|s"
"~y}g{|}w~}|o{|s~y}|k{|o~n{|p~j{|}w~y}|o{|y~|ry~}k{|y~|e{|y~|j{|y~|t{|x~n{|y~|i{|x~}r{|x~}s{|x~|sy~}l{|}x~y}|l{|"
"s~}|i{|}x~y}|m{|s~}|hy}w~y}|ok~}r{}y~r{|y~|r{}y~|p{}y~vy~}t{|x~sy~}ux~rx~q{}y~|r{}y~|r{|l~l{}v~hy~|c{|v~|f{|}|L"
"{}~}M{}y~@{}~}O{|}w~R{}y~`{|y~d{|y~h{}y~`{|y~    ay}y~}h{}~}h{}y~y} Wy}x~}|O{|y}w~}| xx~}  I{|}x~}f{|x~i{|o~m{|"
"o~m{|y}x~}|f{}y~k{|m~}r{|y~|w{}y~vy~}n{|}x~y}|My}Iy}|J{}~| q{|}x~y}T{}y~r{}~}R{}w~}|j{|y~}yy~}O{|}w~} \\{|t~}h{"
"|}y~}M{|}x~}|h{|}x~}|e{|y~L{|}t~|7y}y~}f{|}x~}Uy|y}|py}p{|n{|t{|}w~}r{|y~P{|x~e{|x~e{|x~e{|x~e{|x~f{}v~|jk~|o{|"
"}w~}|m{|o~n{|o~n{|o~n{|o~j{|y~|e{|y~|e{|y~|e{|y~|k{|s~y}|m{|x~|sy~}l{|}x~y}|i{|}x~y}|i{|}x~y}|i{|}x~y}|i{|}x~y}"
"|O{|}x~y}|y{|~}s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~|r{}y~|p{|y~|b{|}x~}|h{}~}b{|y~|g{}~|}~|h{|y~}|"
"{}~iy~}yy~}i{}~|y{}~|3{}~}b{|~}fy~{}~|i{|y~|{|y~}iy~|ay~}g{}~}y~gy~}yy~}i{|y~}wy|j{|y~}y{}~hy~|b{}~}g{|~}|~}h{|"
"}y~}{|~}j{}y~y{}y~|4y~|b{}~}g{|~}{y~h{}y~y{|y~|f{|y~|k{}y~by~}y{}y~  ev~o{}k~} r{}~O{|~e{}v~l{}v~w{}w~}j{}~ Y{}"
"o~  S{|s~}Oy~}g{|y~y{|~}g{}~|x{}~|i{|~m{|y~y}y~|ty~l{}t~}f{|y~c{}~}fy~b{~} S{}~}j{}t~}kt~|j{}r~|l{|r~}f{|w~kq~|"
"j{}s~|n{}p~}m{|r~|l{|s~| D{}s~|i{|y}y~y}|hw~|k{|p~|k{|q~}q{|p~}|m{|o~n{|p~l{|p~}q{|y~|ry~}k{|y~|e{|y~|j{|y~|u{|"
"x~m{|y~|i{|w~|sw~}s{|w~sy~}n{}r~}m{|q~}l{}r~}n{|q~}k{|q~|pk~}r{}y~r{|y~|r{|y~}py~}v{}y~t{}x~|u{|y~|u{|y~}t{}y~|"
"py~}s{|y~}q{|l~l{}w~}h{}~}c{|v~|gw~}L{}~|N{}y~@{}~}P{|u~R{}y~`{|y~d{|y~h{}y~`{|y~  e{}y~  {}w~}h{}~}h{}v~ Ys~}Q"
"{|r~| yv~  K{}t~|hw~|j{|o~m{|o~n{}r~|h{}y~k{|m~}r{|y~|w{}y~vy~}p{}r~}O{}x~Jy~|K{}x~|/{~|f{}t~}Ty~|t{|y~|Ss~j{|y"
"~}yy~}i{|}v~}|j{}~w}y~ v{|}v~}|k{|t~}i{|y~}x~N{}~}|}y~|i{|y}y|}~}fy~|N{|u~y}y~|8{|~y}~}g{|y~x}y~W{|w~}q{}~}s{}x"
"~}q{|y~t{|}x|}~}s{}~|Pw~|fw~|fw~|fw~|fw~|fw~|j{|k~|q{|q~}o{|o~n{|o~n{|o~n{|o~j{|y~|e{|y~|e{|y~|e{|y~|k{|o~|o{|w"
"~sy~}n{}r~}l{}r~}l{}r~}l{}r~}l{}r~}R{}r~}|y~|s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|py~}s{|y~}o{|y~|cs~}h{"
"}~}cy~|g{|~}yy~i{|y~}w~}iy~}yy~}hy~y}~}1y~|d{|y~f{}~|{|~}i{|y~|{|y~}i{|y~b{}~}g{|~}{|~}hy~}yy~}h{|y~y}y~}|k{|y~"
"}y~}~}h{|y~c{|~}fy~y{|~|i{}~}v~|j{}y~y{}y~|4{|y~c{|~}fy~y{|~}i{}y~y{|y~|fy~|j{}y~by~}y{}y~  f{|y~{}~|p{|k~| r{~"
"}Oy~}g{}u~}n{}t~y{}u~}l{}y~} \\{}m~  T{|x~}|{y|y~|Py~}g{|y~y{|~}gy~|xy~|i{|~my~|y{|y~u{}~}m{}y~}|y{|y}f{|y~d{|y"
"~e{}~}hy|x{~}x{| Wy~|k{|y~}|{|}y~}lx~y}y~|jx~}x|}x~|m{|~}v|x~}gv~ky~s|j{}x~w|}~|nr|}y~|mx~}|{y|x~|mx~y|{|}y~| E"
"y~}x|}x~k{}q~|k{|w~}k{|y~u|}x~l{}x~}v|}y~|r{|y~u|y}x~}n{|y~q|n{|y~r|m{}x~}v|}x~|r{|y~|ry~}k{|y~|e{|y~|j{|y~|v{|"
"x~l{|y~|i{|w~}t{|w~}s{|w~}ty~}o{}x~}|{y|}x~n{|y~v|}x~|n{}x~}|{y|}x~o{|y~v|}x~}m{|x~}v|}~|pt|y~}u|q{}y~r{|y~|qx~"
"q{|y~|v{|y~|u{}x~|u{}y~|t{}y~|v{|y~}o{|y~|tx~op|}y~}l{}~}e{|y~`{|y~|h{}v~}L{}~|O{}y~@{}~}Py~}|O{}y~`{|y~d{|y~h{"
"}y~`{|y~  e{}y~ !{|y~}e{}~}e{|y~| [{}y~|x{}y~|jy}~y}|ix~|w{|}| w{}y~|  M{}y~|y{|}y~i{|w~}ix~r|m{|y~q|p{|w~}x|}x"
"~}l{|y}x~y}|n{|y~q|y~}r{|y~|w{}y~vy~}q{}x~}|{y|}x~Q{}v~Ky~|L{}v~|0{~|g{|y~}|y{|y}T{}y~t{}~}i{}~}h{}y~|x{|}P{}~y"
"}x|y}~}k{|v{}~| x{}~y}x|y}~}Qy~x{|~}J{|y~cy~g{}~|Mt~y{}~|5{|~}gy~|x{}~}U{|~}r{|y~r{}y|~}qy~|ny~t{|~}P{|w~}g{|w~"
"}g{|w~}g{|w~}g{|w~}fw~}j{}y~y|y~}r|q{}x~}v|}y~|p{|y~q|n{|y~q|n{|y~q|n{|y~q|j{|y~|e{|y~|e{|y~|e{|y~|k{|y~}u|}x~}"
"p{|w~}ty~}o{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y|}x~T{}x~}|{y|v~|r{}y~r{|y~|q{}y~r{|y~|q"
"{}y~r{|y~|q{}y~r{|y~|p{|y~|tx~n{|y~|d{}y~|x{}y~|h{}~|e{}~|f{~}x{|~}j{|}xx}hy}|yy}|h{|}y~}/y~dy~|g{|~}x{|~|j{|y}"
"|yy}|h{|~}d{|~}f{}~x{}~|iy}|yy}|iy|w~|h{}~y{|}~}f{|~}e{|~}f{}~|x{}~|j{}|y{|y}|i{|y}y{|y}2{|~}dy~f{}~|x{}~|j{|y}"
"y{|y}|g{}~|i{}y~by}|y{|y}5{|}w~}|i{|}w~}|i{|}w~}|i{|}w~}|i{|}w~}|f{}~}{y|ny~}q{}y~ r{|~O{}x~|hs~|p{|s~y|s~|n{|w"
"~} ^{}y~}|  Ix~|u{}|Py~}g{|y~y{|~}gy~wy~k{|}v~y}|s{|y~w{}~|w{|y~ly~}_{|y~d{}~}dy~|iy~}y{~}{|y~|hy}| o{|y~jx~v{}"
"y~l{|x{|y~|j{}|u{|x~d{}y~|i{}~|}y~ky~|d{|y~}]{}y~m{|y~|v{|y~}n{}y~|v{}y~ E{}u{}y~|n{|x~}|w{|}y~}|m{}y~}y~k{|y~|"
"u{|y~}n{}y~}s{|~|r{|y~|t{|x~|o{|y~|e{|y~|f{}y~}r{}~|r{|y~|ry~}k{|y~|e{|y~|j{|y~|w{}y~}k{|y~|i{|y~}y~t{}~}y~}s{|"
"v~ty~}p{}y~}t{}y~}o{|y~|v{|x~o{}y~}t{}y~}p{|y~|v{|x~mx~r{|iy~}k{}y~r{|y~|q{|y~|r{}y~u{|y~|uy~}~}u{}y~rx~vx~m{}y"
"~u{}y~|e{|y~}k{}~}dy~|a{|y~|i{}y~|{}y~| y{}y~@{}~}Py~|N{}y~0{}y~`{|y~  e{}y~ !{|y~d{}~}dy~} [y~}v{}~}ju~}jy~| n"
"{}y~  N{|y~|v{}~}j{}y~}y~i{|y~}e{|y~|gx~}t{}y~}o{|}q~|p{|y~|ry~}r{|y~|w{}y~vy~}r{}y~}t{}y~}S{}t~Ly~|M{}t~|1{~|g"
"{}y~Ly~|v{|y~|i{}~}hy~}L{|y~|t{|y~|g{|~} {{|y~|t{|y~|T{|~|wy~f{}~|ay~ey|y~7{}t~y{}~|5{|~}h{|~}vy~U{|~}r{}~|p{|~"
"}r{|~}my~ty~O{}y~}y~g{}y~}y~g{}y~}y~g{}y~}y~g{}y~}y~g{|y~}y~jy~}yy~}i{}y~}s{|~|p{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{"
"|y~|e{|y~|e{|y~|k{|y~|t{|x~}q{|v~ty~}p{}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}V{}y~}t{}x~q{}"
"y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|o{}y~u{}y~|n{|y~|e{|y~|v{}~}   A{|}|ey|e{}|wy|Py~}y|y~}   ?{}~}h{}y~ p"
"{}r~|l{}r~|l{}r~|l{}r~|l{}r~|h{}~}k{}y~qy~}1{|~}dy}P{}v~|is~|p{|r~}s~}nu~|h{|w}|k{|y}sy}|jx}|j{|y}t{|y}o{}y~|  "
"H{|y~|Gy~}g{|y~y{|~}h{|~}x{|~}l{}r~}s{|~}w{}~}w{}~|ly~}_{|y~dy~|d{}~}h{|y~|~y}~}|g{}~| o{}~}k{|y~|uy~}i{|y~|a{}"
"y~|e{|y~}j{|~}{}y~ky~|dy~}]{|y~}m{}y~tx~ny~}u{|y~|,{|X{|X{|y~|o{}y~|q{}y~my~}|y~|l{|y~|ty~}o{|x~p{|r{|y~|s{|x~o"
"{|y~|e{|y~|g{|x~p{|q{|y~|ry~}k{|y~|e{|y~|j{|y~|x{}y~}j{|y~|i{|y~|y~|uy~|y~}s{|y~|y~}uy~}q{|x~r{}y~|p{|y~|u{}y~|"
"q{|x~r{}y~|q{|y~|u{}y~|ny~}_y~}k{}y~r{|y~|py~}s{|y~}ty~}v{|y~|y~uy~}r{|y~}x{}y~|ly~}w{|y~}e{|x~j{}~}d{}~}a{|y~|"
"j{}y~|x{}y~| {{}y~@{}~}Py~|N{}y~0{}y~`{|y~  e{}y~ !{}y~d{}~}d{}~} \\{|y~u{}y~j{}x|}y~|kx~| o{|y~|  O{}~}u{|y~jy"
"~}|y~|i{|y~}f{|y~|h{}y~|rx~|q{|w~y}y~y}x~}q{|y~|ry~}r{|y~|w{}y~vy~}s{|x~r{}y~|U{}y~|y~}x~My~|N{}y~|y~|x~|2{~|gy"
"~}g{|p{}m{}y~v{}~}h{}~}h{}~}L{~}xy|}y|x{}~l{|}u~ {{~}p{}~T{|~|wy~f{}~|b{}~}g{}w~|7{}t~y{}~|5{|~}h{}~|v{}~|V{|~}"
"s{|~}o{|~}ry~n{|}~|u{}~}Oy~}|y~|hy~}|y~|hy~}|y~|hy~}|y~|hy~}|y~|hy~}|y~|l{}y~|yy~}j{|x~p{|p{|y~|e{|y~|e{|y~|e{|"
"y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|rx~q{|y~|y~}uy~}q{|x~r{}y~|r{|x~r{}y~|r{|x~r{}y~|r{|x~r{}y~|r{|x~r{}y~|q{|}q{|"
"}p{|x~s{}x~|r{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|ny~}w{|y~}m{|s~}|l{|y~u{|y~    8{|w{|y~}  _{} G{}y~ r{|"
"x~|w{|}y~|o{|x~|w{|}y~|o{|x~|w{|}y~|o{|x~|w{|}y~|o{|x~|w{|}y~|i{}~|jy~|s{|y~|1y~}d{~|Q{|t~is~|p{}i~}os~j{|s~|m{"
"|y~sy~|jw~j{|y~|u{}y~p{|y~|  Gx~Fy~}g{|y~y{|~}h{}~}x{}~}m{|y~}{|~x{|}s{|~}w{}~}x{|~}ky~}_{|y~e{|y~c{|y~f{}x~}|e"
"{}~| oy~|k{}y~t{}y~i{|y~|a{|y~|dy~|jy~|{}y~ky~|e{|y~|]{}y~|m{}y~ty~}o{|y~|ty~}/{|}~}Xy~}|[{|y~|p{}y~|o{}y~o{|y~"
"|{y~}l{|y~|ty~}o{}y~|f{|y~|r{}y~|p{|y~|e{|y~|g{}y~|e{|y~|ry~}k{|y~|e{|y~|j{|y~|y{}y~}i{|y~|i{|y~|}~}v{|y~{y~}s{"
"|y~|}y~uy~}q{}y~|qx~p{|y~|u{}y~|q{}y~|qx~q{|y~|u{}y~|o{|y~|_y~}k{}y~r{|y~|p{}y~s{}y~|t{}y~v{|~}{y~|w{|y~|q{}y~|"
"{|y~}k{|y~|xx~dx~|j{}~}d{|y~a{|y~|k{}y~|v{}y~|9{|y}x~y}j{}y~y{}x~}|h{|}x~y}|j{}x~}|{}~}k{|}x~}|j{|s~|i{}x~}|{}~"
"}n{}y~y{}x~}|h{|y~d{|y~h{}y~u{|y~}j{|y~m{}y~y{}x~}w{|}y~}|p{}y~y{}x~}|i{|}x~}|k{}y~y{}x~}|i{}x~}|{}~}k{}y~y{}x~"
"k{|}w~y}|k{|r~l{}~}t{}~}oy~}s{}y~r{}~}v{}y~}v{}~}r{|y~|u{|y~|oy~}s{}y~n{}p~h{}y~d{}~}d{}~} t{}x~}|y{|~}n{|y~u{}"
"~}e{}y~k{|w~y}|g{|}w~y}l{}y~y{}x~}|n{}~}|s{}y~iy~}i{}~}t{}~}p{|y~|r{}y~n{|y}y{}y~}lm~p{}y~x{|y~x{|y~|k{}w~}|j{|"
"}q~|q{}n~ny~|ty~|l{|y~|{y~}h{|y~}g{|y~|hy~}q{|y~}qx~}y{}y~y{|x~|r{|y~|ry~}r{|y~|w{}y~vy~}s{}y~|qx~V{|y~|{y~y|y~"
"}Ny~|O{|y~|{y~|{y~}Ny~}e{|}w~}|jy~}h{|y~r{}~}my~|x{|y~|h{}~}h{|y~}Ny}x{}u~|yy}n{}y~w}y~ y}y{}v~}|xy}T{~}x{|~}f{"
"}~|c{|~}fx|y}|Q{}~}t{}~}ns~y{}~|5{|~}h{}~|v{}~|V{|~}sy~n{|~}s{}~|p{}x~}u{|y~f{|y~|h{|y~|{y~}i{|y~|{y~}i{|y~|{y~"
"}i{|y~|{y~}i{|y~|{y~}i{|y~|{y~}ly~}xy~}j{}y~|d{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|r{|y~}r{|y~|"
"}y~uy~}q{}y~|qx~r{}y~|qx~r{}y~|qx~r{}y~|qx~r{}y~|qx~qy~}s{|y~}q{}y~|t{}~}x~r{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}"
"y~r{|y~|n{|y~|xx~l{|q~}m{}y~w{|w~l{|y}x~y}i{|y}x~y}i{|y}x~y}i{|y}x~y}i{|y}x~y}i{|y}x~y}n{|y}x~y}w{|}x~}|l{|}x~y"
"}|j{|}x~}|h{|}x~}|h{|}x~}|h{|}x~}|g{|y~d{|y~d{|y~d{|y~e{|}v~|l{}y~y{}x~}|i{|}x~}|h{|}x~}|h{|}x~}|h{|}x~}|h{|}x~"
"}|g{|x~f{|}x~}|{}~|o{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}oy~}s{}y~n{}y~y{}x~}|my~}s{}y~;y~}xy~|y{|y~|py~}s{|y"
"~|py~}s{|y~|py~}s{|y~|py~}s{|y~|j{}~|j{}y~sy~}1y~}d{|~Q{|s~}j{}t~o{|i~}p{}s~}kx~}y|}x~m{|y~sy~|k{|w~|jy~}uy~}py"
"~}  Fy~}Fy~}g{|y~y{|~}m{|k~}q{}y~y{|~n{|~}w{}~|xy~j{}y~|`{|y~e{}~}by~|g{|x~}d{}~| p{|y~jy~}t{}y~i{|y~|a{|y~|e{|"
"y~|k{}~}y{}y~ky~|{|g{}y~\\x~l{|y~|v{|y~|o{|y~|tx~i{}y~d{}y~a{|}w~}Xv~}|^x~p{|y~l{}~}p{}y~y{|y~|m{|y~|ty~}ox~e{|"
"y~|qy~}p{|y~|e{|y~|gx~d{|y~|ry~}k{|y~|e{|y~|j{|y~|{}y~}h{|y~|i{|y~y|y~v{}~}{y~}s{|y~|{y~}vy~}qx~p{}y~|q{|y~|u{|"
"y~|qx~p{}y~|r{|y~|u{}y~|ny~}_y~}k{}y~r{|y~|p{|y~|ty~}s{}y~|w{}~|{}~|w{|y~|py~}{x~i{}y~y{}y~|e{}y~|i{}~}cy~|b{|y"
"~|l{}y~|t{}y~|;{|r~|l{}y~|t~|j{}s~|m{|t~|}~}l{}s~|l{|s~|k{|t~|}~}n{}y~|t~|i{|y~d{|y~h{}y~v{}y~}i{|y~m{}y~|t~y{}"
"u~}q{}y~|t~|l{|s~}l{}y~|t~|l{|t~|}~}k{}y~|v~l{|r~k{|s~}l{}~}t{}~}o{}y~sy~}r{|y~v{}x~vy~}q{}y~|w{|y~}n{}y~sy~}n{"
"|p~h{}y~d{}~}d{}~} v{|t~|{}~|n{|y~u{}~}e{|y~|k{|t~|j{}s~|m{}y~|t~|o{}x~|ty~}ix~i{}~}t{}~}py~}q{|y~|p{|y~}{}v~|n"
"m~p{}y~x{|y~x{|y~|ls~|l{|o~|q{}n~o{|y~|t{}~}l{}y~y{}y~|h{}y~}h{|y~|i{|y~|p{}y~r{}y~|x{}y~x{|x~r{|y~|ry~}r{|y~|w"
"{}y~vy~}sx~p{}y~|p{}b{}|yy~|{|}b{}|hy~|i{|}s{}|ly|yy~|y{}My~}g{|r~k{|y~|gx~|}x~}|}y~|m{}y~xy~}g{}~}g{}x~|Q{|~|y"
"y~}|yx|y{|~|p{|~}w{|y~gy|w{|<{|~|y{}~}x|y~|y{|~|U{}y~y}y~e{}~|d{|y~a{}~Q{}~}t{}~}n{}t~y{}~|5{|~}h{}~|v{}~|m{|v{"
"|k{|~}t{}~|n{|~}t{|~}ox|}y~v{}~|f{|y~|h{}y~y{|y~|j{}y~y{|y~|j{}y~y{|y~|j{}y~y{|y~|j{}y~y{|y~|j{}y~y{}y~m{|y~|xy"
"~}jx~c{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|qx~r{|y~|{y~}vy~}qx~p{}y~|sx~p{}y~|sx~p{}y~|sx~p{}y~"
"|sx~p{}y~|r{|y~}u{|x~px~t{}~}{}y~|s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|m{}y~y{}y~|l{|y~v|}x~}n{}y~x{}y~|"
"k{|r~|l{|r~|l{|r~|l{|r~|l{|r~|l{|r~|q{|r~|{}s~n{}s~|l{}s~|k{}s~|k{}s~|k{}s~|i{|y~d{|y~d{|y~d{|y~g{|r~l{}y~|t~|l"
"{|s~}k{|s~}k{|s~}k{|s~}k{|s~}h{|x~h{|q~|n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}o{}y~sy~}n{}y~|t~|n{}y~sy~}<{}~"
"}wy~|x{|y~q{}~}q{|y~q{}~}{~}w{|~y|y~q{}~}t{|~y|y~q{}~}q{|y~j{}~|j{|y~|u{|y~|<q|}y~w|p{|y}uy}Qq~}k{|u~}o{|i~|q{|"
"q~}m{}y~uy~}n{|y~sy~|k{}w~|j{}y~v{|y~|q{|y~  H{}o~My~}fy|xy|m{|k~}q{}~}y{|~n{|y~wy~|y{}~|ix~_y|ey~|by~}i{|}~}~}"
"y~}f{}~| p{|~}jy~}t{|y~|j{|y~|a{}y~f{|}y~}k{|y~x{}y~kt~}|ky~}{|w~}|e{|y~|kx~|x{|y~}n{|y~|tx~i{}y~d{}y~d{|}v~}|q"
"k|p{|}w~}|a{}y~|p{}~|w{|}y~}|{y|xy~|qy~}xy~}m{|y~|u{|y~|p{|y~}e{|y~|qx~p{|y~|e{|y~|h{|y~}d{|y~|ry~}k{|y~|e{|y~|"
"j{|y~|}y~}g{|y~|i{|y~|{y~|wy~|{y~}s{|y~|{}y~vy~}r{|y~}p{|y~|q{|y~|u{}y~|r{|y~}p{|y~|r{|y~|u{}y~mx~}`y~}k{}y~r{|"
"y~|oy~}u{|y~|s{|y~|wy~|{|~}w{}y~o{|v~|hy~}|y~}e{}y~}h{}~}c{}~}b{|y~|m{}y~|r{|y~|<{|}y|x{|}y~l{}w~|y{|x~|lx~}|yy"
"|}|mx~|y{|}x~}mx~y|y{|x~iy~|h{|x~|y{|}x~}n{}w~|y{|x~i{|y~d{|y~h{}y~w{}y~|h{|y~m{}w~|y{|y~}|~}|{|}y~|r{}w~|y{|x~"
"lx~|y{|}y~}m{}w~|y{|x~|mx~|y{|}x~}k{}w~w|ly~}|xy|}i{}y~g{}~}t{}~}o{|y~|u{|y~|r{|y~|ww~vy~|px~wx~m{|y~|u{|y~|f{|"
"y~}h{}y~d{}~}d{}~}6{|}x~|x{}x~|o{|y~}|{|}y~{y~m{|y~v{|y~|dy~|l{}~}x{|x~|l{}y~}|yy|}|m{}w~|y{|x~n{|}~}u{|y~|j{|x"
"~|j{}~}t{}~}q{|y~|py~}q{|x~y|y~y|x~ny|y~}w|}y~}|p{}y~x{|y~x{|y~|mx~|y{|x~|n{|x~|x{}x~y|pu|y~}v|o{|y~s{}y~ly~}xy"
"~}g{}y~|i{|y~|i{}y~o{}y~|sx~w{}y~w{}y~|s{|y~|ry~}r{|y~|w{}y~w{|y~}t{|y~}p{|y~|qy~}_y~|`{|y~|iy~|j{|y~}u{|y~|iy~"
"|Jy~}h{|x~y|~|{|}k{|y~|fp~|ky~}{|y~f{}~}h{}~y}y~}|Sy}y{}~}qy}p{|~}w{|y~h{|~|x{}~<y}x{}~}x{|~}xy}T{|}y~}d{}~|e{|"
"~}`{}~|R{}~}t{}~}n{}t~y{}~|5{|~}h{|~}vy~l{|~|xy}l{|~}u{|~}m{|~}ty~|k{}~|x{|~}e{|y~|hy~}xy~}jy~}xy~}jy~}xy~}jy~}"
"xy~}jy~}xy~}jy~}xy~|n{}y~wy~}k{|y~}c{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|q{}y~r{|y~|{}y~vy~}r{|"
"y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|q{|y~}w{|x~p{|y~}u{|~}y{|y~|s{}y~r{|y~|q{}y~r{|y~|q{}y"
"~r{|y~|q{}y~r{|y~|ly~}|y~}k{|y~|ux~n{}y~y{|y~|j{|}y|x{|}y~l{|}y|x{|}y~l{|}y|x{|}y~l{|}y|x{|}y~l{|}y|x{|}y~l{|}y"
"|x{|}y~q{|}y|x{|}v~|x{|y~}px~}|yy|}|mx~y|y{|x~lx~y|y{|x~lx~y|y{|x~lx~y|y{|x~i{|y~d{|y~d{|y~d{|y~gx~|x{|y~}m{}w~"
"|y{|x~lx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}i{|x~hx~|y{|}y~}m{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~"
"}t{}~}o{|y~|u{|y~|n{}w~|y{|x~|o{|y~|u{|y~|={|y~vy~|w{}~|s{|y~o{}~|s{|y~{}y~}y{|y~}{}~|s{|y~t{|y~}{}~|s{|y~o{}~|"
"ky~|iy~}u{}y~;k~}qw~u{~|R{}p~|k{}w~}mi~q{|o~|ny~|u{}y~n{|y~sy~|ky~}y~}j{|y~|w{}y~p{}~}  Hx}y~t}|My~}M{|y~x{|~}l"
"{}y~y{|~m{}~}y{}~}y{|~}i{|w~I{|y~|b{}y~j{}~}|{~}{|y~|h{}~| p{}~|jy~}t{|y~|j{|y~|b{|y~}j{}u~}jy~|x{}y~kr~}ly~y}t"
"~}f{}y~i{}t~|ly~}u{|x~|j{}y~d{}y~f{}v~}|nk~}n{|}w~}|e{}y~|p{|~}w{|u~y}~x{|~}r{|y~|x{}y~m{|y~|xy|}y~}o{|y~|e{|y~"
"|q{}y~p{|y~r|m{|y~s|o{|y~|d{|y~q|y~}k{|y~|e{|y~|j{|v~}f{|y~|i{|y~|{}~}x{|~}yy~}s{|y~|yy~}wy~}r{|y~|p{|y~}q{|y~|"
"ux~q{|y~|p{|y~}r{|y~|v{|y~}m{|v~}y|ey~}k{}y~r{|y~|o{}y~u{}y~qy~}x{|y~y{|y~wy~}n{}x~}g{|v~e{|y~}g{}~}c{|y~b{|y~|"
" o{}~}m{}x~ux~m{}y~|f{}y~u{}y~}n{}y~|uy~}jy~|h{}y~u{}y~}n{}x~v{|y~|j{|y~d{|y~h{}y~x{}y~|g{|y~m{}x~v{}x~|vy~}r{}"
"x~v{|y~|n{}y~|v{}y~|n{}x~ux~n{}y~u{}y~}k{}x~h{|y~a{}y~g{}~}t{}~}ny~}u{}y~py~|x{|y~}~|x{|y~o{|y~}y{}y~|l{}~}u{}~"
"}ex~g{}y~d{}~}d{}~}6y~y}y~|{}y~}y~}p{}y~vy~}y~m{|y~x{|}x~c{}~}m{|y~u{}y~l{}~}e{}x~v{|y~|n{|y~u{}~}i{}x~}j{}~}t{"
"}~}q{}y~o{}y~q{}y~|{|y~y{|y~}my~|w{|y~|o{}y~x{|y~x{|y~|n{}y~ux~n{}y~u{}y~|iy~|j{|n~m{|y~|x{}y~f{}y~|j{|y~|i{}y~"
"o{|y~|t{|y~}w{}y~w{|y~}s{|y~|ry~}qy~}w{}y~w{|y~|t{|y~|{r~y|y~}rx~|_y~|_{}y~|jy~|k{|x~s{}y~|jy~|Jx|h{}y~|y{~|h{|"
"y~|f{|y~}|y{}y~|n{|u~{u~|j{}~}i{|~}y{|}y~}T{~|yy~p{|~p{|~}wx~i{|y~|y{}y~ok|X{~|x{}~}x{|~}x{|~?k~}m{}~}_y~|R{}~}"
"t{}~}mt~y{}~|ix|J{|~}gy~|x{}~}l{|y~|y{}~}m{|~}uy~|u{|t{|~}u{}~}j{}~|xy~cy|h{|y~|x{}y~k{|y~|x{}y~k{|y~|x{}y~k{|y"
"~|x{}y~k{|y~|x{}y~k{|y~|x{}y~ny~}wy~}r|t{|y~|c{|y~r|m{|y~r|m{|y~r|m{|y~r|i{|y~|e{|y~|e{|y~|e{|y~|k{|y~|q{}y~|s{"
"|y~|yy~}wy~}r{|y~|p{|y~}t{|y~|p{|y~}t{|y~|p{|y~}t{|y~|p{|y~}t{|y~|p{|y~}p{|y~}y{|x~o{|y~|v{|y~wy~}s{}y~r{|y~|q{"
"}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|l{|v~j{|y~|u{}y~|o{}y~y{|y~`{}~}d{}~}d{}~}d{}~}d{}~}d{}~}i{}x~u{|y~|r{}y~|f{}y~|"
"uy~}n{}y~|uy~}n{}y~|uy~}n{}y~|uy~}j{|y~d{|y~d{|y~d{|y~h{}y~|v{|y~|n{}x~v{|y~|n{}y~|v{}y~|n{}y~|v{}y~|n{}y~|v{}y"
"~|n{}y~|v{}y~|n{}y~|v{}y~|ix|i{}y~|w{|x~|n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}u{}~}m{}x~ux~n{}~}u{}~}<{"
"|~}vy~|w{|~}s{|~}o{|~}s{|~}y{}y~}|y~}y{|~}s{|~}u{|y~}y{|~}s{|~}o{|~}ky~|i{}y~uy~};k~}q{|{y~|w{}~R{|n~o{}o~}|r{|"
"k~}qm~|oy~|u{|y~n{|y~sy~|l{|y~|}y~iy~}wy~}p{}~}  F{|y~|Fy~}M{}~}x{}~}l{|y~}y|~lu~xy~|xx}|q{|y~|x~ty|S{|y~a{}y~j"
"{}|x{~}x{}|h{}~| py~j{|y~|t{|y~|j{|y~|bx~i{}v~}|k{}~}w{}y~k{}y|x{|x~}mw~}|y{|x~|gy~}h{}u~}l{}y~|v{}x~|jx|dx|i{|"
"}w~}|kk~}l{|}v~}|i{}y~|o{}~|wy~}x{}x~wy~rx~w{|y~|n{|q~|n{|y~|e{|y~|q{}y~|q{|p~}n{|q~o{|y~|tu|q{|m~}k{|y~|e{|y~|"
"j{|v~e{|y~|i{|y~|yy~xy~|yy~}s{|y~|y{}y~|xy~}r{|y~|oy~}q{|y~|w{|x~}q{|y~|oy~}r{|y~v|}y~}k{|}t~}gy~}k{}y~r{|y~|o{"
"|y~}vy~}q{}y~x{|~}xy~|y{|y~|n{|x~e{}x~|ex~f{}~}by~|c{|y~| o{|y~m{}y~|u{|y~|ny~}ey~}u{|y~}ny~|t{}y~jy~|hy~}u{|y~"
"}n{}y~|u{}~}j{|y~d{|y~h{}y~y{}y~|f{|y~m{}y~|v{|x~u{}y~r{}y~|u{}~}ny~}ty~}n{}y~|u{|y~|oy~}u{|y~}k{}y~|h{|y~a{}y~"
"g{}~}t{}~}n{}y~uy~}p{}~}x{}~}|~}x{}~}n{|y~y|y~}k{|y~uy~|f{}y~f{}~}d{}~}d{}y~7{}~x{|y~|~}x{}~py~}v{}x~}m{|y~{|v~"
"|i{}y~}|{}~}my~|ty~}m{}~}e{}y~|u{}~}my~|vy~|j{|y~}y~j{}~}t{}~}qx~o{|y~|ry~}y{|y~x{}y~my~|w{|y~|o{}y~x{|y~x{|y~|"
"ny~|u{|y~|oy~}ty~}iy~|j{|n~mx~w{|y~|g{|y~}j{|y~|i{}y~o{|y~|t{|y~|w{}y~vy~}s{|y~|ry~}qx~w{}y~w{}y~|t{|y~|{r~|{y~"
"}sx~|^y~|^{}y~|ky~|l{|x~q{}y~|ky~|5{|y~|x{~|h{|y~|f{}~}v{|~}mw}v~w}|j{}~}i{}~|w{|y~}U{~y{|y~p{|~ox~y}~}y~j{}y~|"
"y{}y~nk~}Y{~w{}~}y{|}~|x{|~?k~}n{}y~v|ix}|}y~}Q{}~}t{}~}m{|u~y{}~|iy~}Ly|}~}y|i{|y~x}y~j{}y~|y{}y~n{|~}v{|~}v{|"
"y~}u{|~}v{|y~y{}w~}wx|{|}y~x{}~|uy~}Wx~w{|y~|lx~w{|y~|lx~w{|y~|lx~w{|y~|lx~w{|y~|l{}y~w{|y~|p{}y~|wo~t{|y~|c{|p"
"~}n{|p~}n{|p~}n{|p~}j{|y~|e{|y~|e{|y~|e{|y~|mq~u{}y~|s{|y~|y{}y~|xy~}r{|y~|oy~}t{|y~|oy~}t{|y~|oy~}t{|y~|oy~}t{"
"|y~|oy~}o{|y~}|x~n{|y~|vy~|wy~}s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|k{}x~|j{|y~|u{|y~|o{}y~y{|y~|a{|y~d{"
"|y~d{|y~d{|y~d{|y~d{|y~i{|y~|t{}~}ry~}ey~|t{}y~ny~|t{}y~ny~|t{}y~ny~|t{}y~j{|y~d{|y~d{|y~d{|y~hy~}ty~}n{}y~|u{}"
"~}ny~}ty~}ny~}ty~}ny~}ty~}ny~}ty~}ny~}ty~}Ty~}w{|~}y~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{|y~uy~|m{}y~|u{"
"|y~|o{|y~uy~|<{}~u|y~}w|{y~s{}~n|{y~s{}~|x{}w~}wy~s{}~|v{|y~}wy~s{}~|vy~}vy~ky~|i{|y~|w{|y~|4{|y~}i{}~}w{~}Rm~}"
"qk~|r{}l~q{|m~|p{|y~sy~|o{|y~sy~|l{}y~{|y~|j{}y~x{|y~|p{}i~  V{|y~|F{}~}M{}~|x{}~|k{}v~}|m{|y}|x{}~}y{|v~}s{|y~"
"|{|x~v{|y~S{}y~a{|y~e{~}jt|y~}u| w{|~}j{|y~|t{|y~|j{|y~|cx~|hw|}y~|m{|y~v{}y~cx~|nx~}ux~h{|y~|j{|y~}|{y|x~m{|x~"
"|y{|}w~|={}w~}|E{|}v~|l{|y~|ny~w{}~}v{}y~wy~s{|y~|vy~}n{|q~}|o{|y~|e{|y~|q{}y~p{|p~}n{|q~o{|y~|u{|u~}r{|m~}k{|y"
"~|e{|y~|j{|y~}x~f{|y~|i{|y~|y{}~|{|y~xy~}s{|y~|xy~}xy~}r{|y~|oy~}q{|q~}p{|y~|oy~}r{|r~}h{|y}u~|iy~}k{}y~r{|y~|n"
"x~w{|y~|q{}y~x{}~|x{}~|y{|y~|nw~|ey~}e{}y~|f{}~}b{}~}c{|y~| v{|y}t~m{}y~sy~|o{|y~|f{|y~|ty~}o{|y~|t{|y~jy~|i{|y"
"~|ty~}n{}y~t{}~}j{|y~d{|y~h{}y~{x~|e{|y~m{}y~ty~}u{|y~r{}y~t{}~}o{|y~|t{}y~n{}y~sy~|p{|y~|ty~}k{}y~g{|y~}b{}y~g"
"{}~}t{}~}n{|y~|w{|y~o{|y~x{}~y|y~xy~}m{}w~}iy~|w{}y~f{}y~|g{|y~|d{}~}d{|y~}jy}y~}|t{|}X{~}w{|y~}v{~|r{|y~|v{|x~"
"|m{|y~{|v~}|ku~|y~}n{|y~|t{}y~m{|y~}f{}y~t{}~}m{}y~w{}y~i{}y~{y~}k{}~}t{}~}qy~}ny~}s{|y~|y{|y~x{|y~my~|w{|y~|o{"
"}y~x{|y~x{|y~|o{|y~sy~|p{|y~|t{}y~iy~|j{|y~s|}y~n{|y~}vy~}gx~|j{|y~|i{}y~o{|y~|t{|y~|w{}y~vy~}s{|y~|ry~}q{}y~|x"
"{}y~x{|y~}s{|y~|{r|yy~}tx~}l|ly~|mk|x~|ly~|m{|x~o|x~|ly~|5{}y~w{~|j{}r~}ky~|uy~i{|x~}e{}~}i{}~}v{|y~V{|~y{|y~o{"
"~|o{}x~|{y}k{}y~|y{}~}mk~}Z{|~w{}u~|v{~|@t|y~}t|n{}t~i{|}x~y}P{}~}t{}~}k{|}x~y{}~|iy~}Lt~|i{|}x~}h{|y~|y{}y~|rt"
"~|yy~ux~}wt~|y{}~|{|~}y|}y~x{}v~}|y{|y~u{}y~}m{|y}i{|y~|vy~}m{|y~|vy~}m{|y~|vy~}m{|y~|vy~}m{|y~|vy~}ly~|vy~}py~"
"}vo~t{|y~|c{|p~}n{|p~}n{|p~}n{|p~}j{|y~|e{|y~|e{|y~|e{|y~|m{}s~}u{}y~|s{|y~|xy~}xy~}r{|y~|oy~}t{|y~|oy~}t{|y~|o"
"y~}t{|y~|oy~}t{|y~|oy~}n{|v~m{|y~|wy~|vy~}s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|jy~}i{|y~|u{}y~|o{}y~xx~|"
"i{|y}t~k{|y}t~k{|y}t~k{|y}t~k{|y}t~k{|y}t~p{|y}t~s{|y~s{|y~|f{|y~|t{|y~o{|y~|t{|y~o{|y~|t{|y~o{|y~|t{|y~j{|y~d{"
"|y~d{|y~d{|y~i{|y~|t{}~}n{}y~t{}~}o{|y~|t{}y~o{|y~|t{}y~o{|y~|t{}y~o{|y~|t{}y~o{|y~|t{}y~pk~}q{|y~|w{~}{}y~n{}~"
"}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}my~|w{}y~l{}y~sy~|ny~|w{}y~;{}~|}p~{y~s{}~|}p~{y~s{}~|w{}x~vy~s{}~|w{|y~}vy"
"~s{}~|vy~}vy~ky~|h{}~}w{}y~3y~}h{|y~x{|~|S{|l~r{}k~}qm~|p{}o~}o{|y~sy~|o{|y~sy~|ly~}yy~}j{|y~|y{|y~o{}i~  X{|y}"
"y~u}K{}~}My~|xy~i{|}u~}i{|y~y{|y~|{|y~|t{}~}x{|x~w{|y~S{}y~a{|y~|f{~}jk~} x{}~}iy~}t{|y~|j{|y~|d{}y~|b{}y~|ny~|"
"v{}y~c{|y~}nx~|u{}y~|ix~j{|y~|v{|y~}m{|t~y}y~|=x~}?{|x~}l{}y~m{~}wy~|v{|y~w{}~s{}y~u{}y~n{|y~|v{|}y~|p{|y~|e{|y"
"~|q{}y~p{|y~|e{|y~|h{|y~|u{|u~}r{|y~|ry~}k{|y~|e{|y~|j{|y~|}x~g{|y~|i{|y~|y{|y~{}~}xy~}s{|y~|x{|y~|yy~}r{|y~|p{"
"|y~}q{|s~}|o{|y~|p{|y~}r{|q~|ey|w~iy~}k{}y~r{|y~|n{|y~|x{}y~p{|y~|yy~|x{}~}y{}y~n{}v~ey~}f{}y~|e{}~}b{|~}c{|y~|"
" w{}q~m{}y~sy~}o{|y~e{|y~s{}~}o{|n~jy~|i{|y~s{}~}n{}y~t{}~}j{|y~d{|y~h{}v~c{|y~m{}y~ty~|u{|y~r{}y~t{}~}o{|y~s{}"
"y~n{}y~sy~}p{|y~s{}~}k{}y~f{}w~}|f{}y~g{}~}t{}~}m{}~}w{}~}o{|y~|yy~yy~xy~|lw~h{}y~wy~}g{}y~|i{}w~}c{}~}c{|w~}o{"
"|s~}w|}~}X{~|vy~|vy}r{|y~tx~l{|y~w{|}x~|m{}y~x{}x~|n{|y~s{}y~l{|}v~j{}y~t{}~}m{|y~|xy~}j{|y~|{}y~k{}~}t{}~}qy~}"
"vy~|vy~}s{|y~x{|y~x{|y~|ny~|w{|y~|o{}y~x{|y~x{|y~|o{|y~sy~}p{|y~s{}y~iy~|j{|y~s{}y~n{}y~u{}y~h{}y~|i{|y~|i{}y~|"
"p{}y~s{|y~}w{}y~w{|y~}s{|y~|ry~}px~x{}y~x{}y~|s{|y~|p{|y~}u{}h~ly~|m{}h~ly~|mg~ly~|J{}~}i{}y~w{~|j{}r~}ky~ty~|i"
"x~d{}~}i{}y~|vy~|W{|~y{|y~o{~|X{}y~xy~}^{|~}Z{|~w{}~}|}~}u{~|9{}~| v{}~}t{}~}hy~y{}~|iy~} s{|y~}y{}y~|st|y{}~|v"
"{}~|~}wt|y{|~}sy~|wx|v{}~|vy}|~}m{|y~i{}y~u{}y~m{}y~u{}y~m{}y~u{}y~m{}y~u{}y~m{}y~u{}y~m{}y~u{}y~q{|y~|vy~}k{|y"
"~|c{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|q{}y~|s{|y~|x{|y~|yy~}r{|y~|p{|y~}t{|y~|p{|y~}t{|y~|p{|"
"y~}t{|y~|p{|y~}t{|y~|p{|y~}m{}x~|m{|y~|x{}~|v{|y~}s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|jy~}i{|y~|ux~n{}y"
"~x{|x~}k{}q~l{}q~l{}q~l{}q~l{}q~l{}q~q{}f~s{|y~e{|n~o{|n~o{|n~o{|n~j{|y~d{|y~d{|y~d{|y~i{|y~s{}y~n{}y~t{}~}o{|y"
"~s{}y~o{|y~s{}y~o{|y~s{}y~o{|y~s{}y~o{|y~s{}y~pk~}q{|y~wy~y{}y~n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}m{}y~wy~"
"}l{}y~sy~}n{}y~wy~};{}~|}q~}{y~s{}~|}q~}{y~s{}~|x{|w~}wy~s{}~|x{|y~}uy~s{}~|vy~}vy~ky~g{|y~|xy~|4{}y~fy~|yy}R{|"
"l~ri~po~|n{}p~n{|y~sy~|o{|y~sy~|m{|y~|y{}y~iy~}y{}~}o{}~}  H{}r~}K{}~}N{|y~x{|y~f{|~}w~j{}~|y{}~}x{|y~ty~|w{|x~"
"x{}~}S{}y~a{|y~|f{|ik~}T{}u~|Ly~|iy~}t{|y~|j{|y~|e{}y~|`y~}o{}~}u{}y~by~}nx~t{|y~|j{|y~}jy~}t{}y~k{}x~}|{}y~<v~"
"}|hk|g{|}w~}l{}~}n{|~}wy~ty~wy~sy~}t|y~|o{|y~|t{}y~p{|y~}e{|y~|qx~p{|y~|e{|y~|h{|y~}py~}r{|y~|ry~}k{|y~|e{|y~|j"
"{|y~|{}y~}h{|y~|i{|y~|xy~|y~|xy~}s{|y~|wy~}yy~}r{|y~}p{|y~|q{|y~w|k{|y~}p{|y~|r{|y~|w{}x~bx~|jy~}k{}y~r{|y~|my~"
"}xy~}oy~}{|y~w{|y~yy~}o{|y~}{y~}fy~}g{|y~}d{}~}ay~c{|y~| x{}y~}|w{|y~m{}y~sy~}o{|y~e{}y~s{}~}o{|n~jy~|i{}y~s{}~"
"}n{}y~t{}~}j{|y~d{|y~h{}w~}c{|y~m{}y~ty~|u{|y~r{}y~t{}~}o{}y~s{}y~n{}y~sy~}p{}y~s{}~}k{}y~e{|u~}h{}y~g{}~}t{}~}"
"m{|y~wy~|ny~}{|~}y{}~|{|y~k{}y~}h{|y~|y{|y~|h{|y~}h{}w~|c{}~}c{|}x~}oy~}x|}r~|X{~|v{}~|v{~}r{}y~ty~}l{|y~t{}y~n"
"{|y~|wx~|n{|y~s{}y~l{|u~j{}y~t{}~}ly~}y{|y~|j{}y~y{|y~|l{}~}t{}~}r{|y~}vy~|vy~}s{}y~x{|y~x{|y~|ny~|w{|y~|o{}y~x"
"{|y~x{|y~|o{}y~sy~}p{|y~s{}y~iy~|j{|y~|t{}y~ny~}u{|y~|j{|y~}h{|y~|i{|y~}px~ry~}w{}y~w{}y~|s{|y~|ry~}p{|x~|{}y~y"
"{}y~}r{|y~}p{|y~|u{|h~ly~|m{}h~ly~|m{}h~ly~|J{}~}i{}y~w{~|h{|y~|fy~|uy~mv}x~v}|Tx~|wy~U{~|yy~|q{|~or}ly~}xy~|^{"
"|~}Y{~|x{}~}y{}~}w{|~8{}~| v{}~}t{}~}hy~y{}~| yr}h{}~}y{|y~|k{|~}v{|~y|~}ny~r{}~|p{|~}v{|~{|~}m{|y~iy~}t|y~|ny~"
"}t|y~|ny~}t|y~|ny~}t|y~|ny~}t|y~|ny~}t|y~|r{}y~u|y~}k{|y~}c{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~"
"|q{}y~r{|y~|wy~}yy~}r{|y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|t{|y~}p{|y~|n{|w~}m{|y~}y{}~}u{|y~|s{}y~r{|"
"y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|jy~}i{|y~|w{|x~}n{}y~v{}x~|n{}y~}|w{|y~m{}y~}|w{|y~m{}y~}|w{|y~m{}y~}|w{|y~"
"m{}y~}|w{|y~m{}y~}|w{|y~r{}y~}|w{|n~s{|y~e{|n~o{|n~o{|n~o{|n~j{|y~d{|y~d{|y~d{|y~i{|y~s{}y~n{}y~t{}~}o{}y~s{}y~"
"o{}y~s{}y~o{}y~s{}y~o{}y~s{}y~o{}y~s{}y~pk|p{}y~x{}~|y{}y~n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}n{}~}t{}~}m{|y~|y{|y~|l"
"{}y~sy~}n{|y~|y{|y~|;{|~}vy~|w{|~}s{|~}o{|~}s{|~}y{}y~}|y~}y{|~}s{|~}y{}y~}u{|~}s{|~}vy|v{|~}ky~fy~}y{}y~9k~}n{"
"}y~y{~|R{}l~ri~p{|q~}lq~m{|y~sy~|o{|y~sy~|m{}y~x{|y~|j{}y~yy~}o{|y~  Ey~}E{|Qj~j{|~y{|y~}l{|~}xy~|wy~u{|y~|v{|x"
"~{|y~R{}y~a{|y~K{}~|M{}u~|M{|y~hy~}t{}y~i{|y~|f{}y~|_{}y~o{}n~}ey~}n{}y~t{|y~|j{}y~|jy~}t{|y~|e{}y~;{|}v~}jk~}k"
"{|}v~}j{}~}n{|~}wy~ty~wy~t{|o~}o{|y~|t{|y~|px~e{|y~|qy~}p{|y~|e{|y~|gx~py~}r{|y~|ry~}k{|y~|e{|y~|j{|y~|y{}y~}i{"
"|y~|i{|y~|x{}w~wy~}s{|y~|w{|y~|{y~}qx~p{}y~|q{|y~|gx~p{}y~|r{|y~|v{|y~}c{|y~}jy~}k{}y~r{|y~|m{}y~y{}y~|o{}y~{|~"
"}vy~{|y~|ox~y{|y~|gy~}h{|x~c{}~}a{}~|d{|y~| xy~|u{|y~m{}y~sy~}o{|y~e{|y~s{}~}o{|y~_y~|i{|y~s{}~}n{}y~t{}~}j{|y~"
"d{|y~h{}y~|y~}d{|y~m{}y~ty~|u{|y~r{}y~t{}~}o{|y~s{}y~n{}y~sy~}p{|y~s{}~}k{}y~b{|}w~i{}y~g{}~}t{}~}ly~|y{}y~m{}~"
"}{}~}y{|~}{}~}l{|w~|h{}~}y{}y~h{|y~}d{}y~|d{}~}d{|y~}|m{}t{|}x~}|V{~}w{|x~v{~|r{|y~ty~|l{|y~t{|y~|o{}y~v{}y~m{|"
"y~s{}y~m{}y~}f{}y~t{}~}l{|y~y{}~}iy~|xy~}l{}~}t{}~}qy~}vy~}vy~}s{|y~x{|y~x{|y~|ny~|w{|y~|o{}y~x{|y~x{|y~|o{}y~s"
"y~}p{|y~s{}y~iy~|j{|y~|ty~}o{|y~|ty~}k{|x~g{|y~|hx~q{|y~}r{}y~|x{}y~x{|x~r{|y~|ry~}o{}x~}x~}x~}px~p{}y~|t{}y~}]"
"y~|^{|x~oy|yy~|y{|o{}y~|q{|x~oy|yy~|y{|M{}~}i{}y~w{~|h{|y~|f{}~}v{}~}n{|n~|S{}x~|{}~}Uy}y{}~}qy}p{|r~ky~}y{|y~}"
"_{|~}Yy}x{}~}xy~|xy}8{}~| v{}~}t{}~}hy~y{}~| {{|r~iy~}y{|y~}jy~|w{|~|{|~}o{}~|s{|y~oy~v{|~|{|~}m{|y~j{|o~}o{|o~"
"}o{|o~}o{|o~}o{|o~}o{|o~}s{|p~}jx~c{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|qx~r{|y~|w{|y~|{y~}qx~p"
"{}y~|sx~p{}y~|sx~p{}y~|sx~p{}y~|sx~p{}y~|o{|x~|y~}my~}{}~}t{}y~|s{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|q{}y~r{|y~|jy~"
"}i{|q~}m{}y~u{|x~|oy~|u{|y~my~|u{|y~my~|u{|y~my~|u{|y~my~|u{|y~my~|u{|y~ry~|u{|y~h{|y~e{|y~d{|y~d{|y~d{|y~_{|y~"
"d{|y~d{|y~d{|y~i{|y~s{}y~n{}y~t{}~}o{|y~s{}y~o{|y~s{}y~o{|y~s{}y~o{|y~s{}y~o{|y~s{}y~U{|y~y{}~|x{}y~n{}~}t{}~}n"
"{}~}t{}~}n{}~}t{}~}n{}~}t{}~}l{}~}y{}y~k{}y~sy~}m{}~}y{}y~:{|y~vy~|w{}~|s{|y~o{}~|s{|y~{|y~}y{|y~}{}~|s{|y~{|y~"
"}t{}~|s{|y~o{}~|ky~f{}y~yy~}9k~}n{|y~y|~Q{|u~|y}u~r{}t~y}s~o{|s~}k{|s~|m{|y~sy~|ny~sy~ly~}wy~}j{|y~y|y~|ny~|  F"
"x~ uj~j{|~x{}y~ly~wy~|wy~u{|y~|u{|x~}~}R{|y~a{}y~K{}~| r{}~}h{}y~t{}y~i{|y~|g{}y~|^{}y~o{}n~}ey~}n{}y~t{|y~|jy~"
"}iy~}t{|y~|ey~}8{|}w~}|mk~}n{|}v~}|hx}m{~}wy~|v{|y~x{|~}t{}n~|p{|y~|t{|y~}p{}y~|f{|y~|r{}y~|p{|y~|e{|y~|g{}y~|q"
"y~}r{|y~|ry~}k{|y~|e{|y~|j{|y~|x{}y~}j{|y~|i{|y~|x{|x~}wy~}s{|y~|vy~}{y~}q{}y~|qx~p{|y~|g{}y~|qx~q{|y~|u{}y~|d{"
"|y~}jy~}k{|y~|s{}y~|m{|y~|{y~}n{}y~{}~}v{}~y|y~|p{}y~|x{}y~gy~}hx~|c{}~}a{|~}d{|y~| y{|y~t{}y~m{}y~sy~|o{|y~|f{"
"|y~|ty~}o{|y~|`y~|i{|y~|ty~}n{}y~t{}~}j{|y~d{|y~h{}y~{|x~e{|y~m{}y~ty~|u{|y~r{}y~t{}~}o{|y~|t{}y~n{}y~sy~|p{|y~"
"|ty~}k{}y~_{|y~}j{}y~g{}~}ty~}l{}y~yy~}m{|y~{y~|y{|y~{y~}m{|y~y}y~h{|y~yy~|hx~by~}d{}~}d{}y~7{}~|y{|~}|~}x{}~q{"
"|y~|v{|y~}l{|y~t{|y~|o{}~}v{}~}m{|y~|t{}y~my~|e{}y~t{}~}ky~|{y~|j{}y~w{}y~l{}~}ty~}qy~}vy~}vy~}s{|y~|y{|y~x{}y~"
"my~|w{|y~|o{|y~x{|y~x{|y~|o{}y~sy~|p{|y~|t{}~}iy~|iy~}ty~|o{}y~s{}y~|lx~|g{|y~|h{|y~}rx~px~|y{}y~y{|x~|r{|y~|ry"
"~}n{|r~}o{}y~|qx~r{}y~}^y~|_{|x~o{|y~|{y~|{}~}o{}y~|s{|x~o{|y~|{y~|{}~}Ny~}i{}y~w{~|h{|y~|f{|y~}|{|}y~|h{}y~L{|"
"v~}T{|~xy~}|yx|x{~|U{}y~y{|y~}`{|~}Y{|~x{}~}x{|y~x{~|8{}~| v{}~}ty~}hy~y{}~| `{|y~}y{|y~|j{}~}v{~}y{|~}p{|y~ry~"
"|p{}~|v{~}y{|~}mx~j{}n~|p{}n~|p{}n~|p{}n~|p{}n~|p{}n~s{}p~}j{}y~|d{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y"
"~|k{|y~|r{|y~}r{|y~|vy~}{y~}q{}y~|qx~r{}y~|qx~r{}y~|qx~r{}y~|qx~r{}y~|qx~o{|x~y{|y~}n{}y~}~}sx~r{|y~|s{}y~|q{|y"
"~|s{}y~|q{|y~|s{}y~|q{|y~|s{}y~|jy~}i{|s~}|l{}y~sy~}p{|y~t{}y~n{|y~t{}y~n{|y~t{}y~n{|y~t{}y~n{|y~t{}y~n{|y~t{}y"
"~s{|y~t{}y~|i{|y~|f{|y~|e{|y~|e{|y~|e{|y~|`{|y~d{|y~d{|y~d{|y~i{|y~|t{}y~n{}y~t{}~}o{|y~|t{}y~o{|y~|t{}y~o{|y~|"
"t{}y~o{|y~|t{}y~o{|y~|t{}y~ix|j{|y~|}~}w{}y~n{}~}ty~}n{}~}ty~}n{}~}ty~}n{}~}ty~}l{|y~yy~|k{}y~sy~|m{|y~yy~|9{}~"
"}wy~|x{|y~q{}~}q{|y~q{}~}{~}w{|~y|y~q{}~}{~}t{|y~q{}~}q{|y~k{|y~f{|y~y|y~|9x|}y~}q|m{}~x}P{}w~}{}{v~|r{|t~y|}u~"
"|n{}u~}i{|u~}l{|y~sy~|ny~|u{|y~ly~|w{}y~iy~y}y~m{|y~|  G{|y~| ry~|xy~|f{|~x{}y~m{}~|wy~|wy~ty~}t{|w~Q{|y~|b{}y~"
"K{}~| ry~|h{|y~|uy~}i{|y~|h{}y~|]x~ns|x~y|e{|y~}n{|y~|u{}y~|k{|y~|iy~}t{}y~e{}y~4{|}w~}|U{|}v~}|Ty~w{}~}v{}y~xy"
"~sy~}ry~}p{|y~|t{|y~}p{|x~p{|r{|y~|s{|x~o{|y~|e{|y~|g{|x~qy~}r{|y~|ry~}k{|y~|e{|y~|j{|y~|w{}y~}k{|y~|i{|y~|wx~|"
"wy~}s{|y~|v{|y~|y~}q{|x~r{}y~|p{|y~|g{|y~}r{}y~|q{|y~|u{|y~}d{|y~}jy~}k{|y~}sx~ky~}|y~|n{|y~|y~|v{}~y}y~p{|y~}w"
"{|y~}hy~}i{}y~|b{}~}a{|y~d{|y~| y{|y~tx~m{}y~|u{|y~|ny~}ey~}u{|y~}ny~}`y~|hy~}u{|y~}n{}y~t{}~}j{|y~d{|y~h{}y~y{"
"|x~f{|y~m{}y~ty~|u{|y~r{}y~t{}~}ny~}ty~}n{}y~|u{|y~|oy~}u{|y~}k{}y~^{}~}j{|y~g{}y~u{|y~}l{|y~y|y~|ly~|y~wy~|y~|"
"mx~yy~}hy~y|y~hx~a{}y~d{}~}d{}~}6u~y{}y~}y~|py~|v{}y~}l{|y~t{|y~|o{}~}vy~|ly~}ty~}n{|y~|e{}y~t{}~}k{}~y}y~iy~}v"
"y~|m{}y~ty~}qx~w{|x~w{|y~|ry~}y{|y~x{}~}my~|w{|y~|o{|y~x{|y~x{|y~n{}y~|u{|y~|oy~}ty~}iy~|i{}y~u{|y~ny~}s{|y~}m{"
"}y~|f{|y~|g{}y~|t{}y~|p{|w~y}y~y}x~}q{|y~|ry~}ly}x~y}|n{|x~r{}y~|q{}y~}_y~|`{|x~mx~|y~|}y~|n{}y~|u{|x~mx~|y~|}y"
"~|Ny~}i{|y~|x{~|h{|y~|fp~|i{}y~d{}~}d{|x~|S{~}x{}u~|y{}~S{}y~xy~}a{|~}X{~}y{|~|w{}~|{}~7y| u{}y~ty~}hy~y{}~| a{"
"|y~}y{|y~|j{|y~v{}~x{|~}p{}~|s{}~|p{|y~v{}~x{|~}n{}y~|jy~}ry~}py~}ry~}py~}ry~}py~}ry~}py~}ry~}py~}ry~}ty~}ty~}j"
"{|x~p{|p{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|rx~q{|y~|v{|y~|y~}q{|x~r{}y~|r{|x~r{}y~|r{|x~r{}y~"
"|r{|x~r{}y~|r{|x~r{}y~|p{|x~w{|y~}o{|w~s{}y~|r{|y~}sx~p{|y~}sx~p{|y~}sx~p{|y~}sx~iy~}i{|y~w|h{}y~s{}~}p{|y~tx~n"
"{|y~tx~n{|y~tx~n{|y~tx~n{|y~tx~n{|y~tx~s{|y~tx~}hy~}ey~}dy~}dy~}dy~}`{|y~d{|y~d{|y~d{|y~hy~}ty~}n{}y~t{}~}ny~}t"
"y~}ny~}ty~}ny~}ty~}ny~}ty~}ny~}ty~}j{|x~iy~}~}vy~}n{}y~u{|y~}n{}y~u{|y~}n{}y~u{|y~}n{}y~u{|y~}ky~y|y~j{}y~|u{|y"
"~|ly~y|y~7y~}xy~|y{|y~|py~}s{|y~|py~}s{|y~|py~}s{|y~|py~}s{|y~|k{|y~ey~y}y~6{|y~}b{|x~|O{}y~}y{}{|}y~|p{|w~}{|}"
"{}w~}l{}v~g{}w~}k{|y~sy~|n{}y~uy~}m{|y~v{|y~|j{}w~}l{}y~|  Gx~|u{}|Px|O{|y~x{|y~j{|w{|~x{}~}n{|y~v{}~|x{|y~t{}y"
"~}t{}x~Py~|by~}K{}~|dx|Jx|f{|y~fx~v{}y~h{|y~|i{}y~|f{|s{}y~}f{}y~l{|t{|x~l{}y~ux~j{}y~h{}y~|v{|x~f{|y~}hx|dx|a{"
"}v~}Xv~}|bx|m{}~|x{|y~}x{|x~{|y~|t{|y~|r{}y~p{|y~|t{}y~|o{}y~}s{|~|r{|y~|t{|x~|o{|y~|e{|y~|f{}y~}ry~}r{|y~|ry~}"
"k{|y~|e{|y~|j{|y~|v{}y~}l{|y~|i{|y~|oy~}s{|y~|uv~}p{}y~}t{}y~}o{|y~|f{}y~}t{}y~}p{|y~|t{}y~|o{}r{}y~|jy~}j{}y~|"
"u{|y~}k{}y~}y~ly~}y~u{|w~}px~u{|y~|iy~}j{}y~}a{}~}`y~|e{|y~| y{|y~|v{}x~m{}x~ux~m{}y~|f{}y~u{}y~}n{}y~|ay~|h{}y"
"~u{}y~}n{}y~t{}~}j{|y~d{|y~h{}y~x{|x~g{|y~m{}y~ty~|u{|y~r{}y~t{}~}n{}y~|v{}y~|n{}x~ux~n{}y~u{}y~}k{}y~^y~}j{|y~"
"g{|y~|v{}y~}ky~y}y~kw~}w{}w~m{}y~|y{|y~}i{}~}y~}i{}y~|a{}y~d{}~}d{}~}5{}y~}w{|y~}|o{}y~w{|w~l{|y~}u{}y~n{}~}w{}"
"y~k{}y~|v{}y~|my~|e{}y~t{}~}k{|w~}j{}y~u{}~}m{}y~|v{}y~}q{}y~|x{}~}~|x{}y~q{}y~|{|y~y{|y~|my~|w{|y~|ny~}y{|y~x{"
"}y~n{}x~ux~n{}y~|v{}y~|iy~|i{|y~}vy~}o{|y~|rx~n{|y~}e{|y~|fx~|v{}y~}n{|}q~|p{|y~|ry~}j{}y~j{}y~}t{}y~}o{}~}_y~|"
"`{|y~ks~|l{}~|u{|y~ks~|My~}hx~x{~|h{|y~|gx~|}x~}|}y~|j{}y~d{}~}c{|x~S{|~}xy|}y|x{}~|R{}~|x{}~a{|}|X{|~}p{}~| /{"
"}y~|v{}y~}hy~y{}~| a{|~|x{}~|i{}~|vr~|s{|~}s{}~|o{}~|vr~|q{}y~}j{|y~|r{}y~q{|y~|r{}y~q{|y~|r{}y~q{|y~|r{}y~q{|y"
"~|r{}y~q{|y~|r{}y~u{|y~|ty~}i{}y~}s{|~|p{|y~|e{|y~|e{|y~|e{|y~|a{|y~|e{|y~|e{|y~|e{|y~|k{|y~|t{|x~}q{|y~|uv~}p{"
"}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}p{}y~}t{}y~}p{|x~u{|y~}o{}y~}t{}y~}p{}y~|u{|y~}o{}y~|u{|y~}o{}y~|"
"u{|y~}o{}y~|u{|y~}iy~}i{|y~|e{}y~sy~}p{|y~|v{}x~n{|y~|v{}x~n{|y~|v{}x~n{|y~|v{}x~n{|y~|v{}x~n{|y~|v{}x~s{|y~|v{"
"}w~|i{}y~|f{}y~|e{}y~|e{}y~|e{}y~|a{|y~d{|y~d{|y~d{|y~h{}y~|v{}y~|n{}y~t{}~}n{}y~|v{}y~|n{}y~|v{}y~|n{}y~|v{}y~"
"|n{}y~|v{}y~|n{}y~|v{}y~|j{|x~i{}y~}v{}y~|n{|y~|v{}y~}n{|y~|v{}y~}n{|y~|v{}y~}n{|y~|v{}y~}k{}~}y~}j{}x~ux~k{}~}"
"y~}7{|y~}|{y|{|}y~|o{|y~}|w{|}y~|o{|y~}|w{|}y~|o{|y~}|w{|}y~|o{|y~}|w{|}y~|j{|y~e{|w~|6y~}`x~I{|~hx|y{|}yw|jw~|"
"f{}x~j{|y~sy~|mx~w|x~l{}~}uy~}j{}w~|k{}y~}|  I{|x~}|{y|y~|Py~}O{|~}x{|~}j{}~|y{|~{|}y~|n{}~|v{|y~x{}~}sx~}|y{|}"
"u~Q{}~}by~|K{}~|d{}y~Jy~}f{}~}f{|y~}|{|}y~}kw|y~w|m{}y~}s|my~}w|}w~e{}y~ly~}w|}x~}l{|x~|y{|x~|jy~}h{|x~}|{y|x~|"
"m{~}w|}y~}g{}y~d{}y~_{|}y~}Xy~}|_y~}m{|~}w{|u~y}w~|sx~q{|y~|q{|y~t|}y~}m{}x~}v|}y~|r{|y~u|y}x~}n{|y~q|n{|y~|e{}"
"x~}v|}x~}r{|y~|ry~}k{|y~|e{|y~|j{|y~|u{}y~}m{|y~q|r{|y~|oy~}s{|y~|u{|w~}o{}x~}|{y|}x~n{|y~|e{}x~}|{y|}x~o{|y~|t"
"{|y~}oy~}x|{y|x~}iy~}j{|x~}w|}x~j{|w~}l{}x~}tw~|q{}y~|t{}y~iy~}k{|x~o|l{}~}`{}~}e{|y~| xx~|y{|}w~m{}w~|y{|x~|lx"
"~}|yy|}|mx~|y{|}x~}m{}y~}|x{|}~}jy~|h{|x~|y{|}x~}n{}y~t{}~}j{|y~d{|y~h{}y~w{|x~h{|y~m{}y~ty~|u{|y~r{}y~t{}~}mx~"
"|y{|}y~}m{}w~|y{|x~|mx~|y{|}x~}k{}y~g{}~}|x{|}y~|j{|y~}gx~|y{|}x~}k{}w~}k{}x~}w{|x~}n{|y~|w{}y~|j{|w~|j{}y~|`{}"
"y~d{}~}d{}~} w{|y~}|{|y~}y~}m{|x~}|y{|}y~}n{|~}x{|y~|jx~|y{|}y~}l{}y~}|x{|y}m{}y~t{}~}jw~|jy~}u{|y~|n{}x~}|{|}w"
"~y|s{|x~|{|y~|~}|{}y~}px~y|y~|}y~}ly~|vy~}n{}y~|{|y~y{}y~|n{}w~|y{|x~|mx~|y{|}y~}h{}y~|i{}y~}y{|x~nx~q|}y~|ox~r"
"|m{|y~|iw|x~}x{}y~}w|o{|y}x~y}|n{|y~|ry~}j{}y~i{}x~}|{y|}x~m{|^y~|_{|iu~|j{|s{|iu~|Ly~}h{|y~}|{~|{|}mx|y~}t|o{|"
"y~r{}~}j{}y~d{}~}b{|y~|S{|~}r{}~|Py|w{}:{|~}r{}~|=k|!{}x~}|{|}w~y|jy~y{}~| ay|w{}h{|~}uv|}~}|ry~s{}~|o{|~}uv|}~"
"}|q{|y~}ix~q{|y~|rx~q{|y~|rx~q{|y~|rx~q{|y~|rx~q{|y~|r{}y~q{|y~|vx~sy~}r|q{}x~}v|}y~|p{|y~q|n{|y~q|n{|y~q|n{|y~"
"q|j{|y~|e{|y~|e{|y~|e{|y~|k{|y~}u|}x~}p{|y~|u{|w~}o{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y|}x~n{}x~}|{y"
"|}x~ox~s{|y~}pv~}|{y|}x~o{|x~}w|}x~n{|x~}w|}x~n{|x~}w|}x~n{|x~}w|}x~hy~}i{|y~|e{}y~{x|y{|}y~|ox~|y{|}w~mx~|y{|}"
"w~mx~|y{|}w~mx~|y{|}w~mx~|y{|}w~mx~|y{|}w~rx~|y{|}y~|}y~}|x{|}~}qx~}|yy|}|m{}y~}|x{|}~}m{}y~}|x{|}~}m{}y~}|x{|}"
"~}m{}y~}|x{|}~}j{|y~d{|y~d{|y~d{|y~gx~|y{|}y~}m{}y~t{}~}mx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}lx~|y{|}y~}"
"i{|x~i{|x~|y{|}y~}lx~|y{|}x~}mx~|y{|}x~}mx~|y{|}x~}mx~|y{|}x~}k{|w~|j{}w~|y{|x~|k{|w~|6{|q~|m{|q~|m{|q~|m{|q~|m"
"{|q~|i{|y~dw~5{}~_{}~}I{}~c{}~d{|y~|dy~|j{|y~sy~|m{|s~|ly~}u{}~}j{|w~i{}m~  S{|s~}Oy~}O{}~|x{}~|j{}q~}n{|~}t{}y"
"~}x~q{}s~}{|y~}R{|y~c{|y~J{}~|dx~Jy~}fy~|e{}t~}k{}q~}no~|nq~}d{}y~lq~|j{|s~|j{|y~|g{|r~|ls~}f{}y~dx~\\y|X{}|]y~"
"}ly~|w{|}y~}|{}~}|r{|y~}py~}q{|p~}k{|q~}q{|p~}|m{|o~|o{|y~|d{|p~}q{|y~|ry~}k{|y~|e{|y~|j{|y~|t{}y~}n{|o~r{|y~|o"
"y~}s{|y~|t{}x~}n{}r~}m{|y~|d{}r~}n{|y~|s{}y~|pp~}hy~}i{|r~}hw~|l{}x~}tw~|r{|y~}s{|y~}jy~}k{}l~|m{}~}`{|y~e{|y~|"
" x{|t~}|y~m{}y~|t~|j{}s~|m{|t~|}~}l{}r~}jy~|g{|t~|}~}n{}y~t{}~}j{|y~d{|y~h{}y~v{|x~i{|y~m{}y~ty~|u{|y~r{}y~t{}~"
"}m{|s~}l{}y~|t~|l{|t~|}~}k{}y~g{}r~}h{}u~k{|t~|}~}k{|w~|k{|x~|w{|x~|ny~}u{}y~iw~io~h{}y~d{}~}d{}~} v{}t~{}x~}o{"
"|q~}ly~}y|y~}i{|s~}j{}s~}m{}y~t{}~}j{}x~j{}y~sy~}n{}~}t~}x~}r{|u~|{t~o{|q~ky~|vw~}ot~}x~}m{}y~|t~|l{|s~}g{|v~j{"
"}t~|o{|k~}p{|o~|n{|y~|is~y{|t~}l{}y~k{|y~|ry~}j{}y~h{}r~}Ny~|Kw~|Lw~|Ky~}g{|r~n{|o~}n{|p{|i{}y~d{}~}ay~|R{|y~}y"
"|{y|}y~| a{|y~}y|{y|}y~|<k~}\"{}~}t~}x~}jy~y{}~| Gy~o{|~}r{}~|ty~|ny~o{|~}q{|y~}i{|y~}py~}s{|y~}py~}s{|y~}py~}s"
"{|y~}py~}s{|y~}py~}s{|y~}py~}w{|y~|so~}q{|q~}o{|o~|o{|o~|o{|o~|o{|o~|k{|y~|e{|y~|e{|y~|e{|y~|k{|o~|o{|y~|t{}x~}"
"n{}r~}l{}r~}l{}r~}l{}r~}l{}r~}n{|~q{|~p{}~y|r~}m{|r~}l{|r~}l{|r~}l{|r~}gy~}i{|y~|e{}y~{}t~}n{|t~}|y~m{|t~}|y~m{"
"|t~}|y~m{|t~}|y~m{|t~}|y~m{|t~}|y~r{|s~|y{}r~|p{}s~|l{}r~}l{}r~}l{}r~}l{}r~}j{|y~d{|y~d{|y~d{|y~fs~}l{}y~t{}~}m"
"{|s~}k{|s~}k{|s~}k{|s~}k{|s~}Rq~}k{|t~|}~}m{|t~|}~}m{|t~|}~}m{|t~|}~}jw~i{}y~|t~|iw~3{|}w~}|i{|}w~}|i{|}w~}|i{|"
"}w~}|i{|}w~}|g{|~}d{}y~} r{|~|Iy~|dy~|d{|}cy|i{|y}sy}|k{}w~}k{|y~|u{|y~ix~}gy}p~  Q{|}x~}|Ny~}Oy~wy~h{|y}v~}|my"
"~r{|x~}o{|}w~}|x{}y~}Ry~|d{}~}J{}~|dy~}Jy~}g{|y~c{|}x~}|j{}q~}no~|m{|}w~y}|c{}y~l{|y}w~y}f{}w~}hx~dy}x~y}|k{|}w"
"~}|e{}y~dy~} ry~}l{|y~c{}y~|p{}y~q{|r~}|h{|}w~}|o{|s~y}|k{|o~|o{|y~|b{|}w~y}|o{|y~|ry~}k{|y~|e{|y~|j{|y~|s{}y~}"
"o{|o~r{|y~|oy~}s{|y~|t{|x~}l{|}x~y}|l{|y~|b{|}v~}m{|y~|ry~}o{|y}w~y}|gy~}g{|}w~}|g{|x~k{|x~|t{}x~qx~q{}y~|ky~}k"
"{}l~|m{}~}_y~|f{|y~| v{}x~}|{|y~m{}y~{|}x~}|h{|}x~y}|j{}x~}|{}~}k{|}w~y}|iy~|e{}x~}|{}~}n{}y~t{}~}j{|y~d{|y~h{}"
"y~u{|x~j{|y~m{}y~ty~|u{|y~r{}y~t{}~}k{|}x~}|k{}y~{|}x~}|i{}x~}|{}~}k{}y~f{|y}w~}|fy}w~j{|}x~}y{}~}jx~}ix~ux~|o{"
"}y~t{|y~}j{|y~}io~h{}y~d{}~}d{}~} u{|}x~}|y{}y~}o{|y~|}w~}|k{|v~}f{|}x~}|h{|}w~y}|m{}y~t{}~}j{|y~|jy~}s{}y~n{}~"
"}{}x~}y{}~}|q{|}y~}|x{}x~}l{}v~}|jy~|v{|}y~}n{}s~|l{}y~{|}x~}|i{|}x~}|e{|}x~i{|}x~}m{}j~p{|o~|n{|y~|is~y{|t~}l{"
"}y~k{|y~|ry~}j{}y~f{|}x~y}|My~|Jy~|Jy~|Jy~}f{|}u~}n{|o~}O{}y~d{}~}h{}|w{}y~O{|}v~}| ]{|}v~}|:k~}\"{}~}{}x~}y{}~"
"}|jy~y{}~| H{}~|o{|~|s{|~}t{|t~|t{}~|o{|~|q{}y~h{}y~|p{}y~s{}y~|p{}y~s{}y~|p{}y~s{}y~|p{}y~s{}y~|p{}y~s{}y~|p{}"
"y~w{}y~ro~}o{|}w~}|m{|o~|o{|o~|o{|o~|o{|o~|k{|y~|e{|y~|e{|y~|e{|y~|k{|s~y}|m{|y~|t{|x~}l{|}x~y}|i{|}x~y}|i{|}x~"
"y}|i{|}x~y}|i{|}x~y}|U{|~}x{|}x~y}|j{|}w~}|i{|}w~}|i{|}w~}|i{|}w~}|fy~}i{|y~|e{}y~{|}w~}|k{}x~}|{|y~k{}x~}|{|y~"
"k{}x~}|{|y~k{}x~}|{|y~k{}x~}|{|y~k{}x~}|{|y~p{}x~}|v{|}w~y}|n{|}x~y}|j{|}w~y}|j{|}w~y}|j{|}w~y}|j{|}w~y}|i{|y~d"
"{|y~d{|y~d{|y~e{|}x~}|k{}y~t{}~}k{|}x~}|h{|}x~}|h{|}x~}|h{|}x~}|h{|}x~}|R{}~|{|}x~}|i{|}x~}y{}~}l{|}x~}y{}~}l{|"
"}x~}y{}~}l{|}x~}y{}~}j{|y~}i{}y~{|}x~}|h{|y~}  e{|~} V{|      .{|~ p{}~}dy~|1{|y~2{}~}   U{|y~ ^{}~}  ){|y~|  {"
"}y~}  6{}~}_{}~}f{|y~|  -y~}6{|y~ A{}y~Z{}~}  j{|y~I{}y~d{}~}d{}~} \\{|y~a{|}y|*{}~}j{|y~|O{}~}F{|y~K{|}y~y|j{}"
"y~     Ry~}c{|~| r{}~}h{}t~|K{| U{| '{}~}^y~y{}~|O{|~| wy|cy}|st|sy|ay~}  ^{|~|    9{|    Y{|~|    8y| Q{|y~h{}"
"y~`{|y~  d{|~}        c{|~ oy~e{}~}0{}~}2y~|   U{}~} ]{}y~|r{|y}  7{}y~  y{}y~|  7{}~}_{|y~f{|y~|  .{|y~|6{|y~ "
"A{}y~Z{}~}  j{}~}I{|y~d{}~}dy~} \\{|y~ g{}~}j{|y~|O{}~}F{|y~J{|y~h{}y~     Ry~}b{~| r{}~}h{|y}x~}|   ){}~}^y~y{"
"}~|N{}~ 'y~}  ]y~         p{~}      g{}~}h{}y~`{}~}  h{|}|{}~}        c{|~ o{}~}fy~/{}~    c{}~ [{}y~}|v{|}y~} "
" 7x~  x{}y~|  8{}v~M{|v~|  .{}y~5{}~} A{}y~Z{}~}  k{|y~|I{|y~}e{}~}e{|y~| \\{|y~ g{}~}j{|y~|O{}~}F{|y~J{|y~h{}y"
"~     Ry~}b{~| r{}~}    i{}~}*{}~| (x~uy|  e{}~|         q{}~      h{|y~|h{}y~a{|y~|  h{|y~|y~|        c{|~ ny~"
"g{}~}      M{|}q~|  9y|}y~|    1{}w~}M{|v~|  6y}|x{|}y~|6{|y~} A{}y~Z{}~}  l{|x~G{}w~}h{}~}h{}w~} [{|y~ g{}~}j{"
"|y~|O{}~}F{|y~J{|y~h{}y~     Ry~}b{~| r{}~}    i{}~}-x}y~ '{}x~w|y~|  e{}~|         qy~      i{|x~g{}y~b{|x~  f"
"{}w~                e{|y}w~}|  8{|w~}     ({|n~}  m{}s~}7{|w~ @{}y~Z{}~}  nv~|F{|y}~}h{}~}h{}~y}| Z{|y~ g{}~}j{"
"|y~|O{}~}F{|y~J{|y~h{}y~     Rx| W{}~}    i{}~}-{}y~}| &{}s~|  i{|~y}y~         t{|~y}y~      kv~|g{}y~dv~|  ex"
"}                   s{|y~}|     '{|n~}  m{|y}w~}|6{|y~} ?{}y~Z{}~}  nx~}|-{}~} B{|y~ g{}~}j{|y~|O{}~}F{|y~J{|y~"
"h{}y~           q{}~}  -{|}x~}|  f{}y~}|         t{|x~}|      kx~}|f{}y~dx~}|                                  "
" :{}~}                                     I{" };

// Define a 52x64 font (large sans).
static const char *const data_font_large[] = {
"                                                                                                               "
" -{|                                                                                                           "
"                                    [{|x}|Dw}|Pw}| @{}v~} C{|w}|Ew}|Pv}| xv|Ev|Pu|  kv|Dw|P{|v}  6{|w}|E{|x}|P{"
"|w}| pw}|                                                                                                      "
"                           G{|w~}F{}w~P{}v~}Q{}w~}|w{|x~X{|v~vv~|U{|r~| D{}w~F{}w~P{}u~S{|v~|wv~}V{}w~|G{|w~|Q{"
"|u~|Sv~}w{}w~}\"{|}x~}|v{|x~W{}w~|F{}w~Q{|u~}Q{}x~}|v{|x~X{}w~}w{|v~ G{}w~F{}w~|Q{}u~Rv~|w{}w~}O{}w~           "
"                                                                                                               "
"       E{|w~|H{}w~P{}t~}Ss~}|y{}x~X{|v~vv~|V{|p~ Cw~}H{|w~|Q{|t~}T{|v~|wv~}U{}w~Gw~}Q{|s~|Tv~}w{}w~}#{|s~}|{|x~"
"}V{}w~|H{}w~Ps~}St~}w{}y~}X{}w~}w{|v~ Fw~}H{|w~|Q{|t~}Sv~|w{}w~}P{|w~|                                         "
"                                                                                        D{|w~|J{|w~|Q{|x~}{w~|U"
"{}l~}X{|v~vv~|Vw~}x{}x~} D{|w~|J{|w~|Q{|w~{}x~}U{|v~|wv~}T{}x~}Iw~}Pw~y|w~Tv~}w{}w~}#k~|U{}w~I{|w~|Q{}x~|{}x~|U"
"{}r~|{|x~}X{}w~}w{|v~ Ew~|Iw~}Pw~|}x~}Tv~|w{}w~}Q{|w~|    M{|                                                  "
"                                                                           q{}w~Jw~|Q{|x~}xw~Ux~}y{|}t~}W{|v~vv"
"~|W{|x~|v{|x~| D{|w~|Kw~}Pw~x{}x~|V{|v~|wv~}S{}x~}K{}x~}P{}x~|y{|x~}Uv~}w{}w~}${|x~|y{|s~}S{}x~}K{|w~|Q{}x~}xw~"
"Ux~}{|}r~W{}w~}w{|v~ E{|w~|K{}x~}Pw~|y{}x~|Uv~|w{}w~}Qw~|    O{}v~}                                            "
"                                                                                 s{}x~}L{}x~|Pw~vw~W{|x~v{|}w~}"
"V{|v~vv~|W{}y~}tx~} C{|w~L{}x~}P{}x~|w{}x~|W{|v~|wv~}R{}x~|M{}x~}P{}x~|w{|x~}Vv~}w{}w~}${|x~v{|}w~|Q{}x~}Lw~|Q{"
"|x~}vw~W{|x~w{|t~|W{}w~}w{|v~ D{|w~L{|x~}P{}x~|w{}x~|Vv~|w{}w~}R{}x~}    P{|r~|                      Y{}w~|    "
"                                                                                                  A{}x~|N{}x~}P"
"{}x~u{|x~}\"v|vv|V{}y~}t{}y~} B{}x~}N{|x~}P{}x~|u{}x~Vv|vv|P{}x~|O{|x~}P{}x~|u{|x~}Wv|uv| D{}x~|N{}x~|Q{|x~}tx~"
"}X{|x~u{|}y~}|Vu|vv| C{|x~}N{|w~P{|x~|u{}x~Vv|vu|S{|x~}    Op~|                      Zv~|                      "
"                         ;v~                                                u{|v~      6{|y}|N{|y}|P{|x}s{|x} I"
"{}y~}t{}y~} Aw|Nw|Ow|sw|    Qw|Nw|Pw|rx|  5{|x}N{|x}O{|y}|s{|y}| {{|y}| Dv|@v|Rv| C{}x~}x{|w~ Hu|@v|Rw| yv}@v}R"
"{|w}  lv|@v|Rv|  8v}@v}|S{|w} m{}w~|        E{|y~x}|                                               ;{|w~}      "
"                                          vv~|         J{}y~}t{}y~}               e{}w~}B{|w~}Rv~| Dx~|v{|x~| H"
"v~A{}w~|S{|w~} {{|w~}B{}w~|S{|v~| Ay|sx|Y{}w~|B{|w~}Rv~  8{|w~}B{|w~}Rv~| o{|w~}     ?y}~}|  *x~             J{"
"|y~|  b{}x~|T{|x~}                            L{|q~} y{}q~| H{|w~} xw~} `{|w~| {{|}t~)w~}Cv~Lv~Tw~}Dv~        G"
"{|x}w~}Tw~|U{|v~y}|  1{|y}v~y}|   cv~y}     p{|y}x~y}|             {{v|vv|      3{}w~|         I{|x~|v{|x~|    "
"      %{|   5{|y}w~y}|U{}w~|Cv~R{}v~}Q{|}y~}|ux~|Y{|v~|wv~}W{|x~t{}y~} H{|w~}C{}w~|Ru~|S{}w~}w{|v~W{}w~|D{|w~}R"
"t~S{|v~vv~|X{|v~}K{}w~}ux~X{}w~C{|w~}R{}v~}Q{|}y~}|ux~|Y{|v~vv~| J{|w~}D{|w~}R{}u~Rv~|w{}w~}N{|w~}Zw~}Hv~}w{}w~"
"}    N{|u~}  ,{|y~} Ix|Tx|kw|        Ru|  6{|y~|Yv|fx}|Zu| o{|w~Rw~|Hx|   Xu| vt|Ns| =t| xt|Ot|   [u|  ds|  kr|"
"    Qt| ut| ts|    S{|q~} y{}q~| G{}w~| yw~} `{|w~|!{}q~)w~}Cv~Lv~Tw~}Dv~        I{|r~}Tw~|U{|r~}  5{|}o~| yr| "
" ps~}     t{|p~|  kt|  is| s{|y} r{|x}| rx}|  bt|  lu|S{|v~vv~|!{|y}w~y}|  :{|l~|Qx| u{|y}w~}|Q{|x}w~y}|K{|w~| "
" 9y|y}w~|O{|y}w~}|)y|x}dw~|hy|x}dw~|ly|x}y~y}|e{}x~|   6w~}x{}x~} us|      lt|Nt|Nt|Nt|Nt| ut|p{}~|   9{|}o~|V{"
"}w~D{}w~R{|t~|S{|u~}vx~|Y{|v~|wv~}W{}y~}t{|x~ G{|w~}E{|w~}R{}t~S{}w~}w{|v~V{}w~E{|w~}R{}t~}T{|v~vv~|W{|v~}s{|y}"
"X{}u~}w{|x~Ww~}Dv~R{|t~|S{|u~}w{|x~X{|v~vv~| I{}w~|Ew~}R{|t~}Sv~|w{}w~}Nw~}Yw~}Hv~}w{}w~}    O{|s~|cW}  i{}y~|"
"\"{|}L{|u~}|Z{|}v~}|p{}u~}V{|}  /g|    ({}r~}| v~}R{}x~}vw~}R{|x}|t{|x}|V{|y~|\\{|}t~|i{}x~|]{}q~}|O{}x~}Iw~|R{|"
"w~Hx~  *{|w~V{|}s~}|Sy|y}v~}T{|}q~}|V{|y}p~}|L{|u~}\\{|g~}T{}q~y}|_{}c~}[{|}q~}|U{|}r~}|   b{|}q~| w{}v~}X{}k~y"
"}|R{|y}p~}|b{}m~x}y|W{}c~|`{}e~Y{|}o~}|a{}w~}hv~|Y{}w~}M{}w~}W{}w~}k{|u~}b{}w~}V{}t~|h{}t~|h{}u~}jv~^{|}p~}|Z{}"
"m~y}|U{|}p~}|\\{}m~y}y|S{|}o~}y|bZ~g{|v~h{}w~}i{|v~|d{|v~|rv~|l{|v~}kv~|p{|v~|i{}v~g{}v~fv~}g\\~]{|q~}Uw~}I{}q~"
"|P{|w}| w{}w~ yw~} `{|w~|\"o~)w~}Cv~Lv~Tw~}Dv~        J{|q~}Tw~|U{|q~}  7{}l~}\"y}p~y}  sr~}     v{}n~}R{}v~}V{"
"}c~|_{}d~}^{|}p~}|R{|v~Y{}^~|iv~}r{|v~qv~}a{|}p~}| x{}x~} s{}w~ s{}w~|  f{|}r~}|-{}w~|i{|v~({|q~}|W{|v~vv~|Ty|u"
"}y|U{|}o~|  ly|u}y|U{|l~|T{|}v~}| {|}p~|T{}p~}|N{|w~} yy|}m~} N{|r~|P{}q~|0{|y}t~|f{}x~}l{|y}t~|f{}x~}l{}p~}h{}"
"x~}%{}v~}N{}v~}N{}v~}N{}v~}N{}v~}Q{|p~W{}\\~}b{|y}p~}|^{}c~|a{}c~|a{}c~|a{}c~|X{}w~}M{}w~}M{}w~}M{}w~}Z{|m~x}y|"
"Z{}u~}jv~^{|}p~}|V{|}p~}|V{|}p~}|V{|}p~}|V{|}p~}|\"{|}q~y}t{}x~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}g{}"
"v~fv~}c{}w~}J{|l~}Vw~}F{}w~|R{}x~|w~Ss~}x{|x~X{|v~|wv~}W{}y~}t{|x~ F{|w~|Fw~}R{|x~y}x~}T{}w~}w{|v~U{}x~}Fw~}R{|"
"w~{w~|U{|v~vv~|V{}v~|x{|}v~Y{|s~}x{}x~W{|w~}F{}w~Qw~|w~Ss~}x{|x~X{|v~vv~| H{}w~F{}w~Qw~|}x~|Tv~|w{}w~}O{}w~Xw~}"
"Hv~}w{}w~}    P{|q~c{}Y~}  ix~!y~|N{}r~}\\{}r~}s{|q~|Y{|y~}  5{|}e~}    *{}m~|\"v~}R{}x~}vw~}Rw~|tw~|V{|y~|]{}q"
"~}k{|w~^{|l~|Q{}x~}J{}w~P{}x~}Ix~  *{}x~}W{}n~|Zy|}p~}W{|}k~}Z{}i~|Nt~}\\{|g~}V{}l~|`{}c~}\\{}l~|X{}n~}   e{|l~"
"|Ty|y}u~y}|Rt~X{}g~}V{|}j~}d{}g~}|Z{}c~|`{}e~\\{|}i~}|d{}w~}hv~|Y{}w~}M{}w~}W{}w~}l{|u~}a{}w~}V{}t~}i{|s~|h{}t~"
"|kv~`{|k~}|\\{}i~}|Z{|k~}|^{}i~}|W{|h~}dZ~g{|v~h{}w~}hv~}d{}v~q{}w~}l{}u~kv~|o{}v~j{|v~|fv~}h{}v~f\\~]{|v~u}U{}"
"w~Iu}v~|Qt~| w{}x~} {{w~} `{|w~|#{}o~)w~}Cv~Lv~Tw~}Dv~    Ov|    s~x}|Tw~|U{|x}s~|  9{}j~}%{}j~|  uq~|     x{}l"
"~}St~V{}c~|_{}d~}`{|}k~|T{|v~Y{}^~|iv~}r{|v~qv~}c{|k~}| {}v~} t{}w~ t{}u~|  i{|l~-v~i{}w~|Xw}|R{|l~X{|v~vv~|W{|"
"}o~}|X{|m~|  p{|}o~}|X{|l~|U{}r~}!{|n~}U{}n~|Ow~} {{|}j~} N{|r~|R{|n~}1{|r~|g{|w~k{|r~|g{|w~k{}n~iw~$t~Nt~Nt~Nt"
"~Nt~P{|r~V[~}d{|}j~}`{}c~|a{}c~|a{}c~|a{}c~|X{}w~}M{}w~}M{}w~}M{}w~}Z{|g~}|]{}t~|kv~`{|k~}|Z{|k~}|Z{|k~}|Z{|k~}"
"|Z{|k~}|&{|k~}w{|w~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}fv~}h{}v~b{}w~}K{}j~}W{|w~|H{|w~|R{|x~}{|x~}U{|"
"x~}|w~}|{}x~X{|v~|wv~}W{|x~t{}y~} E{}w~G{}x~}Qw~|{}x~|U{}w~}w{|v~Tw~}H{}w~Q{}x~|{|x~}U{|v~vv~|U{}v~|}t~}Y{}x~|{"
"}w~y|x~}V{|w~|H{|w~|R{}x~|{|x~}U{}x~}|w~}{|x~}X{|v~vv~| G{}x~}H{|w~|R{}x~|yw~Tv~|w{}w~}P{|w~|Xw~}Hv~}w{}w~}    "
"P{}w~y|w~|d{|Y~|  j{|y~}\"{}x~Oo~}_{|o~}u{|o~}Zw~|  8{}b~}    ,{|j~}#v~}R{}x~}vw~}Rw~sw~U{|y~|^{}o~}lw~|_{}k~|Q"
"{}x~}Jw~|P{|w~|Jx~  *w~|Xk~|[m~}X{}h~}[{}h~}P{}t~}\\{|g~}X{|j~|`{}c~}^{|i~}[{|j~   gi~|X{|}l~}|V{}t~|Y{}e~|Y{}f"
"~}f{}d~}\\{}c~|`{}e~]{}e~}|f{}w~}hv~|Y{}w~}M{}w~}W{}w~}m{|u~|`{}w~}V{}s~|j{}s~|h{}t~}kv~b{|g~}]{}g~}]{|g~}_{}g~"
"}Y{}f~dZ~g{|v~h{}w~}h{}v~dv~}q{}w~}lt~|m{|v~mv~}kv~}e{|v~|j{|v~|f\\~]{|w~}O{|w~|D{|w~|Rr~| ww~} w~} `{|w~|${|v~"
"}|#w~}Cv~Lv~Tw~}Dv~    Ov~   !{|v~}Nw~|O{|v~}  :{|u~}|w{|}v~|'{}i~|  r{|}v~}     y{}v~}|x{|}v~}U{}t~|W{}c~|_{}d"
"~}a{}g~|V{|v~Y{}^~|iv~}r{|v~qv~}e{|g~}\"{}t~} u{}w~ u{}s~| >y~}P{|k~-{|w~}k{|w~}Ww~|S{|k~X{|v~vv~|Y{|}k~}|Z{|y~"
"}y|xy|}w~|  s{|}k~}|Z{|l~|V{}p~}\"{|y~}|w{|}w~|V{|}|u{|v~P{}x~} {{}h~} N{|~y}y|}x~|S{|v~}|y{|}w~}2{|w~y}x~|g{}x"
"~|k{|w~y}x~|g{}x~|kx}|w{|}w~}k{}x~}%{}t~|P{}t~|P{}t~|P{}t~|P{}t~|P{}t~}W{|[~}e{}f~}b{}c~|a{}c~|a{}c~|a{}c~|X{}w"
"~}M{}w~}M{}w~}M{}w~}Z{|d~}|`{}t~}kv~b{|g~}]{|g~}]{|g~}]{|g~}]{|g~}){|g~|{|w~|h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f"
"{|v~h{}w~}f{|v~|j{|v~|b{}w~}L{|u~}|w{|}v~|W{|w~|Iw~}Qw~x{}x~|V{}y~}x{}s~|X{|v~|wv~}Vx~}v{|x~| D{}x~}I{}w~Q{}x~|"
"xw~U{}w~}w{|v~T{|w~|J{|w~Q{|x~}x{|x~|V{|v~vv~|T{}q~}|Wx~|x{}s~T{|w~I{|w~|R{|x~}x{}x~|Vx~}x{}s~|X{|v~vv~| Fw~}J{"
"|w~|R{|x~}x{|x~}Uv~|w{}w~}Q{|w~|Ww~}Hv~}w{}w~}    Pw~}y{|x~}cY~  i{}y~|#{|w~}Qm~|`m~}w{|m~|\\{}v~|  ;{}`~}    -"
"{|r~x}t~}$v~}R{}x~}vw~}S{|w~t{|x~}U{|y~|_{|w~}w{}w~|n{}x~}_{|t~w}u~|Q{}x~}K{}w~N{}x~}Jx~  +{|w~Xs~y}s~|\\m~}X{}"
"f~\\{}g~}R{|s~}\\{|g~}Y{|i~|`{}c~|_{|s~w}s~}]{|s~x}s~   hr~}r~|[{|f~}Xs~}Y{}d~|\\{|c~}g{}b~|^{}c~|`{}e~_{|a~|g{"
"}w~}hv~|Y{}w~}M{}w~}W{}w~}n{|u~|_{}w~}V{}s~}jr~|h{}s~|lv~c{|p~}q~}^{}f~}_{|p~}q~}`{}e~[{}q~}p~dZ~g{|v~h{}w~}h{|"
"v~|f{|v~p{|v~m{|t~}m{}w~}m{|v~|m{}v~c{}v~jv~}e\\~]{|w~}Nw~}D{|w~|Sp~| ww~|!w~} `{|w~|${}w~}!w~}Cv~Lv~Tw~}Dv~   "
" Ov~   !{}w~}Mw~|N{|v~  :{}v~|s{|v~V{|t}|V{|t~s}w~|  p{|v~     {{|v~|t{|v~|Vs~}W{}c~|_{}d~}c{|d~|W{|v~Y{}^~|iv~"
"}r{|v~qv~}f{|p~}q~}${}r~} v{}w~ v{}q~| ?y~}Ps~x}u~,v~k{}w~|Ww~|Su~}v|}w~X{|v~vv~|Z{}v~}y|wy|}v~}[{|}q{}x~}  t{}"
"v~}y|wy|}v~}&{}w~|x{|w~}#y|r{}x~}Kw~|R{|w~ {{}p~}v|x~} H{}x~|S{}w~t{}w~|3x|x{}x~|h{|x~}j{|}|x{}x~|h{|x~}`{|w~l{"
"|w~$s~}Ps~}Ps~}Ps~}Ps~}Pr~W{}[~}g{|c~}c{}c~|a{}c~|a{}c~|a{}c~|X{}w~}M{}w~}M{}w~}M{}w~}Z{|b~}a{}s~|lv~c{|p~}q~}_"
"{|p~}q~}_{|p~}q~}_{|p~}q~}_{|p~}q~}+{|p~}q~}w~|g{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}e{}v~jv~}a{}w~}Lu~r{"
"|v~V{|w~J{}x~}Q{}x~|w{}x~Vx~|w{}u~}Vv|vv|U{}x~}x|}w~ Bw~|K{|w~|R{|x~}w{|x~}Vu|vv|S{|w~K{|w~|Qx~}v{}x~Uv|vv|T{|}"
"t~}|Tx~|w{|u~|S{}x~}Jw~}Qw~vw~Vx~|w{}u~}Vv|vv| Dw~|Kw~|Qw~v{}x~|Vv|vv|Pw~|Vw~}Hv|uv| G{|t}|P{|t}|P{|t}|P{|t}|P{"
"|t}|Lw~|xw~c{|[~}  iy~}\"u~|S{|l~a{}l~|x{}l~]{}t~  ={|^~}    .{|u~}|u{|}w~}$v~}R{}x~}vw~}S{}x~}t{}x~}Xy|y}y~y}x"
"|cw~}u{}w~o{|w~^u~}t{|}y~|Q{}x~}Kw~|N{|w~|T{}sx~s{}  4{}x~}Y{}v~}|v{}u~\\m~}X{}v~y}|wy|s~]{}x~}x|v{|}t~}Sr~}\\{"
"|v~k|Z{|t~}|v{|y}y~|`h|u~^t~|u{|}u~|^u~}|v{|}v~}   iv~y|v{|t~]{|o~y}p~|[{|r~|Z{}w~}q|}s~]{|s~}|t{|}u~}g{}w~}r|y"
"}q~}_{}w~}h|_{}w~}j|`{|s~}|s{|}t~|g{}w~}hv~|Y{}w~}M{}w~}W{}w~}o{}u~|^{}w~}V{}r~k{|r~|h{}r~lv~d{|t~}|uy|s~_{}w~}"
"s|y}t~}a{|t~}|uy|s~a{}w~}s|y}s~]{}u~}|ty|}v~dn|}v~}n|g{|v~h{}w~}gv~}f{}w~}ov~|n{|t~}mv~|l{}v~|o{|v~|bv~}l{}v~dc"
"|u~}]{|w~}N{}w~D{|w~|T{}o~| x{|w~!w~} `{|w~|${}w~ w~} >w~}Dv~    Ov~   !{}w~|Mw~|M{}w~  :v~|q{}w~|Xp~}X{}v~|p{|"
"}|  o{}w~|     v~|r{|v~W{|r~|X{}v~}i|^{}w~}h|d{|s~}y|xy|}s~}[{|y}u~y}y|]{}w~}h|v~|iv~}r{|v~qv~}g{|t~}|uy|s~&{}p"
"~} w{}w~ w{}o~| @y~}Q{}v~}|u{|}y~,{|w~}m{|w~}Vw~|T{|v~|s{|}~({|w~}|o{|}w~|P{}x~|  w{|w~}|o{|}w~|(x~}tw~ rw~K{}x"
"~|Rw~ {{}o~}w{|x~} H{}x~|T{|w~r{}x~}-{}x~|hw~|d{}x~|hw~|_{}x~|mw~|%{|r~|R{|r~|R{|r~|R{|r~|R{|r~|R{}r~|Y{|v~|y{|"
"v~}h|h{|s~}|t{|}u~}c{}w~}h|`{}w~}h|`{}w~}h|`{}w~}h|W{}w~}M{}w~}M{}w~}M{}w~}Z{|v~r|x}q~b{}r~lv~d{|t~}|uy|s~a{|t~"
"}|uy|s~a{|t~}|uy|s~a{|t~}|uy|s~a{|t~}|uy|s~-{|t~}|u{|}q~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}dv~}l{}v~`"
"{}w~}M{|v~p{}w~|V{}x~}L{}x~}Q{|x~|ux~}Wx~|v{|w~} {{}q~| Aw~|Lw~|Qw~u{}x~| y{|x~}Lw~|Q{}x~tx~}#{|}r~}Rx~u{|}y~}|"
"Q{}x~}L{}x~}Q{}x~|v{|x~}Wx~|v{}w~}  j{|w~L{}x~}Q{}x~|u{}x~ x{}x~}Uw~}  b{|}p~}|V{|}p~}|V{|}p~}|V{|}p~}|V{|}p~}|"
"P{|w~|xx|av~|fv~|  j{|y~|#{}t~Sk~|c{|k~}y{|k~}_{|s~}  ?{}t~}y|     u{|u~|p{}y~}$v~}R{}x~}vw~}Sw~|tw~|[{|}m~}|h{"
"|w~sw~|p{}x~|_{}v~|q{|}|Q{}x~}L{}w~Lw~}U{}y~|ux~u{|y~}U{|x}|  `w~|Z{|v~}s{|v~}]w~y}y|{}w~}X{}x~|p{|u~|^y}|n{|u~"
"|U{}x~y}w~}\\{|w~}K{|u~}o{}|Mv~|_{}v~}q{|u~_{}v~}r{|v~|   jy~}|qu~|_{}t~}y|s{|}t~}\\{}w~}w~}Z{}w~}o{|u~}_{|t~|n"
"{|}x~}g{}w~}n{|}t~}`{}w~}L{}w~}P{|t~}m{|}w~|g{}w~}hv~|Y{}w~}M{}w~}W{}w~}p{}u~|]{}w~}V{}w~}w~|l{}r~|h{}r~|mv~e{|"
"u~}|p{|t~`{}w~}q{|}u~|c{|u~}|p{|t~b{}w~}p{}u~|_{|u~|n{|}y~W{|v~|Z{|v~h{}w~}g{|v~fv~|o{}w~}n{}x~}w~mv~|kv~}ov~}a"
"{|v~|n{|v~|M{}v~}\\{|w~}N{|w~|E{|w~|U{}v~}{|u~| x{|x~}\"w~} `{|w~|$v~ w~} >w~}Dv~    Ov~   !v~Lw~|M{}w~|  <{|w~"
"}p{|w~}Xn~|Zv~  _{|v~    !{|w~}p{}w~}X{}w~}w~}W{}v~|M{}w~}R{|t~|p{|t~|_{|}l~}|`{}w~}hv~|iv~}r{|v~qv~}h{|u~}|p{|"
"t~({}n~} x{}w~ x{}m~| Ay~}R{|v~}p{}+{}w~|nv~Uw~|T{}w~| x{|w~|k{|w~|Q{|x~|  x{|w~|k{|w~|*{|x~rx~|R{|w}Fw~Kw~|S{}"
"x~| {|n~}w{|x~} H{}x~|T{}x~}qw~|.{}x~|i{}x~}c{}x~|i{}x~}^{}x~|n{}x~}${}w~}w~}R{}w~}w~}R{}w~}w~}R{}w~}w~}R{}w~}w"
"~}Rv~|w~}Y{}w~}x{|v~U{|t~|n{|}x~}c{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~n{|}s~c{}r~|mv~e{|u~}|p{|"
"t~c{|u~}|p{|t~c{|u~}|p{|t~c{|u~}|p{|t~c{|u~}|p{|t~/{|u~}|p{}t~}e{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}d{|v"
"~|n{|v~|`{}w~}M{}w~}ow~}U{}x~|N{|w~Px~}t{|x~|Xx|sy| w{}s~| @{|w~M{}x~|Q{}x~|tw~ x{}x~}N{}x~|Q{|x~|t{|x~|&{}t~}v"
"~} t{}x~|N{|x~}Q{|x~}t{}x~|Xx|sy|  g{|x~}N{|x~}Q{|x~}sx~} {{|x~}Tw~}  d{|j~|Z{|j~|Z{|j~|Z{|j~|Z{|j~|R{|w~Z{}w~}"
"g{}w~} Ay|J{}y~#{|s~}Tk~}c{}j~|{}j~_q~|  A{}u~}     q{}v~|n{}~}$v~}R{}x~}vw~}Sw~t{|w~\\{|h~|i{}x~}s{}x~}q{|x~}^"
"v~|C{}x~}Lw~}L{}w~V{|v~|wx~w{|v~|V{}w~  a{|w~Yv~}q{|v~|^{}y|u{}w~}Xy}|m{|u~M{|v~}V{|w~|}w~}\\{|w~}Ku~|?{|v~^u~o"
"{}v~|a{|v~}p{}v~   j{~|nv~}`u~}|l{|}u~]v~{v~Z{}w~}mu~_u~}j{|y~}g{}w~}l{|}u~}a{}w~}L{}w~}Q{|u~}i{|}y~|g{}w~}hv~|"
"Y{}w~}M{}w~}W{}w~}q{}u~|\\{}w~}V{}w~|w~}lw~|v~|h{}q~mv~f{|u~}m{|u~}a{}w~}o{}v~}d{|u~}m{|u~}c{}w~}o{|u~_{}v~|j{|"
"W{|v~|Z{|v~h{}w~}fv~|h{}v~n{}w~}nw~|w~|o{|v~j{|v~}q{}v~_{}v~nv~}M{|u~[{|w~}Mw~}E{|w~|V{}v~}x{|u~|  vw~} `{|w~|$"
"w~} w~} >w~}Dv~    Ov~   !v~Lw~|M{}w~|  <{}w~|ow~}Xm~|[v~  ^v~|    \"v~|p{|v~Xv~{v~V{}v~|N{}w~}Ru~}l{}u~|b{|g~}"
"|b{}w~}hv~|iv~}r{|v~qv~}i{|u~}m{|u~}*{}l~} y{}w~ y{}k~| By~}R{}v~ y{|w~}o{|w~}Uw~|T{}w~ x{|x~}g{}x~|R{|x~}  y{|"
"x~}g{}x~|+{}y~}r{}y~}R{}w~Fx~}M{|}w~ Mm~}w{|x~} H{}x~|Tw~p{}x~|.{}x~|j{|w~b{}x~|j{|w~]w~n{|w~#v~{v~Rv~{v~Rv~{v~"
"Rv~{v~Rv~{v~S{|w~}{}w~|Zv~|x{|v~Uu~}j{|y~}c{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~k{}t~d{}q~mv~f{|"
"u~}m{|u~}e{|u~}m{|u~}e{|u~}m{|u~}e{|u~}m{|u~}e{|u~}m{|u~}1{|u~}m{|u~}e{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w"
"~}c{}v~nv~}_{}w~}Mv~n{}w~Tw}N{|x}P{|x}r{|x} F{|}x~}| ={|x}|O{|x}|Px}|s{|x}| xw|Nw|Pw|rw|'{|v~}|y{|v~} tw}Nw}P{|"
"x}rx}|  6w|Nw|Ox|rw| Nw~}  e{}h~}\\{}h~}\\{}h~}\\{}h~}\\{}h~}S{|w~Z{|v~gv~| Ay~}L{|y~}${|q~}V{|j~ci~}|i~|a{}p~|"
"Oy|Uw|jw|Vu|Wv|kw|b{}v~}     p{|v~|l{|}$v~}R{}x~}vw~}T{|x~}t{|x~}]{|g~|i{}x~|s{|w~qw~|^v~B{}x~}M{|w~|L{|w~}V{|}"
"w~}xx~x{}w~}|U{}w~  a{}w~Z{|v~o{}w~}U{}w~}X{|j{}v~|M{}v~Vw~}{}w~}\\{|w~}L{|v~|>v~}_{|v~|nv~}a{}v~nv~|   \\{}w~}"
"b{|u~|h{|}v~|`{|w~}{}w~|[{}w~}m{|v~|a{}v~}gy}g{}w~}j{}u~|b{}w~}L{}w~}Q{}v~}f{|~|g{}w~}hv~|Y{}w~}M{}w~}W{}w~}r{}"
"u~|[{}w~}V{}w~y|w~m{|w~{v~|h{}w~}v~|nv~f{}v~}ju~|b{}w~}nu~d{}v~}ju~|d{}w~}n{}v~|`v~}D{|v~|Z{|v~h{}w~}f{}w~}hv~}"
"n{|v~o{|w~{}x~}o{}w~}i{}v~|s{|v~|^v~}p{}v~M{|u~|[{|w~}M{}x~}E{|w~|W{}v~|v{|u~|  ww~} `{|w~|$w~} w~} >w~}Dv~    "
"Ov~   !v~Lw~|M{|w~|  <{}w~|ow~}Xy~}w|}t~[v~|  _{}w~}    #{|w~}n{}w~|Z{|w~}{}w~|Vu~|O{}w~}S{}v~}j{}u~c{}d~|c{}w~"
"}hv~|iv~}r{|v~qv~}i{}v~}ju~|,{}v~y}w~|v~} {{}w~ {{}v~y}w~|u~| Cy~}R{}w~}R{|ey|_{}w~|pv~Tw~|T{}w~ y{|x~}e{}x~|\\"
"{|}p~}  {{|x~}e{}x~|,{}y~}r{}y~}R{}w~G{}x~|Rq~| N{|m~}w{|x~} H{}x~|U{|w~p{|x~}.{}x~|j{}x~|b{}x~|j{}x~|_{|w~|n{}"
"x~|${|w~}{}w~|T{|w~}{}w~|T{|w~}{}w~|T{|w~}{}w~|T{|w~}{}w~|T{}w~|{|w~}[{|v~w{|v~V{}v~}gy}c{}w~}M{}w~}M{}w~}M{}w~"
"}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~j{|u~}e{}w~}v~|nv~f{}v~}ju~|f{}v~}ju~|f{}v~}ju~|f{}v~}ju~|f{}v~}ju~|c{}d{}|d{}v~}"
"k{}u~|f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}bv~}p{}v~^{}m~y}|Yv~o{|}w~         Py~}|u{|v~}       2w~}  f{"
"}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~T{|w~Yv~|i{|v~ A{}x~}M{}y~|$o~|W{|j~ch~}i~}"
"b{}n~T{|}t~y}|Zw~}kw~}X{}u~|X{}w~|m{}w~|d{|v~|     ov~}j{|$v~}R{}x~}vw~}T{}x~}t{}x~}]u~}|{|y~|y{|y}x~|iw~|rw~r{"
"}x~}]v~B{}x~}Mv~Jv~T{|}w~|{x~{|w~}|S{}w~  aw~}Z{}w~}o{|v~U{}w~}Ev~}M{|v~W{}w~y{}w~}\\{|w~}Lv~}>{|v~|_{|v~m{}w~}"
"av~|n{|v~ 8{|y}6{|~|4{}v~c{|v~}d{|v~`{}w~|{|w~}[{}w~}lv~|b{|v~}e{|g{}w~}i{}u~b{}w~}L{}w~}R{|v~}dy|g{}w~}hv~|Y{}"
"w~}M{}w~}W{}w~}s{}u~Y{}w~}V{}w~|{w~|nw~}{v~|h{}w~y|v~nv~g{|v~}i{|u~b{}w~}n{|v~|f{|v~}i{|u~d{}w~}n{|v~|a{|v~C{|v"
"~|Z{|v~h{}w~}f{|v~|j{|v~|mv~|p{|w~{|x~}ov~|hv~}sv~}]{|v~|r{|v~|Mu~|Z{|w~}M{|w~E{|w~|X{}v~|t{|u~|  xw~} `{|w~|$w"
"~} w~} >w~}Dv~    Ov~   !w~}Lw~|M{|w~|  <v~nw~}X{|s{}v~}\\{}v~|  `{|v~    #{}w~|n{|w~}Z{}w~|{|w~}Uu~|P{}w~}T{|u"
"~h{}v~}f{|r~y}v~}r~}d{}w~}hv~|iv~}r{|v~qv~}j{|v~}i{|u~-{}v~}{}w~{|v~} {}w~ {}v~}{}w~{|u~ Cy~}Rv~|S{}~}g{|y~|_v~"
"q{}w~|Tw~|T{}w~| {{x~}t{|y}u~}|u{}x~^{}m~}  {{x~}wq}y|s{}x~,{}y~}r{}y~}R{}w~H{|x~}Qs~} L{}m~}w{|x~} H{}x~|U{|x~"
"}p{|x~}.{}x~|k{|x~}a{}x~|k{|w~cx}u~|n{|x~}#{}w~|{|w~}T{}w~|{|w~}T{}w~|{|w~}T{}w~|{|w~}T{}w~|{|w~}Tv~xv~[v~}w{|v"
"~W{|v~}e{|c{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~i{|u~|f{}w~y|v~nv~g{|v~}i{|u~g{|v~}i{|u~g{|v~}i{"
"|u~g{|v~}i{|u~g{|v~}i{|u~d{}y~f{}y~|f{|v~}k{|s~f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}b{|v~|r{|v~|^{}i~}|"
"\\v~q{}t~|         F{}v~|    C{~|   mw~}  gu~}p{}u~|au~}p{}u~|au~}p{}u~|au~}p{}u~|au~}p{}u~|V{|w~Y{}w~}i{}w~} B{"
"}w~}Mx~${}n~W{|k~}d{|U~}c{|m~}W{|n~}[w~}kw~}Xt~}X{|w~}mv~cv~|     o{|v~| mv~}R{}x~}vw~}Tw~|tw~|^{}v~|x{|y~|u{|~"
"|iw~|rw~s{|w~\\v~B{}x~}N{|w~}J{}w~|S{|n~|Q{}w~  b{|w~|Zv~|nv~|V{}w~}E{}w~}M{|v~X{|w~|y{}w~}\\{|w~}M{|v~={}v~^{|"
"v~m{}w~}b{|v~lv~| <{|}x~}6{|x~}|7{}w~}cv~|b{|w~}b{|v~xv~[{}w~}l{}w~}bu~|P{}w~}h{}v~}c{}w~}L{}w~}Ru~M{}w~}hv~|Y{"
"}w~}M{}w~}W{}w~}t{}u~X{}w~}V{}w~|{}x~}o{|w~|{v~|h{}w~|{v~}ov~gu~|h{}v~|c{}w~}mv~}fu~|h{}v~|e{}w~}mv~}a{|v~C{|v~"
"|Z{|v~h{}w~}ev~}j{}v~l{}w~}p{}x~}{|w~ov~|h{|v~}u{}v~[{}v~rv~}M{}v~}Y{|w~}Lw~|F{|w~|Y{}v~|qu~| Kt|Uw~}uu|Mt|Ru|u"
"{|w~|Wt|Ow~}Mu|Tw~}uu| Jw~}Dv~Tu|mv|Vu|Pt|Ku|Qu|Bv|Us|Rv~   !w~}Lw~|M{|w~|  iv|Sv~o{|w~}N{}v~\\{|t~}|Is|Mu| u{}"
"w~|   Zt| Lv~|n{|v~[{|v~xv~Tu~P{}w~}T{}v~|gu~g{|t~}|y{|v~x{}t~}e{}w~}hv~|iv~}r{|v~qv~}ju~|h{}v~|/{}v~}y{}w~y{|v"
"~}!{}w~!{}v~}y{}w~y{|u~ F{|}y~}x|V{|v~S{}x~}i{|w~|`{}w~|rw~}Sw~|T{|v~|!{}y~}u{|n~}v{}y~}a{|k~}  {}y~}vn~}t{}y~}"
"-{}y~}r{}y~}R{}w~I{|w~Pt~}| L{}m~}w{|x~} H{}x~|U{|x~}p{|w~.{}x~|kw~|a{}x~|kw~|ct~}lw~|${|v~xv~U{|v~xv~U{|v~xv~U"
"{|v~xv~U{|v~xv~U{|w~}x{}w~|]{|v~v{|v~Wu~|L{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~h{|v~}f{}w~|{v~}o"
"v~gu~|h{}v~|hu~|h{}v~|hu~|h{}v~|hu~|h{}v~|hu~|h{}v~|f{}w~h{}w~|gu~|l{|r~|g{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~"
"h{}w~}a{}v~rv~}]{}g~}]w~}s{|r~|Xt|Nt|Nt|Nt|Nt|Nt|Xt|lu|Ut|Pt|Nt|Nt|Nt|  0{}v~|Pu|Pt|Nt|Nt|Nt|Nt| ut|t{}y~}   nw"
"~}uu|  t{}w~}|wv|v{}v~b{}w~}|m{}v~b{}w~}|m{}v~b{}w~}|m{}v~b{}w~}|m{}v~V{|w~Xv~iv~| C{|v~M{|y~}%{}m~}Wk~}d{|U~}d"
"{|k~}Y{}k~|]w~}kw~}Y{|s~X{|v~n{|w~}d{}w~}     n{}w~} lv~}R{}x~}vw~}U{|w~t{|w~]v~|w{|y~|`w~|rw~s{}x~|\\v~|C{}x~}"
"N{}w~|J{|w~}Q{|r~|O{}w~  b{}w~Z{|v~m{}w~}V{}w~}E{}w~}M{|v~Xw~}x{}w~}\\{|w~}M{}w~}=v~}^{|v~m{}w~}b{|v~lv~} ?{|}u"
"~}6{|u~}|:{}w~}d{}w~|`{|w~}c{}w~|x{}w~}\\{}w~}l{}w~}c{|v~}O{}w~}gu~c{}w~}L{}w~}S{|v~}M{}w~}hv~|Y{}w~}M{}w~}W{}w"
"~}uu~}W{}w~}V{}w~|{|w~|p{}w~yv~|h{}w~|{|v~ov~h{|v~}fu~c{}w~}mv~}g{|v~}fu~e{}w~}mv~}a{|v~C{|v~|Z{|v~h{}w~}e{}v~j"
"v~|l{}w~}pw~|yw~|q{|v~f{}v~|w{|v~|Zv~}t{}v~M{}v~}X{|w~}L{}x~}F{|w~|Z{}v~|o{}v~| P{|}q~}|Xw~}w{}s~}|S{|}q~}|X{}s"
"~}|x{|w~|Z{|}r~}|W{}k~}W{}s~}|x{|w~|`w~}w{|s~}|Rv~Lv~Tw~}n{|v~}Xv~_w~}w{}s~}r{|s~}cw~}w{|s~}|V{|}r~}|Yw~}w{}s~}"
"|V{}s~}|x{|w~|Zw~}w{}t~|Y{}o~}|Z{}i~]{|w~|m{}w~|c{|v~iv~i{}w~|pu~ow~}hv~}m{|v~|d{|v~iv~`d~Uw~}Lw~|M{|w~|  l{|s~"
"}|u{}x~}av~o{|w~}M{}w~|\\{}q~}|P{}o~}|\\w~}w{|s~}|^x~y}hv~W{}w~}X{|w~|m{}w~|d{}w~}h{}w~}]{|y}w{|}x~}|]_~|dv~t{}"
"w~t{|w~}[{|q~}|U{|y}i~}f{|`~b{|v~lv~|\\{}w~|x{}w~}U{|u~Q{}w~}U{|v~}f{|v~|ht~|w{|v~v{}u~}f{}w~}hv~|iv~}r{|v~qv~}"
"k{|v~}fu~/{|w~}x{}w~x{|w~}I{|T{}w~S{|i{|\\w~}x{}w~x{|w~|!v~}O{|}p~}|Y{|v~T{|v~}k{|v~}_v~s{}w~|Sw~|Su~|#{|x~u{}l"
"~ux~|bv~}y|v{|x~} !{|x~ul~|ux~|.{|x~|t{|x~|R{}w~J{|w~|L{|}x~}&{|w~|m{}w~|a{}m~}w{|x~} H{}x~|U{|x~}p{|w~.{}x~|l{"
"}x~}`{}x~|l{}x~}br~|o{}x~}Qv~|S{}w~|x{}w~}V{}w~|x{}w~}V{}w~|x{}w~}V{}w~|x{}w~}V{}w~|x{}w~}V{}w~|x{|w~}]{}w~}v{|"
"v~X{|v~}K{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~gu~|g{}w~|{|v~ov~h{|v~}fu~i{|v~}fu~i{|v~}fu~i{|v~}"
"fu~i{|v~}fu~g{|u~j{}v~}h{|v~}l{|w~}v~}g{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}`v~}t{}v~\\{}f~}^w~}t{}v~}y|Y"
"{|}q~}|U{|}q~}|U{|}q~}|U{|}q~}|U{|}q~}|U{|}q~}|_{|}q~}|r{|}r~}[{|}q~}|W{|}r~}|T{|}r~}|T{|}r~}|T{|}r~}|Qv~Lv~Lv~"
"Lv~O{|y}w~}u~|\\w~}w{|s~}|V{|}r~}|T{|}r~}|T{|}r~}|T{|}r~}|T{|}r~}|Q{}u~Q{|}r~}|x{}x~}b{|w~|m{}w~|a{|w~|m{}w~|a{"
"|w~|m{}w~|a{|w~|m{}w~|c{|v~iv~aw~}w{}s~}|^{|v~iv~ W{}w~}u{}w~u{}w~}d{}w~}j{}w~}d{}w~}j{}w~}d{}w~}j{}w~}d{}w~}j{"
"}w~}W{}w~X{}w~}k{|v~ C{|v~|M{}y~|&{|k~}X{}l~|cU~}di~|[{}i~|^w~}kw~}Y{}s~|Xv~|o{}w~|dw~}     mv~| lv~}R{}x~}vw~}"
"^{}Z~f{|w~}v{|y~|`w~|rw~t{|x~}[{}w~}C{}x~}Nv~Hv~O{}v~}M{}w~  bw~}Z{}w~}m{|v~V{}w~}E{}w~}M{|v~Y{}w~w{}w~}\\{|w~}"
"Mv~|>{|v~]{|v~m{}w~}b{|w~}l{}w~}W{|v}M{}v~D{}r~}6{|r~}|>{|v~|e{}w~|^{|w~|dv~w{|v~\\{}w~}lv~|c{}v~N{}w~}g{}v~|d{"
"}w~}L{}w~}S{}v~L{}w~}hv~|Y{}w~}M{}w~}W{}w~}vu~}V{}w~}V{}w~|yw~}pw~}yv~|h{}w~|y{}w~}pv~h{}v~e{}v~|d{}w~}mv~}g{}v"
"~e{}v~|f{}w~}mv~}a{|v~C{|v~|Z{|v~h{}w~}dv~|l{|v~k{|v~q{|w~x{}x~}q{}w~}e{}v~wv~}Y{|v~|v{|v~|N{|v~}W{|w~}L{|w~F{|"
"w~|[{}v~l{}v~ S{|}k~|Zw~}y{|o~}V{|k~|\\{|o~}y{|w~|\\{|m~}X{}k~}Y{|o~}y{|w~|`w~}y{|o~}Sv~Lv~Tw~}o{|v~}Wv~_w~}y{|"
"o~|v{|o~|ew~}y{|o~}Y{|}n~}|[w~}y{|o~}Y{|o~}y{|w~|Zw~}y{|r~|[{}j~[{}i~]{|w~|m{}w~|b{}w~|k{|w~}i{|w~}q{|u~|q{|w~|"
"h{|v~|o{|v~}b{}w~|k{|w~}`d~Uw~}Lw~|M{|w~|  n{|o~}vw~|av~o{}w~|M{|v~[{|o~}|U{}k~}]w~}y{|o~}_u~|k{|w~}Wu~X{|w~|m{"
"}w~|dv~|h{|v~_{}x~}x{}s~}__~|dv~t{}w~t{|w~}\\{}n~}Y{|}e~}f{|`~b{|w~}l{}w~|\\v~w{|v~T{|u~R{}w~}U{}v~dv~}i{}u~u{|"
"v~u{|u~|g{}w~}hv~|iv~}r{|v~qv~|k{}v~e{}v~|c{~}I{|y~}w{}w~w{|y~}I{}~|U{}w~T{}~|k{}~|\\y~}w{}w~w{|y~| v~}P{}k~Z{|"
"v~S{|v~}x{|}v~}|y{|v~}^{|w~}u{|w~}Rw~|S{|u~}${}y~|v{}v~}|wy|}y~u{|y~}c{|x~}r{|x~}Q{|q{| W{}y~|uw~vy|v~u{|y~}-w~"
"|v{|w~Q{}w~K{|w~|I{|w~'{|w~|m{}w~|a{}m~}w{|x~} H{}x~|U{|x~}p{|x~}]{|q{|X{}x~|m{|w~_{}x~|m{|w~]{|}w~}q{|w~Pv~|Sv"
"~w{|v~Vv~w{|v~Vv~w{|v~Vv~w{|v~Vv~w{|v~W{|v~vv~^{|v~|v{|v~X{}v~J{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z"
"{|v~g{|v~}g{}w~|y{}w~}pv~h{}v~e{}v~|j{}v~e{}v~|j{}v~e{}v~|j{}v~e{}v~|j{}v~e{}v~|g{|u~l{}v~}g{}v~kw~}{}v~g{|v~h{"
"}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}`{|v~|v{|v~|\\{}w~}s|y}t~}_w~}u{|v~|Y{|}k~|Z{|}k~|Z{|}k~|Z{|}k~|Z{|}k~|Z{|"
"}k~|d{|}k~|v{|m~}_{|k~|[{|m~}W{|m~}W{|m~}W{|m~}Rv~Lv~Lv~Lv~Q{|}l~\\w~}y{|o~}Y{|}n~}|X{|}n~}|X{|}n~}|X{|}n~}|X{|"
"}n~}|S{}u~S{|}n~}{|x~}a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|b{}w~|k{|w~}aw~}y{|o~}^{}w~|k{|w~} X{|w~}"
"t{}w~t{|w~}f{|w~}h{|w~}f{|w~}yy|p{|}y{|w~}f{|w~}ly|y{|w~}f{|w~}h{|w~}X{}x~}X{|v~kv~| Cv~|Lx~&{|i~|Y{|m~}bU~|e{}"
"h~\\{|u~}|xy|}u~^w~}kw~}Yr~}X{}w~}ov~d{}w~     lv~| lv~}R{}x~}vw~}^{}Z~f{|w~|v{|y~|`w~|s{|w~tw~|[{|v~|D{}x~}Nw~"
"}H{}w~|Q{|t~|N{}w~  c{|w~|Zv~|lv~|W{}w~}E{}w~}M{}w~}Z{|w~|w{}w~}\\{|w~}N{|v~={}w~}\\v~|nv~|b{}w~}l{}v~W{}v~M{}v"
"~G{|}p~|6{|o~}@u~e{|w~|\\{}w~e{|w~}v{}w~|]{}w~}m{|v~|cv~}N{}w~}g{|v~}d{}w~}L{}w~}Sv~}L{}w~}hv~|Y{}w~}M{}w~}W{}w"
"~}x{|u~}U{}w~}V{}w~|y{}w~q{|w~|yv~|h{}w~|y{|v~pv~hv~}e{|v~}d{}w~}mv~}gv~}e{|v~}f{}w~}mv~}a{|v~|D{|v~|Z{|v~h{}w~"
"}d{}w~}l{}w~}jv~|r{|w~x{|x~}qv~|e{|v~}y{}v~W{}v~vv~}N{|u~V{|w~}Kw~|G{|w~|\\{}w~}j{}v~ T{}i~}[w~}{}m~}X{}j~|]{}m"
"~}{|w~|]{}j~Y{}k~}Z{}m~}{|w~|`w~}{|l~Tv~Lv~Tw~}p{}v~}Vv~_w~}{|m~|x{|m~|fw~}{|m~}[{|j~|\\w~}{}m~}[{}m~}{|w~|Zw~}"
"{|q~|\\{}i~[{}i~]{|w~|m{}w~|b{|w~}k{}w~|hw~}q{|u~}q{}w~|g{}v~ov~}a{|w~}k{}w~|`d~Uw~}Lw~|M{|w~| Gy|l{|Z{}m~}x{|w"
"~`v~p{|v~Kv~Z{|m~|X{}j~}]w~}{|l~`t~|l{}w~|X{|u~}Y{|w~|m{}w~|e{}v~f{}w~}b{|v~}y{|q~}`_~|dv~t{}w~t{|w~}^{|k~}[{|c"
"~}f{|`~b{}w~}l{}w~}]{|w~}vv~|T{|v~}S{}w~}Uv~}d{}v~j{|u~t{|v~t{|u~g{}w~}hv~|iv~}r{|v~r{|v~|kv~}e{|v~}dx~}I{|}v{}"
"w~v{|}I{}x~|V{}w~U{}x~|m{}x~|\\{|v{}w~vy| {{v~}R{|i~Z{|v~R{|v~}|q~}|v~}\\v~u{}w~Qw~|R{|t~|'{|y~}v{}w~}p{|t{}y~|"
"d{}x~|r{|x~}Ry}r{|~ X{|y~}tw~sw~|u{}y~|.{|w~}x|}w~|Q{}w~L{|w~|G{|x~}({|w~|m{}w~|a{}m~}w{|x~} H{}x~|U{|w~p{|x~}]"
"{~|r{|}Y{}x~|mw~|_{}x~|m{}x~|[{|w~|r{}x~|Pv~|T{|w~}v{}w~|X{|w~}v{}w~|X{|w~}v{}w~|X{|w~}v{}w~|X{|w~}v{}w~|X{}w~}"
"v{}w~}_{}w~}u{|v~Xv~}J{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~fu~g{}w~|y{|v~pv~hv~}e{|v~}jv~}e{|v~}"
"jv~}e{|v~}jv~}e{|v~}jv~}e{|v~}f{|u~n{}v~}fv~}l{}x~}y{|v~|h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}_{}v~vv~}["
"{}w~}q{|}u~|`w~}uv~W{}i~}[{}i~}[{}i~}[{}i~}[{}i~}[{}i~}e{}i~}x{}k~}a{}j~|\\{}j~Y{}j~Y{}j~Y{}j~Sv~Lv~Lv~Lv~R{}j~"
"}]w~}{|m~}[{|j~|Z{|j~|Z{|j~|Z{|j~|Z{|j~|T{}u~T{|f~`{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|b{|w~}k{}w~|a"
"w~}{}m~}_{|w~}k{}w~| Xw~}s{}w~s{}w~fw~}f{}w~fw~}y{|y~|r{|y~}y{}w~fw~}l{|y~}y{}w~fw~}f{}w~X{}x~}Wv~|m{|v~ C{}w~}"
"[{|}|o{|y~|&g~|Y{}n~|b{}V~e{|g~}]v~}r{|v~}_w~}kw~}Z{|r~}X{|v~p{|w~}dw~}     pw|v~l| {{v~}R{}x~}vw~}^{}Z~f{|w~|v"
"{|y~|`{}x~}s{|x~}u{}x~}Y{}v~|E{}x~}O{|w~}H{}w~|S{|}r~}|P{}w~  c{|w~Yv~|lv~|W{}w~}Ev~|N{|v~|Zw~}v{}w~}\\{|w~}|}v"
"~y}|X{}w~}>{|v~|\\{}w~}o{|v~a{}w~}l{}v~W{}v~M{}v~J{|}p~}|2{|}p~}|D{}v~|e{}x~}p{|}w~}|vx|uw~|f{}w~|v{|w~}]{}w~}m"
"{}v~c{|v~|N{}w~}fv~}d{}w~}L{}w~}T{|v~|L{}w~}hv~|Y{}w~}M{}w~}W{}w~}y{|u~}T{}w~}V{}w~|y{|w~|r{}x~}xv~|h{}w~|x{}w~"
"}qv~i{|v~|dv~}d{}w~}mv~}h{|v~|dv~}f{}w~}n{|v~|`u~D{|v~|Z{|v~h{}w~}d{|v~m{|v~|j{}w~}r{}x~}x{|w~qv~|d{}v~y|v~|Vv~"
"}x{}v~Mu~|V{|w~}K{}x~}G{|w~|]{}w~}h{|v~ U{}u~v}s~}\\w~}|v~w}t~}Zr~v}v~|^{}t~w}v~}|w~|^{}t~v}t~Zv}v~s}[{}t~w}v~}"
"|w~|`w~}|u~x}t~}Uv~Lv~Tw~}q{}v~|Uv~_w~}|v~x}s~y{|v~x}s~fw~}|u~x}t~}]{|s~x}s~|]w~}|v~w}t~}]{|t~w}v~}|w~|Zw~}|t~}"
"x~|]{}t~u}u~[{|x}v~q}]{|w~|m{}w~|av~kv~g{}w~q{}t~qv~e{}v~q{}v~_v~|m{|v~_d~Uw~}Lw~|M{|w~| J{|}v~}r{}v~}|_{}u~w}u"
"~|y{}x~}`v~q{|v~}K{}w~|\\{}w~}p~}Z{}s~w}u~}]w~}|u~x}t~}as~m{|v~W{}t~Y{|w~|m{}w~|ev~|f{|v~c{|u~}yn~a_~|dv~t{}w~t"
"{|w~}_{|t~w}t~}]{|b~}f{|`~b{}w~|l{}w~}]{}w~|v{|w~}S{|v~}T{}w~}Uv~|d{|v~|k{}v~|t{|v~s{}v~|h{}w~}hv~|i{}w~}r{|v~r"
"{|v~|l{|v~|dv~}ev~}C{}w~C{}v~|W{}w~V{}v~n{|v~|W{}w~ sv~}S{|s~}y~x}v~Z{|v~Q{|e~}[{|w~}w{|w~}Qw~|R{}r~|){}y~|w{|w"
"~}g{|y~}dw~q{}x~}S{}~}s{}y~ X{}y~|tw~s{}x~}u{|y~}-{}p~}P{}w~M{|w~|F{|x~}({|w~|m{}w~|a{}m~}w{|x~} H{}x~|Tw~p{}x~"
"|]y~}s{|y~Z{}x~|n{|x~}^{}x~|n{|w~Y{|x~}s{|x~}Ov~|T{}w~|v{|w~}X{}w~|v{|w~}X{}w~|v{|w~}X{}w~|v{|w~}X{}w~|v{|w~}Xv"
"~u{|v~_v~|u{|v~Y{|v~|J{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{}v~g{}w~|x{}w~}qv~i{|v~|dv~}k{|v~|d"
"v~}k{|v~|dv~}k{|v~|dv~}k{|v~|dv~}e{|u~p{}v~}f{|v~|m{}w~wv~}h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}^v~}x{}v"
"~Z{}w~}o{}v~}`w~}v{|w~|W{}u~v}s~}\\{}u~v}s~}\\{}u~v}s~}\\{}u~v}s~}\\{}u~v}s~}\\{}u~v}s~}f{}u~v}s~}{s~w}t~}cr~v}"
"v~|]{}t~v}t~[{}t~v}t~[{}t~v}t~[{}t~v}t~Tv~Lv~Lv~Lv~S{}h~|^w~}|u~x}t~}]{|s~x}s~|\\{|s~x}s~|\\{|s~x}s~|\\{|s~x}s~"
"|\\{|s~x}s~|U{}u~U{|s~x}q~|`{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|av~|m{|v~`w~}|v~w}t~}_v~|m{|v~ X{|w~"
"r{}w~rw~}h{|w~dw~}h{|w~y{|w~|t{|w~}yw~}h{|w~l{|w~}yw~}h{|w~dw~}Y{}x~}W{}w~}m{}w~} Xg|}v~s|e{|}x~}o{}y~&{}f~Y{|o"
"~}a{|V~f{|e~}_{|w~}p{|v~_w~}kw~}Z{}w~}v~Wv~|q{}w~}e{|w~     pc~} {{v~}R{|x}|v{|x}|^{}Z~f{|w~|v{|y~|`{|w~s{}x~}v"
"{|w~Wu~|F{|x}|O{}w~|H{|w~}U{|}w~|x~|w~}|R{}w~  c{}x~}Yv~|lv~|W{}w~}F{|v~N{|v~}Z{}w~u{}w~}\\{|k~}Z{}w~}x{|}u~y}|"
"L{}v~Zv~|pv~}a{|v~l{}v~|X{}v~M{}v~M{|}p~}|,{|}p~}|H{}v~|e{|w~q{|q~}y{}x~|v{|x~}fv~tv~]{}w~}n{}v~|c{|v~|N{}w~}f{"
"}v~d{}w~}L{}w~}T{}v~|L{}w~}hv~|Y{}w~}M{}w~}W{}w~}{|u~}S{}w~}V{}w~|xw~}rw~|xv~|h{}w~|x{|v~|rv~i{|v~|d{}v~d{}w~}n"
"{|v~|h{|v~|d{}v~f{}w~}n{}v~|`{}v~}|F{|v~|Z{|v~h{}w~}cv~|n{}v~i{}w~}rw~|ww~|s{|v~b{}q~}U{|v~|{|v~|N{}v~|U{|w~}K{"
"|w~G{|w~|^{}w~}f{|v~ V{}y~}|r{|u~|]r~|u{|u~}\\{}u~}s{|}y~|_{|u~|u{|}s~|_{}v~}|t{}v~}Vw~}T{|u~|u{|}s~|`r~|u{|u~|"
"Vv~Lv~Tw~}ru~|Tv~_r~|v{|}v~}{w~|u{}v~}gr~|u{|u~|^u~}|v{|}u~]r~|u{|u~|_{|u~|u{|}s~|Zr~}|v{|\\v~}|r{|}y~Wv~S{|w~|"
"m{}w~|a{}w~|m{|w~}g{}w~|rs~qw~}dv~}s{|v~|_{}w~}m{}w~|Nu~Uw~}Lw~|M{|w~| K{}r~u{|r~}a{|v~}|v{}v~yw~|`v~r{|u~|K{|w"
"~|]{}w~|xy|}t~}[u~}|s{|}~}]r~|u{|u~|ay|v~|n{}w~|X{|s~|Z{|w~|m{}w~|f{|v~dv~|e{|u~}|{|v~y|}v~}bx}u~q}u~x}|dv~t{}w"
"~t{|w~}_u~|u{|u~|_{|u~}|v{|}t~v}f{|q}u~p}b{}w~|l{|v~]v~tv~R{}v~}U{}w~}V{|v~|cv~}l{|v~}s{|v~s{|v~}h{}w~}hv~|i{}v"
"~r{|v~r{|v~|l{|v~|d{}v~fu~|C{}w~C{|u~|X{}w~W{}v~}m{}v~|X{}w~ sv~}T{|u~}|yy~}x{|}y~Z{|v~P{|g~}Y{}w~|xv~Pw~|T{|v~"
"}u~}*x~v{}w~ex~dw~qw~}U{|x~}t{}x~ Xx~sw~s{}x~}tx~,{|r~|O{}w~N{|w~|Dw~({|w~|m{}w~|a{|m~}w{|x~} H{}x~|T{}x~}qw~|]"
"x~}t{|x~|\\{}x~|nw~]{}x~|nw~|Xw~sw~|Ov~|Tv~tv~Xv~tv~Xv~tv~Xv~tv~Xv~tv~Y{|w~}tv~|a{|v~t{|v~Y{|v~|J{}w~}M{}w~}M{}"
"w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{|v~|h{}w~|x{|v~|rv~i{|v~|d{}v~k{|v~|d{}v~k{|v~|d{}v~k{|v~|d{}v~k{|v~|d{"
"}v~d{|u~r{}v~}e{|v~|n{}w~v{}v~h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}^{|v~|{|v~|Z{}w~}nu~`w~}v{}w~V{}y~}|r"
"{|u~|]{}y~}|r{|u~|]{}y~}|r{|u~|]{}y~}|r{|u~|]{}y~}|r{|u~|]{}y~}|r{|u~|g{}y~}|r{|o~}|u{|}v~}e{}u~}s{|}y~|^{}v~}|"
"t{}v~}]{}v~}|t{}v~}]{}v~}|t{}v~}]{}v~}|t{}v~}Uv~Lv~Lv~Lv~T{}u~}|v{|}v~}^r~|u{|u~|^u~}|v{|}u~\\u~}|v{|}u~\\u~}|v"
"{|}u~\\u~}|v{|}u~\\u~}|v{|}u~U{}u~Uu~}|u{}u~|_{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{}w~}m{}w~|`r~|u{"
"|u~|`{}w~}m{}w~| Xw~|r{}w~r{|w~hw~|d{|w~hw~|yu~|v{|u~y{|w~hw~|m{|u~y{|w~hw~|d{|w~Y{}x~}Vv~mv~| XZ~}g{}t~oy~}'{}"
"e~}Y{}p~_W~|fc~|`v~n{}w~|`w~}kw~}Zv~|}w~|X{}w~}qv~|e{}x~}     q{|c~| {{v~} y{|x~}t{}x~}]{|w~}v{|y~|_w~|u{|w~|vw"
"~|Wt~ p{}w~|H{|v~V{}w~}yx~y{}w~}S{}w~  cw~|Z{|v~k{}w~}W{}w~}Fv~}Qy|u~}Z{|w~|u{}w~}\\{|i~|\\v~|y{}p~}|Nv~}Z{|v~|"
"s{|v~}`{|v~lu~|X{}v~M{}v~P{|}p~}|b{|Z~}b{|}p~}|L{}v~}d{}x~|r{|n~{}x~|uw~|h{}w~}t{}w~|^{}w~}q{|}u~}b{}v~M{}w~}f{"
"}v~d{}w~}L{}w~}T{}v~K{}w~}hv~|Y{}w~}M{}w~}W{}w~}|u~}R{}w~}V{}w~|x{|w~s{}w~wv~|h{}w~|w{}w~}rv~i{}v~c{}v~d{}w~}n{"
"}v~|h{}v~c{}v~f{}w~}o{|u~_{|t~}|H{|v~|Z{|v~h{}w~}c{}v~nv~}i{|v~s{|w~|w{}x~}s{}w~}b{|q~S{}v~|v~}N{}v~}T{|w~}K{|w"
"~|H{|w~|  s{}|m{}w~}]t~}q{}v~|^{}v~}ny|_u~q{}t~|`{|v~|q{|v~|Ww~}Tu~q{|t~|`t~}r{|v~}Vv~Lv~Tw~}t{|u~Rv~_t~}r{}v~}"
"y~}r{}v~gt~}r{|v~}_{}v~|r{|v~}^s~q{}v~_{}v~|r{}t~|Zs~T{|w~}m{|Wv~S{|w~|m{}w~|a{|w~}mv~|g{|w~}s{|s~|s{|w~|d{|v~|"
"u{|v~}]v~mv~N{}v~Tw~}Lw~|M{|w~| L{}p~w{|p~}bv~}s{}w~y|w~_v~wx|}t~}J{|w~}^{}w~r{}u~|]{|v~|Ot~}r{|v~}_{|v~nv~W{}s"
"~}Z{|w~|m{}w~|f{}w~}d{}w~}eu~}x{|w~|x{}v~|`{|w~}q{|w~}`v~t{}w~t{|w~}`{}v~q{}v~_u~}r{|v~}V{|w~}Wv~|l{|v~^{}w~}t{"
"}w~|R{}v~}V{}w~}V{|v~bv~}l{|v~|s{|v~r{}v~h{}w~}hv~|i{}v~r{|v~r{}v~k{}v~c{}v~gu~|B{}w~B{|u~|Y{}w~X{}v~}k{}v~|Y{}"
"w~ sv~}Tu~|wy~}u{|Z{|v~O{|u~}|x{|}v~}_{|p~}y{|p~}Ww~|Tw~}y{|t~|,y~}vw~|e{}y~dw~|s{}w~}V{|w~}u{}w~ Xy~}sw~s{}x~}"
"t{}y~*y}x~}|[m|}w~l|^{}w~C{|x~}({|w~|m{}w~|`m~}w{|x~} H{}x~|T{|w~|s{}x~}\\w~}u{|w~|]{}x~|o{}x~}]{}x~|o{}x~}Ww~t"
"{}x~}Nv~|U{}w~}t{}w~|Z{}w~}t{}w~|Z{}w~}t{}w~|Z{}w~}t{}w~|Z{}w~}t{}w~|Z{}w~|t{|w~}av~}t{|v~Y{}v~I{}w~}M{}w~}M{}w"
"~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{|v~|h{}w~|w{}w~}rv~i{}v~c{}v~k{}v~c{}v~k{}v~c{}v~k{}v~c{}v~k{}v~c{}v~c{|"
"u~t{}v~}d{}v~n{|w~|v{|v~h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}]{}v~|v~}Y{}w~}n{|v~|aw~}vv~V{}|m{}w~}]{}|m"
"{}w~}]{}|m{}w~}]{}|m{}w~}]{}|m{}w~}]{}|m{}w~}g{}|m{}r~|q{|v~|g{}v~}ny|_{|v~|q{|v~|_{|v~|q{|v~|_{|v~|q{|v~|_{|v~"
"|q{|v~|Vv~Lv~Lv~Lv~U{|v~}q{|v~|_t~}r{|v~}_{}v~|r{|v~}^{}v~|r{|v~}^{}v~|r{|v~}^{}v~|r{|v~}^{}v~|r{|v~}V{}u~V{}v~"
"|r{|v~}_{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|`v~mv~_s~q{}v~_v~mv~ X{|w~q{}w~q{}x~|j{|w~b{}x~|j{|w~wu~"
"|x{|u~|x{}x~|j{|w~m{|u~|x{}x~|j{|w~b{}x~|Z{}x~}V{}w~|o{|v~ WZ~}gx~}w~|q{}y~|({|c~}_v|{}r~u|d{}X~f{}b~|b{|w~}mw~"
"}`w~}kw~}[{|v~{}w~}X{|w~}r{|v~d{}x~|     q{}c~ yv~} y{}x~}t{}x~}\\v~}w{|y~|_{}w~|vw~}v{|x~}X{|r~ qv~Fv~X{}w~}|x"
"x~x{|}w~}U{}w~  d{|w~Y{|v~k{}w~}W{}w~}G{}v~|Xm~}Y{}x~}t{}w~}\\{|h~}]v~y|l~}P{|v~|Y{|u~u|}v~}_{|v~|n{|u~|X{}v~M{"
"}v~R{|o~}|`{|Z~}_{|}p~}|P{}v~}cw~r{|l~}x~|u{|x~|hv~|t{|v~^{}e~}a{}v~M{}w~}f{|v~|e{}d~|_{}g~|d{}v~K{}^~|Y{}w~}M{"
"}w~}W{}p~|Q{}w~}V{}w~|ww~|tw~}wv~|h{}w~|vv~|sv~i{}v~c{|v~|e{}w~}o{|u~g{}v~c{|v~|g{}w~}p{|u~|^{}q~y}|M{|v~|Z{|v~"
"h{}w~}c{|v~|p{|v~gv~|t{|w~v{|x~}sv~|a{|s~|Rq~}N{}v~}S{|w~}Jw~}H{|w~|  bv~|^t~ov~}^v~}P{|v~|p{}u~|`v~|o{|v~Ww~}U"
"{|v~o{}u~|`u~}p{|v~Vv~Lv~Tw~}u{|v~}Qv~_u~}pt~}pv~|hu~}p{|v~`{|v~|p{|v~|_t~ov~}a{|v~|p{}u~|Zt~S{}w~Gv~S{|w~|m{}w"
"~|`v~|o{|v~ev~s{|x~y}x~}s{}w~|c{}v~uv~}\\{}w~|o{|w~}O{}v~|U{|w~}Lw~|M{|w~} M{|x~}x|}w~}xv~}x|}x~|d{}v~qw~y}x~}_"
"v~x{}q~}I{|w~}_{|w~|q{|u~]{}w~|Nu~}p{|v~^{}w~|p{|w~}X{|q~Z{|w~|m{}w~|fv~|d{|v~f{|v~}w{}w~|wu~`{|w~}q{|w~}`v~t{}"
"w~t{|w~}a{|v~ov~}a{|v~}p{}v~|W{|w~}Wv~}l|}v~^v~|t{|v~Q{}v~}W{}w~}V{|v~b{}w~}l{}v~r{|v~r{}v~|i{}w~}hv~|i{|v~|s{|"
"v~r{}v~k{}v~xi~}y{|v~|iu~|A{}w~A{|u~|Z{}w~Y{}v~}i{}v~|Z{}w~ sv}|U{}v~|vy~}S{|v~O{|w~}s{|v~_{|o~|{o~}Ww~|U{}x~}v"
"{}u~}.{|y~|w{|w~d{|y~|e{}w~t{}v~}W{|v~|v{}w~}cY|8{|y~|sw~sw~|t{|y~| `{|Z~}_{}x~}C{|w~}({|w~|m{}w~|`{|n~}w{|x~} "
"H{}x~|Sv~|u{}w~|\\{}v~v{|v~|^{}x~|p{|w~\\{}x~|p{|w~W{|x~}u{|w~Mv}|Uv~|t{|v~Zv~|t{|v~Zv~|t{|v~Zv~|t{|v~Zv~|t{|v~"
"Zv~rv~b{|v~s{|c~l{}v~I{}d~|`{}d~|`{}d~|`{}d~|W{}w~}M{}w~}M{}w~}M{}w~}Z{|v~ev~}h{}w~|vv~|sv~i{}v~c{|v~|l{}v~c{|v"
"~|l{}v~c{|v~|l{}v~c{|v~|l{}v~c{|v~|c{|u~v{}v~}c{}v~o{|w~|u{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}\\q~"
"}X{}w~}mv~}aw~}vv~Ev~|Mv~|Mv~|Mv~|Mv~|Mv~|Ws~|o{}w~}gv~}Ov~|o{|v~_v~|o{|v~_v~|o{|v~_v~|o{|v~Vv~Lv~Lv~Lv~Uv~}o{}"
"w~}_u~}p{|v~`{|v~|p{|v~|`{|v~|p{|v~|`{|v~|p{|v~|`{|v~|p{|v~|`{|v~|p{|v~|Wt|W{|v~|q{}u~|`{|w~|m{}w~|a{|w~|m{}w~|"
"a{|w~|m{}w~|a{|w~|m{}w~|`{}w~|o{|w~}_t~ov~}`{}w~|o{|w~} X{}x~}q{}w~q{|x~}j{}x~}b{|x~}j{}x~}vu~|yu~|w{|x~}j{}x~}"
"mu~|w{|x~}j{}x~}b{|x~}Z{}x~}V{|v~o{}w~} WZ~}g{}|yw~}qx~'a~|c{|}t~}k~}|fY~}g{}`~b{|w~|m{}w~`w~}kw~}[{|w~}{|v~Wv~"
"r{}w~}dw~|     lv~| kv~| yw~|tw~|\\{}v~}|y{|y~|^v~}y|}v~uw~X{|p~ rv~Fv~Xw~|vx~v{|w~U{}w~  d{}x~}Y{|v~k{}w~}W{}w"
"~}H{|v~}Wo~}|Y{|w~|t{}w~}\\{|v~x}|x}s~}^v~|j~}Q{}w~}V{}l~}]v~}n{}u~}X{}v~M{|v}U{|}p~}|]{|Z~}\\{}o~|S{}v~}c{|x~}"
"rv~}|w{|}t~|tx~}i{|v~rv~|_{}h~}|_v~}M{}w~}f{|v~|e{}d~|_{}g~|dv~}K{}^~|Y{}w~}M{}w~}W{}q~|P{}w~}V{}w~|w{}w~u{|w~|"
"wv~|h{}w~|v{}w~}sv~iv~}c{|v~|e{}w~}p{|u~|gv~}c{|v~|g{}w~}sy|}u~}\\{}m~}|Q{|v~|Z{|v~h{}w~}bv~}p{}w~}g{}w~}t{}x~}"
"v{|w~sv~|`{}u~}Q{|r~|O{|u~R{|w~}J{}w~H{|w~|  b{|w~}^u~|o{|v~_{}v~Ov~}nu~|a{}w~}m{}w~|Xw~}Uv~|nu~|`u~nv~|Wv~Lv~T"
"w~}v{}v~}Pv~_u~o{}u~|p{}w~}hu~nv~|a{}w~}n{}w~}_u~|o{|v~a{}w~}nu~|Zu~|S{}w~Gv~S{|w~|m{}w~|`{}w~}o{}w~}e{}w~s{}x~"
"}|w~sv~a{}v~w{}v~[{|w~}ov~|P{}v~|T{|w~}Lw~|M{|w~}:{|4x~|v{|w~}{}x~}u{}x~dv~}q{}s~|_v~x{}r~}S{|y}~y}|w{|w~}_w~}o"
"{|v~}^{}w~Mu~nv~|_{|w~}pv~|X{}w~}v~|[{|w~|m{}w~|g{|v~bv~|g{}v~v{}w~v{|v~|a{|w~}q{|w~}`v~t{}w~t{|w~}a{}w~|o{|v~a"
"{}v~nv~}W{|w~}W`~_{|v~rv~|Q{}v~|X{}w~}V{|v~b{}w~}lu~r{|v~r{|v~|i{}w~}hv~|hv~}s{|v~rv~}kv~}xi~}y{|v~|ju~|@{}w~@{"
"|u~|[{}w~Z{}v~}g{}v~|[{}w~ Gv~}uy~}S{|v~Ow~}q{|w~|`{|n~}o~}Ww~|Uw~|t{}u~|0{|y~|w{|x~}d{|y~|e{|v~}w|t~}X{|v~|vv~"
"}c{|Z~}8{|y~|sw~t{}w~s{|y~| `{|Z~}`{}x~}M{|~}|v{|}v~'{|w~|m{}w~|_{}o~}w{|x~}Vv}| s{}x~|S{|v~}|{y|}w~}Z{}v~|w{|v"
"~}_{}x~|pw~|o{}w~m{}x~|p{}x~|vy|}w~y}|g{|w~|u{}x~|o{}w~3{|v~rv~|\\{|v~rv~|\\{|v~rv~|\\{|v~rv~|\\{|v~rv~|\\{}w~}"
"r{}w~|c{}w~}s{|c~lv~}I{}d~|`{}d~|`{}d~|`{}d~|W{}w~}M{}w~}M{}w~}M{}w~}_{}i~}nv~}h{}w~|v{}w~}sv~iv~}c{|v~|lv~}c{|"
"v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|b{|u~x{}v~}bv~}p{|w~}t{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}\\{|r~|"
"X{}w~}mv~}aw~}v{}w~}F{|w~}M{|w~}M{|w~}M{|w~}M{|w~}M{|w~}W{|u~}m{}w~h{}v~O{}w~}m{}w~|a{}w~}m{}w~|a{}w~}m{}w~|a{}"
"w~}m{}w~|Wv~Lv~Lv~Lv~V{}v~n{|v~_u~nv~|a{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~},{}w~}q{}t~}`"
"{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|`{|w~}ov~|_u~|o{|v~`{|w~}ov~| X{}x~|q{}w~q{|w~j{}x~|b{|w~j{}x~|u"
"u~|u~|v{|w~j{}x~|nu~|v{|w~j{}x~|b{|w~Zw~}Uv~|q{|v~ VZ~}c{}w~r{|y~}({}`~d{}^~|h{|Z~g{|_~}c{}w~l{|w~`w~}kw~}[{}w~"
"|yv~|X{}w~|sv~|dV~}    2v~| k{}w~| {{|w~t{|w~Zs~y}y~|^{|o~|v{}x~}rx|e{|v~y}u~n{|w~},{|v~Fv~|Y{|~}tx~t{}~|U{}w~ "
" dw~|Y{|v~k{}w~}W{}w~}Hu~Vp~}|Y{|w~}s{}w~}\\{|~}|q{}t~|`{|q~}|xy|t~|Rv~|U{|}p~|[{}v~|ot~} V{|}p~}|Z{|Z~}Z{|}p~}"
"|W{}v~|b{}x~|s{}w~|s{|u~|tw~i{}w~}r{}w~}_{}g~}|`v~}M{}w~}f{|v~|e{}d~|_{}g~|dv~}K{}^~|Y{}w~}M{}w~}W{}q~O{}w~}V{}"
"w~|w{|w~|v{}w~vv~|h{}w~|uv~|tv~iv~}c{|v~|e{}w~}sy|s~fv~}c{|v~|g{}f~}Z{}k~}S{|v~|Z{|v~h{}w~}b{|v~pv~|g{}w~}tw~|u"
"w~|u{|v~_{}u~O{}t~|O{|u~|R{|w~}J{|w~|I{|w~|  aw~}^v~}m{}w~}`v~|P{|v~m{}v~|av~l{|w~}Xw~}V{|v~m{|v~|`v~}n{}w~|Wv~"
"Lv~Tw~}w{}v~}Ov~_v~}o{|v~}o{|w~}hv~}n{}w~|av~|n{|v~|`u~mv~|bv~m{}v~|Zv~}R{}w~Gv~S{|w~|m{}w~|`{|v~ov~d{}w~|tw~|{"
"w~|u{|w~}`v~}y{|v~|Z{}w~|q{|v~P{}v~|Sv~|Lw~|Lv~|W{|y}w~}|iy}5{|y~}sw~|x~}s{}y~|f{|v~|ps~^v~x{}q~}|W{|r~|y{|w~}`"
"{}w~m{}v~^{}w~Mv~}n{}w~|^{}w~q{|v~Wv~y|w~}[{|w~|m{}w~|g{}v~b{}w~}h{|v~|v{}w~u{}w~}a{|w~}q{|w~}`v~t{}w~t{|w~}av~"
"mv~|c{|v~|n{|v~W{|w~}W`~_{}w~}r{}w~}Q{|v~}X{}w~}V{|v~b{}w~}lv~}r{|v~r{|v~|i{}w~}hv~|h{}v~s{|v~s{|v~|kv~}xi~}y{|"
"v~|ku~|?{}w~?{|u~|\\{}w~[{}v~}e{}v~|\\{}w~ H{}v~ty~}S{|v~P{|w~o{}w~_s|}r~s|Vw~|V{|w~r{|u~0{|y~v{}x~}d{|y~|d{}o~"
"|x~}Y{}v~v{|v~|b{|Z~}8{|y~rw~u}v~|s{|y~| `{|Z~}a{}l~|X{|m~|'{|w~|m{}w~|^o~}w{|x~}W{|v~| xm~}W{|n~}X{|v~|vv~}e{}"
"n~}v{}x~}o{|v~m{}x~|q{|w~w{|o~|t{|~}y|w{|}v~u{|x~}o{|v~3{}w~}r{}w~}\\{}w~}r{}w~}\\{}w~}r{}w~}\\{}w~}r{}w~}\\{}w"
"~}r{}w~}\\v~|r{|w~}cv~|s{|c~lv~}I{}d~|`{}d~|`{}d~|`{}d~|W{}w~}M{}w~}M{}w~}M{}w~}_{}i~}nv~}h{}w~|uv~|tv~iv~}c{|v"
"~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|a{|u~|}v~}av~}pw~}s{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}["
"{}t~|W{}w~}mv~}aw~}v{}v~|Fw~}Lw~}Lw~}Lw~}Lw~}Lw~}Vu~l{|w~|iv~|Ov~l{|w~}av~l{|w~}av~l{|w~}av~l{|w~}Wv~Lv~Lv~Lv~V"
"v~|mv~|`v~}n{}w~|av~|n{|v~|av~|n{|v~|av~|n{|v~|av~|n{|v~|av~|n{|v~|-v~|r{|x~}v~`{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{"
"}w~|a{|w~|m{}w~|_{}w~|q{|v~^u~mv~|`{}w~|q{|v~ Ww~p{}w~pw~jw~yd|yw~jw~t{|p~|tw~jw~nu~|tw~jw~pv~}qw~Zw~|U{}w~}q{}"
"w~} F{}w~}W{|w~|s{}y~|){|_~}f{}\\~|h{}\\~|g{}^~c{}w~l{|w~|aw~}kw~}[v~x{}w~}X{|w~}t{|v~cV~}    2v~| k{}w~| {{|x~"
"}t{|x~}Z{|o~}y|`{|}r~|v{|w~t{}u~}|hv~}y{}u~o{|w~|,{|v~F{}w~|X{|sx~s{|T{}w~  e{|w~X{|v~k{}w~}W{}w~}Iu~|Vm~|[{}w~"
"r{}w~}L{}u~`{|r~|s{|u~S{}v~V{|}m~}|\\u~p{}t~} Y{|}p~}|VY|W{|}p~}|[{|v~|aw~rw~}q{|v~|t{}x~iv~q{|v~_{}e~}av~}M{}w"
"~}f{|v~|e{}d~|_{}g~|dv~}m{}n~|h{}^~|Y{}w~}M{}w~}W{}q~}P{}w~}V{}w~|vw~}vw~}vv~|h{}w~|u{}v~tv~iv~}bv~|e{}e~|fv~}b"
"v~|g{}g~}X{|}k~}U{|v~|Z{|v~h{}w~}av~|r{|v~f{|v~u{|w~|u{}x~}u{}w~}`{|t~|O{}v~}Nu~|Q{|w~}Iw~}I{|w~|  a{}w~^v~|m{|"
"w~}a{|v~O{|w~}lv~|b{|w~}kv~Xw~}V{|w~}lv~|`v~|n{|w~}Wv~Lv~Tw~}x{}v~|Nv~_v~|nv~|nv~hv~|n{|w~}b{|v~lv~|`v~}m{|w~}c"
"{|w~}m{|v~|Zv~|R{}w~|Hv~S{|w~|m{}w~|_{}w~|q{|w~}d{|w~}u{|w~y{}x~|u{|w~|`{|v~y|v~}Y{|w~}q{}w~|Q{|v~}S{}v~Kw~|L{}"
"w~}Y{|p~}|n{|y~}5{}y~r{|t~qy~}f{}v~ot~}^v~x{}o~}Y{}p~|{|w~|`w~}lv~|_{|w~}Nv~|n{|w~}^{|w~|r{}w~|X{}w~}yv~[{|w~|m"
"{}w~|gv~}b{}v~h{|v~u{}w~u{|v~a{|w~}q{|w~}`v~t{}w~t{|w~}b{|w~}m{|w~}c{|v~lv~|X{|w~}W`~_v~|r{|v~Qu~W{}w~}V{|v~b{}"
"w~}lv~}r{|v~qv~|i{}w~}hv~|h{|v~|t{|v~s{}v~jv~}xi~}xv~|lu~[|]{}w~\\\\|u~|]{}w~\\{}v~}c|u~|]{}w~ H{}w~}ty~}X{}g~|"
"[{}x~}nw~Vs~|Nw~|V{}x~}pv~}1{}y~v{}x~}d{|y~}c{}r~}{|x~}Z{}w~}v{|v~|a{|Z~}8{}y~rn~}q{|y~} `{|Z~}a{}l~|X{|o~}|&{|"
"w~|m{}w~|]{}q~}w{|x~}W{|v~| xm~}V{|}q~|V{|v~|v{}w~}fm~}vw~o{|u~rm~}vw~|w{}n~|u{|m~|uw~|p{|u~3v~q{|v~\\v~q{|v~\\"
"v~q{|v~\\v~q{|v~\\v~q{|v~]{|v~pv~|e{}w~}r{|c~lv~}I{}d~|`{}d~|`{}d~|`{}d~|W{}w~}M{}w~}M{}w~}M{}w~}_{}i~}nv~}h{}w"
"~|u{}v~tv~iv~}bv~|lv~}bv~|lv~}bv~|lv~}bv~|lv~}bv~|`{|p~}`v~}q{}x~}qv~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}"
"w~}Z{}v~}V{}w~}mv~}aw~}uu~}G{}w~L{}w~L{}w~L{}w~L{}w~L{}w~V{}w~}kw~}j{|v~O{|w~}kv~b{|w~}kv~b{|w~}kv~b{|w~}kv~Wv~"
"Lv~Lv~Lv~W{|v~l{}w~}`v~|n{|w~}b{|v~lv~|b{|v~lv~|b{|v~lv~|b{|v~lv~|b{|v~lv~|.{|v~r{|w~{}w~|a{|w~|m{}w~|a{|w~|m{}"
"w~|a{|w~|m{}w~|a{|w~|m{}w~|_{|w~}q{}w~|^v~}m{|w~}`{|w~}q{}w~| Ww~yd~|{w~jw~yd~|{w~jw~s{|r~|sw~jw~ou~|sw~jw~pv~}"
"qw~Zw~|U{|v~qv~| G{}w~}Uw~}sx~({}^~g{}Z~g]~}f{|_~|cw~}l{|w~|aw~}kw~}\\{|v~x{|v~Wv~t{}w~}cV~}    2v~| k{}w~| {{}"
"x~}t{}x~}Y{|}m~}`{|}w~}|tw~|v{|q~}j{}v~w{}u~p{}w~|,{|w~}F{}w~|Ox~Z{|Z~}  t{}x~}X{|v~k{}w~}W{}w~}J{}v~|Ut|}t~}]{"
"|w~|r{}w~}K{}v~|a{|s~p{|v~}Tv~}W{}i~}]{}u~|t{|}s~} Z{|q~}| e{|}q~}\\v~}`x~}s{}w~ov~|t{}x~|k{|w~}p{}w~|`{}w~}p|}"
"t~|cv~}M{}w~}f{|v~|e{}w~}i|^{}w~}l|cv~}m{}n~|h{}w~}h|v~|Y{}w~}M{}w~}W{}w~}u~}Q{}w~}V{}w~|v{}w~w{|w~uv~|h{}w~|tv"
"~|uv~iv~}c{|v~|e{}f~|ev~}c{|v~|g{}i~}S{|}m~}V{|v~|Z{|v~h{}w~}a{}w~}rv~}ev~|v{|w~t{|w~uv~|`r~O{|v~|O{}v~}P{|w~}I"
"{}w~I{|w~|  a{}w~^v~|lv~a{}w~}O{}w~|lv~|b{|w~|k{}w~Xw~}V{}w~|lv~|`v~m{|w~}Wv~Lv~Tw~}yu~|Mv~_v~mv~mv~hv~m{|w~}b{"
"}w~}l{}w~}`v~|m{|v~c{}w~|lv~|Zv~Q{}v~|Iv~S{|w~|m{}w~|_{|w~}q{}w~|cv~u{}x~}y{}x~}u{}w~^{}q~}Wv~qv~Q{|v~}Uy|}v~|K"
"w~|L{|u~}|^{|k~}|s{|}x~}5y~}q{}v~|q{}y~f{}w~}o{}u~|^v~ty|}s~[{|u~y}v~y|w~|a{|w~}l{}w~}^{}w~|Ov~m{|w~}]w~}rv~Wv~"
"|y{}w~}\\{|w~|m{}w~|gv~|b{|v~h{}w~}u{}w~tv~a{|w~}q{|w~}`v~t{}w~t{|w~}b{}w~|m{|v~c{}w~}l{}w~}X{|w~}W`~`{|w~}pv~|"
"S{}v~|W{}w~}V{|v~bv~}lv~}r{|v~r{|v~|i{}w~}hv~|gu~t{|v~t{|v~}jv~}xh|y{|v~|mT~]{}w~]T~|^{}w~]{}U~|^{}w~ Hv~|ty~}X"
"{}g~|[w~|nw~|W{}u~}Mw~|V{}w~ov~1{|y~v{}x~}d{|y~|ay}x~y}ww|[{}w~}v{|v~|`{|Z~}8{|y~ro~o{|y~| Q{}w~R{}l~|V{|y}v~y}"
"|${|w~|m{}w~|\\{|}s~}w{|x~}W{|v~| xm~}T{|y}w~}|S{|v~|v{}w~}gm~}w{}x~}oy~y}x~rm~}w{}x~}v{}~}y|w{|v~u{|o~}t{}x~}o",
"t~^v|V{|w~}p{}w~|^{|w~}p{}w~|^{|w~}p{}w~|^{|w~}p{}w~|^{|w~}p{}w~|^{}w~}p{}w~}ev~|r{|v~h|lv~}I{}w~}i|_{}w~}i|_{}"
"w~}i|_{}w~}i|V{}w~}M{}w~}M{}w~}M{}w~}_v}u~r}nv~}h{}w~|tv~|uv~iv~}c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|"
"_{|r~}_v~}r{}w~q{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}Z{|v~|V{}w~}mv~}aw~}u{|t~|I{}w~L{}w~L{}w~L{}w~"
"L{}w~L{}w~V{}w~|kv~j{}w~}O{|w~|k{}w~b{|w~|k{}w~b{|w~|k{}w~b{|w~|k{}w~Wv~Lv~Lv~Lv~W{}w~}l{|w~}`v~m{|w~}b{}w~}l{}"
"w~}b{}w~}l{}w~}b{}w~}l{}w~}b{}w~}l{}w~}b{}w~}l{}w~}eY|f{}w~}rw~y{|w~}a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|"
"m{}w~|^v~qv~]v~|m{|v~_v~qv~ Vw~yd~|{}x~|kw~yd~|{}x~|kw~r{|t~|r{}x~|kw~pu~|r{}x~|kw~pv~}q{}x~|[w~|T{}w~|s{|v~ G{"
"}v~T{}w~t{|y~}(]~|i{|Y~}h{|_~}d{|a~}bw~}kw~|aw~}kw~}\\{}w~}wv~|Xv~|u{}w~|cV~}    2v~| k{}w~| {{w~|tw~|W{|}m~}T{"
"}x~}v{|o~}l{|v~|v{}u~q{}w~+{|w~}F{}w~|Ox~Z{|Z~}+m| ww~|X{|v~k{}w~}W{}w~}K{}v~}K{|}v~}^w~}q{}w~}Ju~a{|t~|o{}v~U{"
"|v~|X{}u~}|wy|u~}]t~}y|{y|}q~} Z{|t~}| _{|}t~}\\v~`{|x~}s{}x~}o{|w~|t{}x~|kv~|p{|w~}`{}w~}n{|u~cv~}M{}w~}f{|v~|"
"e{}w~}L{}w~}Tv~}m{}n~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}|u~}R{}w~}V{}w~|v{|w~|x{}x~}uv~|h{}w~|t{|v~uv~iv~}c{|v~|e{}h~"
"}cv~}c{|v~|g{}h~}Qy|y}p~W{|v~|Z{|v~h{}w~}a{|v~s{|v~|e{}w~}v{}x~}t{|w~uv~|a{}r~}P{|v~|P{}v~}O{|w~}I{|w~|J{|w~|  "
"n{|y}l~^v~kv~a{}w~|Ov~|l{}w~|b{}w~|k{}w~|Yw~}Vv~|l{}w~|`v~m{|w~}Wv~Lv~Tw~}|u~Kv~_v~mv~mv~hv~m{|w~}b{}w~|l{|v~`v"
"~kv~c{}w~|l{}w~|Zv~Pu~}|Kv~S{|w~|m{}w~|^v~qv~b{}w~u{}x~|y{|w~uv~]{}r~V{}w~|s{|w~}R{|v~}X{|q~}Jw~|K{|q~}c{}g~}w|"
"}u~}5y~}pw~}p{}y~fv~|o{}u~]v~p{|t~\\v~}w{|w~}w~|a{}w~|l{|w~}]{}w~}y|Rv~m{|w~}]{}w~s{}w~}X{}w~}x{|v~\\{|w~|m{}w~"
"|h{|v~|b{|v~|i{}w~|u{}w~tv~|b{|w~}q{|w~}`v~t{}w~t{|w~}bv~kv~c{}w~|l{|w~}X{|w~}Wv~jv~`v~|p{}w~}T{}v~|V{}w~}V{|v~"
"|cv~|lv~}r{|v~r{|v~|i{}w~}hv~|g{}v~}u{|v~tu~|jv~}c{|v~|n{|T~]{}w~]T~}^{}w~]T~}^{}w~ I{|v~sy~}X{}g~|[w~m{}x~|Vu~"
"|#{|w~|p{|w~|2{|y~|w{|x~}d{|y~|3v~}v{}v~|Aw~}8{|y~|sw~x{|w~}p{|y~| Q{}w~  p{|w~|m{}w~|Y{|}v~}w{|x~}W{|v~|  jv~}"
"v{}v~|W{|w~o{}y~{}x~r{}n~}x{|w~uy|rw~|ty|t}|s{|w~o{}y~|}x~^{}w~|Wv~|p{|w~}^v~|p{|w~}^v~|p{|w~}^v~|p{|w~}^v~|p{|"
"w~}^v~|p{|v~f{|v~q{|v~Yv~}I{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~ev~}h{}w~|t{|v~uv~iv~}c{|v~|lv~}"
"c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|^{|t~}^v~}s{}w~p{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}Z{|v~|V{}w"
"~}n{|v~|aw~}t{}t~}W{|y}l~Y{|y}l~Y{|y}l~Y{|y}l~Y{|y}l~Y{|y}l~c{|y}l~j{}w~j{}w~|O{}w~|k{}w~|c{}w~|k{}w~|c{}w~|k{}"
"w~|c{}w~|k{}w~|Xv~Lv~Lv~Lv~W{}w~|l{|v~`v~m{|w~}b{}w~|l{|v~b{}w~|l{|v~b{}w~|l{|v~b{}w~|l{|v~b{}w~|l{|v~f{|Z~}f{}"
"w~|s{}x~|y{|w~}a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|^{}w~|s{|w~}]v~kv~_{}w~|s{|w~} Vw~yd~|{}x~|kw~yd"
"~|{}x~|kw~qt~|r{}x~|kw~qu~|q{}x~|kw~pv~}q{}x~|[w~|T{|w~}s{}w~} H{|v~|T{|w~|u{}y~({|]~}i{}X~g{|`~b{}b~aw~}kw~}aw"
"~}kw~}\\v~|w{}w~}X{}w~}uv~bw~}Z|    5x|v~}p| v{}w~| {|w~t{|w~S{|}n~|Vw~uv~|y{|}w~}m{}w~}t{}u~rw~}+{|w~}F{}w~|Ox"
"~Z{|Z~},{|m~ x{|w~|X{|v~k{}w~}W{}w~}L{}v~}H{}v~}`{}w~p{}w~}J{}v~`t~n{|v~|V{}v~X{}v~}q{}v~}^{|j~|v~| Z{|t~| ]{|}"
"u~}]{|w~}`{|x~|sw~|o{|w~|t{}x~|l{|v~nv~`{}w~}lv~}dv~}M{}w~}f{|v~|e{}w~}L{}w~}Tv~}m{}n~|h{}w~}hv~|Y{}w~}M{}w~}W{"
"}w~}{|t~S{}w~}V{}w~|u{}x~}y{|w~|uv~|h{}w~|sv~|vv~iv~}c{|v~|e{}k~}|av~}c{|v~|g{}w~}t|y}u~}M{|}s~}X{|v~|Z{|v~h{}w"
"~}`v~}t{}v~d{}w~}vw~|sw~|w{|v~a{|v~}v~|Q{|v~|Q{|u~N{|w~}Hw~|J{|w~|  p{}h~|_v~k{}w~|bv~|Ov~k{}w~|bv~j}v~|Yw~}Vv~"
"k{}w~|`w~}m{|w~}Wv~Lv~Tq~}Jv~_w~}mv~mv~hw~}m{|w~}bv~|l{|v~`v~kv~|dv~k{}w~|Zv~P{}r~}y|Pv~S{|w~|m{}w~|^{}w~|s{|w~"
"}b{|w~|vw~|xw~|w{|w~}\\s~|Uv~sv~|Ru~W{|s~}|Iw~|I{|}t~}d{|u~}w|}g~}5{|y~|p{|x~|p{}y~fv~|o{|v~}]v~n{}v~|^{}w~|ts~"
"`v~|l{|v~\\{}p~}Xw~}m{|w~}]{|w~|tv~|Xv~|wv~|]{|w~|m{}w~|h{|v~|q{}x~}q{|v~|iv~|u{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{"
"|w~}bv~kv~|dv~|l{|v~X{|w~}Wv~|l{|v~a{|v~nv~U{|v~}U{}w~}Uv~}d{|v~|l{}v~r{|v~r{|v~|i{}w~}hv~|fu~|v{|v~u{}v~}iv~}c"
"{|v~|n{|T~]{}w~]T~}^{}w~]T~}^{}w~ rw|V{|w~}sy~}X{|w}u~q}Zw~m{}x~|V{}v~\"{|v~ow~|2{|y~|w{|w~d{|y~|4{}w~}v{|v~?w~"
"}8{|y~|sw~vw~}q{|y~| Q{}w~  p{|w~|m{}w~|Ux~}w{|x~}W{|v~|  i{}w~|v{|v~Ww~|p{|y~|{}x~`{}x~|j{|x~}bw~|p{|y~}{}x~^{"
"}w~|X{|v~nv~_{|v~nv~_{|v~nv~_{|v~nv~_{|v~nv~_{|w~}nv~|g{}w~}q{|v~Yv~}I{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}"
"M{}w~}Z{|v~ev~}h{}w~|sv~|vv~iv~}c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|lv~}c{|v~|]{}u~|^v~}t{|w~|p{|v~|i{|v~h{}w~}"
"f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}Z{|v~|V{}w~}n{}v~|aw~}s{|s~|[{}h~|\\{}h~|\\{}h~|\\{}h~|\\{}h~|\\{}h~|f{}h~j}v~"
"jv~|Ov~j}v~|cv~j}v~|cv~j}v~|cv~j}v~|Xv~Lv~Lv~Lv~Wv~|l{|v~`w~}m{|w~}bv~|l{|v~bv~|l{|v~bv~|l{|v~bv~|l{|v~bv~|l{|v"
"~f{|Z~}fv~|t{}x~|wv~a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|]v~sv~|]v~kv~|_v~sv~| Vw~yd~|{w~jw~yd~|{w~j"
"w~rr~|sw~jw~ru~|pw~jw~pv~}qw~Zw~|Sv~sv~ H{|v~|Rw~}uy~}({|]~}i{}X~|g{}b~|a{}d~|aw~}kw~}aw~}kw~}]{|v~v{|v~X{|v~v{"
"|w~}b{}x~}     pf~ v{|w~ {{|w~t{|x~}P{|y~}r~W{}x~|v{}w~u{}w~mv~r{}u~t{|w~|+{|v~F{}w~|Ox~Z{|Z~},{|m~ x{}w~W{|v~k"
"{}w~}W{}w~}M{}v~}F{}v~a{|w~|p{}w~}Iv~|au~}mv~}Vv~|Y{|v~}o{|v~|]{}m~|{v~| Z{|r~}| c{|}r~}]{|w~}`{|x~|sw~|nw~|t{}"
"x~k{}w~}n{}w~}a{}w~}l{|v~|e{}v~M{}w~}f{}v~d{}w~}L{}w~}T{}v~mr|v~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}y{|t~T{}w~}V{}w~|u"
"{|w~y{}w~tv~|h{}w~|s{|v~vv~i{}v~c{|v~|e{}w~}r|]{}v~c{|v~|g{}w~}q{}v~}K{|t~|Y{|v~|Z{|v~h{}w~}`{}v~tv~|d{|v~w{|w~"
"|s{}x~}w{}w~}av~}{}v~Q{|v~|R{|u~M{|w~}H{}x~}J{|w~|  r{|f~|_w~}k{}w~|bv~|Ov~k{}w~|b`~|Yw~}Vv~k{}w~|`w~}m{|w~}Wv~"
"Lv~Tq~Iv~_w~}mv~mv~hw~}m{|w~}bv~jv~`v~k{}w~|dv~k{}w~|Zw~}O{}o~}|Sv~S{|w~|m{}w~|^{|w~}s{}w~|b{|w~}w{|w~w{}x~}w{|"
"w~|\\{|u~}T{}w~|u{|w~}Ru~V{|s~}|Iw~|J{|}s~}d{|w~|s{|}k~|3y~}p{|x~}p{}y~fv~mv~|]v~m{}v~_{|w~}rt~`v~jv~Z{}r~}Xw~}"
"m{|w~}\\w~}u{|w~}X{|w~}v{}w~}]{|w~|m{}w~|h{|v~|q{}x~}pv~|iv~t{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{|w~}bv~k{}w~|dv~jv"
"~X{|w~}W{}w~|l{|v~a{}w~}n{}w~}W{|u~T{}w~}U{}w~}d{}v~k{}v~|s{|v~r{}v~h{}w~}hv~|f{|u~|w{|v~v{}u~h{}v~c{|v~|n{|T~]"
"{}w~]T~|^{}w~]{}U~}^{}w~ s{|w~V{|w~}sy~}S{|v~Pw~|nw~|V{|w~}!{}v~|q{}x~|1y~}vw~|e{}y~ci|]{}w~u{|w~|?w~}7y~}sw~v{"
"|w~|r{}y~ P{}w~  p{|w~|m{}w~|Ux~}w{|x~}W{|v~| Fi|U{|w~|u{}w~X{}x~}p{|y~}y{}x~a{|w~i{|x~}c{}x~}p{|y~}y{}x~^{}w~|"
"X{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~}`{}w~}n{}w~}`{}w~|n{}w~}h{|v~p{|v~Y{}v~I{}w~}M{}w~}M{}w~}M{}w~}"
"D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{|v~|h{}w~|s{|v~vv~i{}v~c{|v~|l{}v~c{|v~|l{}v~c{|v~|l{}v~c{|v~|l{}v~c{|v~|^{}s~|_"
"{}v~u{|w~|o{|v~|i{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}Z{|v~|V{}w~}o{|u~`w~}q{}t~|^{|f~|^{|f~|^{|f~|^{|f~|"
"^{|f~|^{|f~|h{|P~jv~|O`~|c`~|c`~|c`~|Xv~Lv~Lv~Lv~Wv~jv~`w~}m{|w~}bv~jv~bv~jv~bv~jv~bv~jv~bv~jv~f{|Z~}fv~|u{}x~}"
"vv~a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|]{}w~|u{|w~}\\v~k{}w~|_{}w~|u{|w~} Uw~yq}w~r}yw~jw~yd|yw~jw~"
"sp~|tw~jw~su~|ow~jw~pv~}qw~Zw~|S{}w~}u{|w~} Hv~|Q{}w~|w{|y~|({|\\~iW~|f{}d~|_e~|`w~}kw~}aw~}kw~|]{}w~}uv~Wv~|w{"
"}w~|b{}x~}     q{|g~| v{|w~({}Z~X{|y~|{|}u~}Y{|w~uw~|tw~}o{|w~}q{}u~u{}w~*{|v~F{}w~|*m|}w~l|,{|m~ xw~}W{|v~k{}w"
"~}W{}w~}N{}v~}Dv~|bw~}o{}w~}Iv~|au~|m{}w~}W{|v~X{}v~m{}v~\\{|p~}xv~| Y{}p~}| i{|}p~}|]{}w~}`{|x~|sw~mw~|t{}x~kv"
"~}n|}v~a{}w~}kv~}e{}v~M{}w~}f{}v~d{}w~}L{}w~}T{}v~dv~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}x{|t~U{}w~}V{}w~|tw~|{w~}tv~|"
"h{}w~|rv~}wv~i{}v~c{}v~d{}w~}T{}v~c{}v~f{}w~}p{}v~|Ju~}Y{|v~|Z{|v~h{}w~}_v~|v{|v~bv~|x{|w~r{}w~wv~|b{}v~xv~}R{|"
"v~|Ru~|M{|w~}H{|w~J{|w~|  s{|q~t}v~|_w~}k{}w~|bv~Nv~k{}w~|b`~|Yw~}Vv~k{}w~|`w~}m{|w~}Wv~Lv~Tp~Jv~_w~}mv~mv~hw~}"
"m{|w~}bv~jv~`w~}k{}w~|dv~k{}w~|Zw~}N{|m~|Uv~S{|w~|m{}w~|]v~t{|v~`v~w{}x~}w{|x~}w{}w~[{|u~|T{|w~}u{}w~|S{}v~|V{|"
"x}t~}Jw~|K{|s~y}|d{|y~}n{|}p~}1y~}p{}w~p{}y~fv~mv~\\v~lv~|`{}w~|r{|v~}`v~jv~\\{|p~}Xw~}m{|w~}\\{}w~u{}w~|Xv~|v{"
"|v~]{|w~|m{}w~|h{|v~p{}w~pv~}iv~t{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{|w~}bw~}k{}w~|dv~jv~X{|w~}W{}w~|l{|w~}av~|n{|v"
"~Wu~|T{}w~}U{}v~dv~}k{|v~}s{|v~s{|v~}h{}w~}hv~|e{}u~|x{|v~w{}u~|h{}v~c{}v~l{|u~}\\|]{}w~][|u~|]{}w~\\{}v~}c|u~}"
"]{}w~ s{|w~V{|w~}sy~}S{|v~P{}x~}o{|w~`{|a~}+u~|rw~|1y~}v{}w~ex~d{|j~}]{}w~}v{|v~|@w~}7y~}sw~u{}w~rx~ P{}w~  p{|"
"w~|m{}w~|Ux~}w{|x~}  w{|j~}V{|v~|v{}w~}Xw~oy~}x{}x~aw~|i{|x~|cw~ox~x{}x~^{}w~|Xv~}n|}v~`v~}n|}v~`v~}n|}v~`v~}n|"
"}v~`v~}n|}v~a{|b~h{}v~p|}v~Y{}v~I{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{|v~|h{}w~|rv~}wv~i{}v~c{"
"}v~k{}v~c{}v~k{}v~c{}v~k{}v~c{}v~k{}v~c{}v~^{}q~|`{}v~v{|w~}n{}v~h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}Z{"
"|v~|V{}w~}p{|u~|`w~}p{|t~}`{|q~t}v~|_{|q~t}v~|_{|q~t}v~|_{|q~t}v~|_{|q~t}v~|_{|q~t}v~|i{|q~t}`~|kv~N`~|c`~|c`~|"
"c`~|Xv~Lv~Lv~Lv~Wv~jv~`w~}m{|w~}bv~jv~bv~jv~bv~jv~bv~jv~bv~jv~f{|Z~}fv~u{|x~}uv~a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m"
"{}w~|a{|w~|m{}w~|]{|w~}u{}w~|\\w~}k{}w~|_{|w~}u{}w~| U{}x~|q{}w~q{|w~j{}x~|b{|w~j{}x~|uu~|u~|v{|w~j{}x~|uu~|o{|"
"w~j{}x~|qv}|r{|w~[{|w~|S{|v~uv~| TZ~}a{|w~}wx~'{|\\~iW~|ee~|^{|g~}_w~}kw~}aw~}kw~|]v~|u{}w~|X{}w~}wv~|b{|w~|   "
"  r{}g~ u{|w~({}Z~X{|y~|w{}v~|Zw~|v{|w~s{|w~o{|w~}p{}u~vw~})v~Fv~| w{}w~ x{|m~ y{|w~|Vv~|lv~|W{}w~}O{}v~}C{}w~}"
"c{|w~n|}w~}v|N{}w~}au~l{|v~Wv~}Xv~}m{|v~|[{|y}w~y}|x{|v~ V{|}p~}|XY|X{|}q~}|Z{}w~}`{|x~|sw~mw~|tw~l{|b~|b{}w~}k"
"{}v~e{|v~|N{}w~}fv~}d{}w~}L{}w~}T{|v~|ev~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}w{|t~V{}w~}V{}w~|t{}w~|w~|tv~|h{}w~|r{|v~"
"wv~i{|v~|d{}v~d{}w~}T{|v~|d{}v~f{}w~}o{}v~J{|u~Y{|v~|Z{|v~h{}w~}_{}w~}v{}w~}b{}w~}x{}x~}r{|w~wv~b{|v~|x{|v~|S{|"
"v~|S{}v~|L{|w~}Gw~|K{|w~|  t{|u~}|q{}w~|_v~k{}w~|bv~Nv~k{}w~|b`~|Yw~}Vv~k{}w~|`w~}m{|w~}Wv~Lv~Tw~}|u~Kv~_w~}mv~"
"mv~hw~}m{|w~}bv~jv~`w~}k{}w~|dv~k{}w~|Zw~}L{|}o~}Vv~S{|w~|m{}w~|]{}w~}u{}w~}`{}w~|xw~|w{|w~wv~\\{|s~Sv~uv~S{}v~"
"|O{}v~}Kw~|L{|v~}|_{|~|j{|y}x~y}|/x~q{|v~}qx~fv~m{}x~}\\v~l{}w~|`v~pv~}`v~jv~]n~}Xw~}m{|w~}\\{|w~|vv~X{|v~t{}w~"
"|^{|w~|m{}w~|h{|v~p{}w~pv~|iv~t{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{|w~}bw~}k{}w~|dv~jv~X{|w~}W{}w~}l{}w~}b{|v~lv~|Y"
"{}v~|S{}w~}U{|v~}f{|v~|ju~|t{|v~s{}v~|h{}w~}hv~|dt~}y{|v~y{|t~|g{|v~|d{}v~k{|u~|?{}w~>u~|b{|v{}w~[{}v~|e{}v~}\\"
"{}w~ s{|w~V{|w~}sy~}S{|v~P{|w~o{}x~}`{|a~}+{|u~}|u{|w~0{}y~v{|w~}g{|y~}d{|j~}\\{}v~|w{|v~}Aw~}7{}y~sw~tw~}t{|y~"
"} P{}w~  p{|w~|m{}w~|Ux~}w{|x~}  w{|j~}W{|v~|vv~}X{}x~|p{}y~|x{}x~b{}x~}hw~c{}x~}p{}y~|x{}x~^v~X{|b~|b{|b~|b{|b"
"~|b{|b~|b{|b~|b{}b~}id~Y{|v~|J{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~f{}v~g{}w~|r{|v~wv~i{|v~|d{}v"
"~k{|v~|d{}v~k{|v~|d{}v~k{|v~|d{}v~k{|v~|d{}v~_{}v~}u~|a{|v~|ww~}m{}v~h{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w~}f{|v~h{}w"
"~}Z{|v~|V{}w~}sy|s~_w~}n{}u~|b{|u~}|q{}w~|`{|u~}|q{}w~|`{|u~}|q{}w~|`{|u~}|q{}w~|`{|u~}|q{}w~|`{|u~}|q{}w~|j{|u"
"~}|q{}a~|kv~N`~|c`~|c`~|c`~|Xv~Lv~Lv~Lv~Wv~jv~`w~}m{|w~}bv~jv~bv~jv~bv~jv~bv~jv~bv~jv~.v~v{|w~tv~a{|w~|m{}w~|a{"
"|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|\\v~uv~[w~}k{}w~|^v~uv~ T{}x~}q{}w~q{|x~}j{}x~}b{|x~}j{}x~}vu~|{|u~|w{|x~}j{}"
"x~}vu~|n{|x~}j{}x~}b{|x~}[{|w~Qv~|w{|v~ SZ~}`v~x{|y~}'{|]~}iW~|e{|g~}\\{}i~}^w~}kw~}aw~}l{|w~|^{|v~t{|w~}X{|v~x"
"{|v~`w~}     m{|v~ jw|({}Z~X{|y~|v{}w~}[{}x~}u{}x~}s{|w~o{}w~}o{}u~x{|w~|)v~Fv~ v{}w~  g{}w~Uv~|lv~|W{}w~}P{}v~"
"}B{|v~c{|_~|O{}w~}a{}v~l{|v~X{|v~|Y{|v~|lv~|N{|v~ S{|}p~|[{|Z~}[{|}p~}|X{}w~}`{|x~|sw~|nw~|u{|x~}l{}b~}b{}w~}k{"
"|v~e{|v~}N{}w~}g{|v~}d{}w~}L{}w~}T{|v~}ev~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}v{|t~W{}w~}V{}w~|t{|r~sv~|h{}w~|q{}w~}xv"
"~i{|v~}dv~}d{}w~}T{|v~}dv~}f{}w~}nv~}J{}v~Y{|v~|Z{|v~|i{}w~}_{|v~vv~|b{}w~}xw~|qw~|y{|v~bv~}v{}v~S{|v~|T{}v~}K{"
"|w~}G{}x~}K{|w~|  tv~}n{}w~|_v~kv~|bv~|Ov~k{}w~|bv~Bw~}Vv~k{}w~|`w~}m{|w~}Wv~Lv~Tw~}{|u~|Mv~_w~}mv~mv~hw~}m{|w~"
"}bv~|kv~`v~k{}w~|dv~k{}w~|Zw~}Iy|}q~Wv~S{|w~|m{}w~|]{|v~uv~_{|w~|xw~uw~|y{|w~}\\r~}T{|w~|w{}w~}T{}v~|M{|v~Kw~|L"
"{}w~} O{}y~|rt~|s{|y~}fv~|nw~}\\v~l{|w~}`w~}p{}w~|`v~|kv~^u~}|Qw~}m{|w~}[w~}w{}w~}X{}w~|t{|w~}^{|w~|m{}w~|h{|v~"
"pv~pv~|iv~t{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{|w~}bv~k{}w~|dv~|l{|v~X{|w~}W{|w~}l{}w~|b{}w~}l{}w~}Z{|v~}R{}w~}T{}v"
"~f{}v~i{|u~t{|v~t{|u~g{}w~}hv~|cr~}v~}s~}f{|v~}dv~}j{|u~|@{}w~?u~|b{}~|w{}w~vy~a{}v~|g{}v~}b{}~|w{}w~vy} {{}w~|"
"W{|w~}sy~}S{|v~Ow~}q{|w~|`{|a~}){}u~}vw~}0{|y~}v{}w~}p{|t{}y~|d{|j~}[{|v~|vv~}Bw~}7{|y~}tw~t{|w~|u{}y~| P{}w~  "
"p{|w~|m{}w~|Ux~}w{|x~}  w{|j~}X{}v~v{|v~}X{|w~p{|y~|w{}x~bw~h{}x~|d{|w~p{|y~}w{}x~^v~X{}b~}b{}b~}b{}b~}b{}b~}b{"
"}b~}b`~j{}d~Y{|v~}J{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~fv~}g{}w~|q{}w~}xv~i{|v~}dv~}k{|v~}dv~}k"
"{|v~}dv~}k{|v~}dv~}k{|v~}dv~}`{}v~|{|u~|b{|v~}x{}x~}lv~}h{|v~|i{}w~}f{|v~|i{}w~}f{|v~|i{}w~}f{|v~|i{}w~}Z{|v~|V"
"{}e~|_w~}m{|u~bv~}n{}w~|`v~}n{}w~|`v~}n{}w~|`v~}n{}w~|`v~}n{}w~|`v~}n{}w~|jv~}n{}w~Tv~|Ov~Lv~Lv~Lv~Av~Lv~Lv~Lv~"
"Wv~|l{|v~`w~}m{|w~}bv~|kv~bv~|kv~bv~|kv~bv~|kv~bv~|kv~.v~vw~|u{|v~a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}"
"w~|\\{|w~|w{}w~}[v~k{}w~|^{|w~|w{}w~} T{|w~q{}w~q{}x~|j{|w~b{}x~|j{|w~wu~|x{|u~|x{}x~|j{|w~wu~|m{}x~|j{|w~b{}x~"
"|[{|w~Q{|w~}w{}w~} SZ~}`{}w~|y{}y~|'{|n~y}~|n~}i{}k~x}k~c{|i~}Z{}j~]w~}kw~}a{}w~l{|w~|^{}w~}sv~Wv~|y{}w~}`{}w~|"
"     mv~|  o{}Z~X{|y~|v{|w~}\\{|w~t{}x~|rw~|p{}w~}n{}u~yw~}(v~|Gv~ v{}w~  gw~}U{}w~}m{|v~V{}w~}Q{}v~}A{|v~c{|_~"
"|O{}w~}a{}v~l{|v~X{}v~X{|v~k{}w~}N{}w~} Q{|}p~}|^{|Z~}^{|}p~}|U{}w~}`{|x~}sw~|o{|w~|u{}x~|l`~b{}w~}k{|v~|eu~N{}"
"w~}g{}v~|d{}w~}L{}w~}Su~ev~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}u{|t~X{}w~}V{}w~|ss~}sv~|h{}w~|q{|v~|yv~hu~e{|v~|d{}w~}"
"Su~e{|v~|f{}w~}n{}v~|K{|v~|Z{|v~|Yv~|i{}w~}^v~|x{}v~a{|v~y{|w~|q{}x~}y{}w~}c{}v~tv~}T{|v~|U{|v~}J{|w~}G{|w~K{|w"
"~|  u{|v~m{}w~|_v~kv~a{}w~|O{}w~|l{}w~|bv~|Cw~}V{}w~|l{}w~|`w~}m{|w~}Wv~Lv~Tw~}y{|u~|Nv~_w~}mv~mv~hw~}m{|w~}bv~"
"|l{|v~`v~kv~cv~|l{}w~|Zw~}D{|}u~}Xv~S{|w~|m{}w~|\\{}w~|w{|w~}^w~}y{|w~u{}x~}y{}w~|]{}q~|Tv~wv~|U{|v~}K{}w~|Lw~|"
"Lv~ N{|x~s{}x~{w~|tx~|fv~|o{|v~\\v~l{|w~}a{|w~|p{}w~_{}w~|l{|v~_{}v~|Ow~}m{|w~}[{}w~|xv~X{|v~rv~|_{|w~|m{}w~|h{"
"|v~|qv~pv~|iv~|u{}w~t{}w~|b{|w~}q{|w~}`v~t{}w~t{|w~|bv~kv~c{}w~|l{|v~X{|w~}Vv~l{}w~|bv~|l{|v~[{|v~}Q{}w~}T{|v~}"
"h{|v~|hu~}u{|v~u{|u~|g{}w~}hv~|b{}f~|du~e{|v~|i{|u~|A{}w~@u~|b{}x~|x{}w~ww~a{}v~|i{}v~}b{}x~|x{}w~w{}y~} {}w~|W"
"{|v~sy~}S{|v~O{|w~}s{}w~}^q|}v~q|'{}t~|{|w~}.x~u{}v~}|wy|}y~tx~/{|v~|v{}w~}Cw~}6x~tw~s{}w~ux~ O{}w~  p{|w~|m{}w"
"~|Ux~}w{|x~}  B{}w~}v{|v~|Ww~|q{|y~}v{}x~c{}x~|i{}x~}cw~|q{|y~}v{}x~_{|v~X`~b`~b`~b`~b`~c{|`~|kc~Xu~J{}w~}M{}w~"
"}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~g{|v~}g{}w~|q{|v~|yv~hu~e{|v~|ju~e{|v~|ju~e{|v~|ju~e{|v~|ju~e{|v~|a{}"
"v~|x{|u~|bu~y{}w~l{|v~|gv~|i{}w~}ev~|i{}w~}ev~|i{}w~}ev~|i{}w~}Z{|v~|V{}f~|^w~}l{|v~|d{|v~m{}w~|a{|v~m{}w~|a{|v"
"~m{}w~|a{|v~m{}w~|a{|v~m{}w~|a{|v~m{}w~|k{|v~m{}w~T{}w~|Ov~|Mv~|Mv~|Mv~|Bv~Lv~Lv~Lv~W{}w~|l{|v~`w~}m{|w~}bv~|l{"
"|v~bv~|l{|v~bv~|l{|v~bv~|l{|v~bv~|l{|v~.v~|x{}x~|t{|v~a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|a{|w~|m{}w~|[v~wv~|[v"
"~kv~\\v~wv~| Sw~|r{}w~r{|w~hw~|d{|w~hw~|yu~|v{|u~y{|w~hw~|yu~|m{|w~hw~|d{|w~Z{|w~Pv~wv~| SZ~}_w~}yx~%n~{|~{|o~|"
"i{|l~}|}|l~}b{}j~Xk~|]w~}kw~}a{}w~l{}w~]v~|s{}w~|X{}w~}yv~|_w~}     mv~}  g{}x~}t{}x~}O{|y~|uw~}\\{}x~|t{}x~|rw"
"~|p{|w~}m{}u~}w~|({}w~|H{|w~} v{}w~  h{|w~|U{}w~}m{|v~V{}w~}R{}v~}@{|v~c{|_~|Ov~|a{|v~l{}w~}Xv~}X{|v~k{}w~}Nv~|"
" N{|}p~}|a{|Z~}a{|}p~}|R{|w}|_x~}s{}x~}o{}w~|v{|w~l{}`~|c{}w~}k{|v~|e{}v~|O{}w~}gu~c{}w~}L{}w~}S{}v~|fv~|h{}w~}"
"hv~|Y{}w~}M{}w~}W{}w~}t{|t~Y{}w~}V{}w~|s{}t~rv~|h{}w~|p{}w~}yv~h{}v~|f{}v~c{}w~}S{}v~|f{}v~e{}w~}mv~}K{|v~|Z{|v"
"~|Yv~|iv~|^{}w~}xv~}`v~|{|w~p{}w~yv~|d{|v~|t{|v~|U{|v~|V{|u~I{|w~}Fw~|L{|w~|  u{}w~|mv~|_v~|m{|v~a{}w~}O{}w~|lv"
"~|b{}w~|Cw~}V{}w~|lv~|`w~}m{|w~}Wv~Lv~Tw~}x{|u~|Ov~_w~}mv~mv~hw~}m{|w~}b{}w~|l{|w~}`v~kv~c{}w~|lv~|Zw~}B{|u~Xv~"
"S{|w~|m{}w~|\\{|w~}w{}w~|^v~y{}x~}u{|x~}y{}w~]{|v~|}v~T{}w~|y{|w~}U{|v~}J{|w~}Lw~|M{|w~} Mx~}v{|w~|{|w~|v{}x~e{"
"}w~|o{}v~\\v~l{|w~}a{|w~|pw~}_{}w~|l{|w~}_v~Mw~}m{|w~}[{|w~}y{|w~}X{}w~|r{}w~}_{|w~|m{}w~|h{|v~|qv~|r{|v~|i{}w~"
"|u{}w~tv~|b{|w~}q{|w~}`v~t{}w~t{}w~|bv~kv~c{}w~|l{|w~}X{|w~}Vv~lv~b{}v~jv~|\\u~P{}w~}S{}v~|iu~g{|t~|w{|v~v{}u~}"
"f{}w~}hv~|a{}h~|c{}v~|f{}v~g{|u~|B{}w~Au~|b{}v~|y{}w~xu~a{}v~|k{}v~}b{}v~|y{}w~x{}w~}!{}w~|Vv~sy~}S{|v~O{|u~}y|"
"{y|u~}T{|w~}Lw}|P{|}p~}-{|y~}u{}l~u{}y~|.{|v~|v{}w~}Dw~}6{|y~}uw~rw~}w{}y~| O{}w~  p{|w~|m{}w~|Ux~}w{|x~}  C{}w"
"~}v{|v~|W{}x~}px~u{}x~d{|w~i{}x~}c{}x~}px~u{}x~_{}w~}Y{}`~|d{}`~|d{}`~|d{}`~|d{}`~|d{}w~}j|}w~}l{|c~X{}v~|K{}w~"
"}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~gu~|g{}w~|p{}w~}yv~h{}v~|f{}v~i{}v~|f{}v~i{}v~|f{}v~i{}v~|f{}v~"
"i{}v~|f{}v~a{}v~|v{|u~|c{}v~|}w~|l{}v~fv~|iv~|ev~|iv~|ev~|iv~|ev~|iv~|Z{|v~|V{}h~}\\w~}k{}w~|d{}w~|mv~|a{}w~|mv"
"~|a{}w~|mv~|a{}w~|mv~|a{}w~|mv~|a{}w~|mv~|k{}w~|mv~|U{}w~}O{}w~|M{}w~|M{}w~|M{}w~|Bv~Lv~Lv~Lv~W{}w~}l{}w~}`w~}m"
"{|w~}b{}w~|l{|w~}b{}w~|l{|w~}b{}w~|l{|w~}b{}w~|l{|w~}b{}w~|l{|w~}.{}w~|y{}x~|s{|w~}a{|w~|m{}w~|a{|w~|m{}w~|a{|w"
"~|m{}w~|a{|w~|m{}w~|[{}w~|y{|w~}Zv~kv~\\{}w~|y{|w~} R{|w~r{}w~rw~}h{|w~dw~}h{|w~y{|w~|t{|w~}yw~}h{|w~y{|w~|lw~}"
"h{|w~dw~}Z{|w~P{}w~|y{|w~} Rs}v~g}|_{}w~{|y~}%{|p~|{|~yp~}g{}m~{}~{}m~|a{}l~|X{|m~}\\w~}kw~}a{|w~|mv~]v~r{}w~}X"
"{|v~{|v~^{}w~}     n{}v~  gw~|tw~|O{|y~|uw~}]{|x~}sw~|rw~|p{|v~l{}r~}'{|w~}H{|w~} v{}w~  h{|w~T{|v~m{}w~}V{}w~}"
"S{}v~}?{|v~c{|_~|Ov~|`v~|m{}w~}Y{|v~W{|v~k{}w~}O{|v~ J{|}p~}|d{|Z~}d{|}p~}|-w~s{|w~ov~|v{}x~|lv~|j{|v~c{}w~}k{}"
"v~cv~}O{}w~}h{}v~|c{}w~}L{}w~}Rv~}fv~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}rt~Z{}w~}V{}w~|ru~}rv~|h{}w~|p{|v~|{v~h{|v~}g"
"{|v~}c{}w~}Rv~}g{|v~}e{}w~}m{|v~|L{|v~|Z{|v~|Y{}w~}j{|v~|^{|v~|{|v~_{}w~}{}x~}p{|w~yv~cv~}r{}v~U{|v~|W{|u~|I{|w"
"~}F{}x~}L{|w~|  u{}w~|n{|v~|_v~}m{}w~}a{|w~}O{|w~}m{|v~|b{}w~}Cw~}V{|w~}m{|v~|`w~}m{|w~}Wv~Lv~Tw~}vu~|Pv~_w~}mv"
"~mv~hw~}m{|w~}b{|w~}l{}w~}`v~|m{|w~}c{|w~}lv~|Zw~}@v~|Yv~S{|w~}mv~|[v~wv~]{}w~|{w~|u{|w~yw~}]v~}y{}v~U{|w~}y{}w"
"~|V{|v~}I{|w~}Lw~|M{|w~} M{|w~x}v~}x{}v~x}w~|e{}w~}ou~|]v~l{|w~|a{|w~p{}w~|_{|w~}l{}w~}`{|w~}Mw~}m{|w~}Zv~y{}w~"
"|Y{|v~q{|v~_{|w~}m{}w~|gv~|r{|v~|r{|v~h{}w~}u{}w~tv~a{|w~}q{|w~}`v~t{}w~t{}w~|bv~|m{|w~}c{|w~}l{}w~}X{|w~}V{}w~"
"|n{|w~}bv~}j{}v~]{}v~|P{}w~}Ru~j{}v~|f{|t~}|y{|v~x{|t~}e{}w~}hv~|`{|}l~}`v~}g{|v~}f{|u~|C{}w~Bu~|`u~|{}w~yu~|`{"
"}v~|m{}v~}a{|u~|{}w~y{}v~}!{}w~|Vv~|ty~}S{|v~P{|g~}U{|w~}Lw~|N{|r~}+{}y~|u{|}o~}v{|y~}+v~}v{}v~Ew~}5{}y~|vw~r{|"
"w~|y{|y~} N{}w~  p{|w~}m{}w~|Ux~}w{|x~}  Dv~}v{}v~|W{|w~p{}y~|u{}x~dw~|j{}w~c{|w~p{}y~|u{}x~`{}v~|Yv~|j{|v~dv~|"
"j{|v~dv~|j{|v~dv~|j{|v~dv~|j{|v~dv~|j{|v~l{}w~}n{|v~Wv~}K{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~h{"
"|v~}f{}w~|p{|v~|{v~h{|v~}g{|v~}i{|v~}g{|v~}i{|v~}g{|v~}i{|v~}g{|v~}i{|v~}g{|v~}b{}v~|t{|u~|cq~|l{|v~}f{}w~}j{|v"
"~|e{}w~}j{|v~|e{}w~}j{|v~|e{}w~}j{|v~|Z{|v~|V{}k~}|Zw~}k{}w~}d{}w~|n{|v~|a{}w~|n{|v~|a{}w~|n{|v~|a{}w~|n{|v~|a{"
"}w~|n{|v~|a{}w~|n{|v~|k{}w~|n{|v~}U{|w~}O{}w~}M{}w~}M{}w~}M{}w~}Bv~Lv~Lv~Lv~W{|v~lv~|`w~}m{|w~}b{|w~}l{}w~}b{|w"
"~}l{}w~}b{|w~}l{}w~}b{|w~}l{}w~}b{|w~}l{}w~}Xt|X{}w~}{}x~}r{}w~}a{|w~}mv~|a{|w~}mv~|a{|w~}mv~|a{|w~}mv~|[{|w~}y"
"{}w~|Zv~|m{|w~}\\{|w~}y{}w~| Qw~}s{}w~s{}w~fw~}f{}w~fw~}y{|y~|r{|y~}y{}w~fw~}y{|y~|l{}w~fw~}f{}w~Y{|w~P{|v~y{}w"
"~| Kv~}J{|w~|}y~|${}r~}y{}~y{|q~f{|n~|{}~yn~}_m~|V{|o~}[w~}kw~}`w~}n{|w~}^{|w~}r{|v~Wv~{}w~}]v~|     o{|v~|  hw"
"~t{|w~N{|y~|uw~}]w~|s{}x~|rw~|ov~|l{}s~&{|w~}H{}w~| v{}w~  h{}x~}Sv~|nv~|V{}w~}T{}v~}>{}w~}Q{}w~}J{}v~_{}w~}mv~"
"}Y{}w~}Vv~|lv~|Ov~} G{|}p~}|0{|}o~}*{}x~rw~}q{}v~|w{}w~l{|v~hv~|d{}w~}ku~c{}v~}P{}w~}i{}u~b{}w~}L{}w~}R{}v~|gv~"
"|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}qt~[{}w~}V{}w~|r{}v~|rv~|h{}w~|o{}w~}{v~g{}v~|hu~|c{}w~}R{}v~|hu~|e{}w~}lv~}L{}v~Y"
"{|v~|Y{}v~j{}v~\\{}w~}{}w~}_{|v~{w~|ow~y|v~d{}v~pv~}V{|v~|Wu~|H{|w~}F{|w~L{|w~|  u{}w~m{}v~|_u~mv~|a{|v~Nv~|n{}"
"v~|b{|v~Cw~}Uv~|n{}v~|`w~}m{|w~}Wv~Lv~Tw~}uu~|Qv~_w~}mv~mv~hw~}m{|w~}b{|v~lv~|`v~}m{}w~}c{|v~m{|v~|Zw~}@{}w~|Yv"
"~S{|w~}mv~|[{}w~|y{|w~}]{|w~}{w~sw~y|w~}^{}w~}wv~}U{}w~yv~Uv~}Gw~}Lw~|M{|w~| L{|q~}v{}q~|d{|w~}p{|u~|]v~l{}w~|a"
"{|w~pv~^{|v~lv~|`{|w~|Mw~}m{|w~}Z{}w~y|v~X{}w~}pv~|`{|w~}mv~|gv~}r{|v~}r{}v~h{|v~u{}w~u{|w~}a{|w~}q{|w~}`{}w~|u"
"{}w~tv~av~}m{}w~}c{|v~lv~|X{|w~}V{|w~}n{}w~|c{|v~i{|v~|_{}v~}O{}w~}R{|v~}l{}v~|d{|r~y}v~y}s~}d{}w~}hv~|]{|}s~y}"
"|^{}v~|hu~|e{|v~}C{}w~C{}v~|^u~|}w~{}v~|^{}v~n{|v~}_{|u~|}w~{}v~} {}w~|V{}w~}ty~}S{|v~Q{}e~}V{|w~}Lw~|L{|t~*{|x"
"~|t{|y}u~}|u{|x~|*{}w~|v{|v~Fw~}5{|x~|ww|qw|y{|x~|   >{|w~}mv~|Ux~}w{|x~}  Ev~}v{|v~U{}x~|q{|y~}t{}x~e{}x~}j{}w"
"~b{}x~|q{|y~}t{}x~a{}v~}Y{|v~hv~|f{|v~hv~|f{|v~hv~|f{|v~hv~|f{|v~hv~|f{}v~hv~|n{|v~|n{|v~W{}v~}L{}w~}M{}w~}M{}w"
"~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~i{|u~|f{}w~|o{}w~}{v~g{}v~|hu~|h{}v~|hu~|h{}v~|hu~|h{}v~|hu~|h{}v~|hu~|c{}"
"v~|r{|u~|d{}s~|ku~|f{}v~j{}v~d{}v~j{}v~d{}v~j{}v~d{}v~j{}v~Y{|v~|V{}w~}r|Vw~}k{|w~|d{}w~m{}v~|a{}w~m{}v~|a{}w~m"
"{}v~|a{}w~m{}v~|a{}w~m{}v~|a{}w~m{}v~|k{}w~m{}u~U{|v~O{|v~M{|v~M{|v~M{|v~Bv~Lv~Lv~Lv~Vv~|n{|v~_w~}m{|w~}b{|v~lv"
"~|b{|v~lv~|b{|v~lv~|b{|v~lv~|b{|v~lv~|X{}u~X{|v~|x~}qv~|a{|w~}mv~|a{|w~}mv~|a{|w~}mv~|a{|w~}mv~|Z{}w~yv~Yv~}m{}"
"w~}[{}w~yv~ P{|w~}t{}w~t{|w~}f{|w~}h{|w~}f{|w~}yy|p{|}y{|w~}f{|w~}yy|l{|w~}f{|w~}h{|w~}Y{|w~Ov~y|v~ K{}w~}Hw~}y"
"~}\"{}t~}x{}~x{|s~d{|p~}y{}~y{|p~}]o~|T{}p~Zw~}kw~}`{}w~|o{}w~|^{}w~|qv~|X{}w~|v~|]{|v~|     o{}v~j{}  {|x~}t{|"
"x~}N{|y~|v{}w~}^{}x~}r{}x~}rw~|o{}v~k{}u~|%v~Hv~ u{}w~  hw~|S{}v~o{}v~U{}w~}U{}v~}>{|v~}Q{}w~}Ju~_{|v~n{|v~|Z{|"
"v~|Vv~}m{|v~|P{}v~ C{}o~}4{|o~}|({|x~}s{}w~}s{}u~|x{}w~|l{}w~}h{}w~}d{}w~}l{|v~}bu~|g{|}g{}w~}j{}u~|b{}w~}L{}w~"
"}R{|u~|hv~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}pt~\\{}w~}V{}w~|r{|v}qv~|h{}w~|nv~|v~g{|u~|j{}v~}b{}w~}R{|u~i{}v~}d{}w~}"
"l{|v~|M{}v~Y{|v~|Y{|v~|kv~}\\{|v~{v~|_{|v~|w~|o{}x~y}w~}e{|v~|p{|v~|W{|v~|X{}v~}G{|w~}F{|w~|M{|w~|  u{}w~|nu~|_"
"u~}o{}v~_v~}O{}w~}o{|u~|av~}Dw~}U{}w~}o{|u~|`w~}m{|w~}Wv~Lv~Tw~}t{}v~|Rv~_w~}mv~mv~hw~}m{|w~}av~|n{|v~_u~mv~|bv"
"~|n{}v~|Zw~}@{}w~|Yv~Rv~n{}v~|[{|w~}y{}w~|\\w~}|x~}s{}x~y}w~|_{}v~v{|v~|V{|w~y}w~}Vu~Fw~}Lw~|M{|w~| K{|s~}t{}s~"
"|bv~p{}u~}]v~|mv~`{|w~q{}w~}]v~}n{}v~_{|w~|Mw~}m{|w~}Yw~y}w~|Xv~o{|w~}`{|v~n{|v~|g{}v~r{}u~rv~}gv~|v{}w~uv~|a{|"
"w~}q{|w~}`{|w~}u{}w~u{|v~au~mv~|bv~}n{}v~Vv~Uv~nv~b{}w~}hv~}`{|v~}N{}w~}Q{|v~}n{}v~}b{|c~}c{}w~}hv~|Z{|v~Z{|u~|"
"j{}v~}c{|w~B{}w~B{}x~|\\u~}w~}v~|\\{}x~|m{}x~}]{|u~}w~}v~} {{v~|V{|v~|uy~}S{|v~R{}v~y|q~}|u~W{|w~}Lw~|J{}u~*{|x"
"~|e{|x~|({}x~}u{|w~F{|x}|4{|x~|e{|x~|   ={|v~n{|v~|Ux~}w{|x~}  Ew~|u{|x~}U{|x~}p{}j~}iw~j{}w~b{|x~}p{}j~}f{}v~}"
"X{}w~}h{}w~}f{}w~}h{}w~}f{}w~}h{}w~}f{}w~}h{}w~}f{}w~}h{}w~}fv~}h{}w~}n{}w~}m{|v~Vu~|g{|}c{}w~}M{}w~}M{}w~}M{}w"
"~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~j{|u~}e{}w~|nv~|v~g{|u~|j{}v~}g{|u~|j{}v~}g{|u~|j{}v~}g{|u~|j{}v~}g{|u~|j{}v~}c{"
"}v~|p{|u~|e{|t~}k{}v~}e{|v~|kv~}d{|v~|kv~}d{|v~|kv~}d{|v~|kv~}Y{|v~|V{}w~}Mw~}k{}w~|d{}w~|nu~|a{}w~|nu~|a{}w~|n"
"u~|a{}w~|nu~|a{}w~|nu~|a{}w~|nu~|k{}w~|nt~|Uv~}Ov~}Mv~}Mv~}Mv~}Cv~Lv~Lv~Lv~V{}v~nv~}_w~}m{|w~}av~|n{|v~`v~|n{|v"
"~`v~|n{|v~`v~|n{|v~`v~|n{|v~W{}u~Wr~q{|v~_v~n{}v~|`v~n{}v~|`v~n{}v~|`v~n{}v~|Z{|w~y}w~}Yu~mv~|[{|w~y}w~} O{}w~}"
"u{}w~u{}w~}d{}w~}j{}w~}d{}w~}j{}w~}d{}w~}j{}w~}d{}w~}j{}w~}X{}w~O{|w~y}w~} L{}w~}G{}u~|!{|}x~}|w{}~v{}w~}b{|r~|"
"x{}~w{}s~|\\{|q~}Rq~|Zw~}kw~}`{|v~p{|v~]v~p{}w~}X{|q~[{}v~}     p{|v~}ly}$v}|\"{}x~}t{}x~}Yy}|s{|y~|w{|v~|_{|w~"
"q{}x~}s{|w~n{|v~}l{|u~}%{}w~|Iw~} u{}w~L{}w~} tv}|P{|w~R{|v~|pv~}U{}w~}V{}v~}={}v~|Q{}w~}K{}v~|^v~|o{}v~Y{}v~U{"
"}v~m{}v~P{|v~}U{|v}M{}w~}F{|}q~}6{|q~}|G{|w}|^w~ru~y|x{|}t~y|}v~|kv~|h{|v~d{}w~}m{|u~|b{|u~|i{|~}g{}w~}l{|}u~}a"
"{}w~}L{}w~}Q{}u~|iv~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}ot~]{}w~}V{}w~|bv~|h{}w~|n{}q~f{}u~k{}u~a{}w~}Q{}u~k{|u~c{}w~}"
"kv~}c{|}h{|v~}Y{|v~|X{}v~l{}v~|[v~}v~]v~}w~n{}r~|ev~}n{}v~W{|v~|Y{}v~}F{|w~}Ew~}M{|w~|  u{}w~|o{}u~|_t~|q{|v~}_"
"{|v~|P{|v~}pt~|a{|v~|Ew~}U{|v~|pt~|`w~}m{|w~}Wv~Lv~Tw~}s{}v~|Sv~_w~}mv~mv~hw~}m{|w~}a{}v~nv~}_u~}o{}v~a{}v~o{|u"
"~|Zw~}@{}w~|Y{}w~|Sv~|p{|u~|Zv~{|v~[v~}x~}s{|r~_{|v~|u{}v~Uq~V{}v~|Fw~}Lw~|M{|w~| I{|y}~y}|r{|}x~}|`{}w~}qs~]u~"
"n{|v~`{|w~r{|v~\\{|v~nv~}_{|w~}Mw~}m{|w~}Y{}r~X{}w~}nv~`{|v~|o{}v~|g{|v~|st~|t{|v~|g{}v~v{}w~v{|v~`{|w~}q{|w~}_"
"v~|v{}w~uv~}au~}o{}v~a{|v~nv~}Vv~U{|w~}p{}w~}bv~|h{|v~`u~M{}w~}P{|u~|q{}v~}_{}g~}|b{}w~}hv~|Z{|v~Y{}u~k{}u~a{|y"
"~A{}w~A{}~|Zl~|Z{}~|k{}~}[{|l~} yv~}Uv~}uy~}S{|v~S{}v~|x{|y}x~}|wu~X{|w~}Lw~|I{|v~}*{}x~|g{|x~}&{}y~}t{|x~ T{}x"
"~|g{|x~}   <{|v~|o{}v~|Ux~}w{|x~}  Ex~|t{|y~}Tw~|p{}j~}j{}x~|k{}x~}aw~|p{}j~}g{}v~}Wv~|h{|v~fv~|h{|v~fv~|h{|v~f"
"v~|h{|v~fv~|h{|v~g{|v~g{|v~|ov~|m{|v~V{|u~|i{|~}c{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~k{}t~d{}w~"
"|n{}q~f{}u~k{}u~e{}u~k{}u~e{}u~k{}u~e{}u~k{}u~e{}u~k{}u~c{}v~|n{|u~|e{}u~|l{}u~c{}v~l{}v~|c{}v~l{}v~|c{}v~l{}v~"
"|c{}v~l{}v~|Y{|v~|V{}w~}Mw~}kv~c{}w~|o{}u~|a{}w~|o{}u~|a{}w~|o{}u~|a{}w~|o{}u~|a{}w~|o{}u~|a{}w~|o{}u~|k{}w~|o{"
"}s~U{|v~|P{|v~|N{|v~|N{|v~|N{|v~|Dv~Lv~Lv~Lv~Uv~}p{}v~^w~}m{|w~}a{}v~nv~}`{}v~nv~}`{}v~nv~}`{}v~nv~}`{}v~nv~}W{"
"}u~W{}t~|qv~}_v~|p{|u~|`v~|p{|u~|`v~|p{|u~|`v~|p{|u~|Yq~Xu~}o{}v~Yq~ M{}w~}|w{}x~}v{}v~b{}w~}|m{}v~b{}w~}|m{}v~"
"b{}w~}|m{}v~b{}w~}|m{}v~W{}x~}Nq~| M{|v~F{|u~ py~|V{|}y~y}|vy~|w{|y}y~y}Y{|s~}Q{|s~|Yw~}kw~}_{}v~|s{}v~|^{|w~}p"
"{|v~X{|r~}Z{}u~}     q{}v~}o{|y~}$v~}\"w~|tw~|Y{}y~}|u{|y~|x{|u~^{}x~|q{|w~s{}x~}mu~}n{|s~}&{|w~|J{|w~| u{}w~L{"
"}v~ u{|v~|P{}x~}Q{}v~|r{}v~T{}w~}W{}v~}O{}|k{}v~}P{}w~}]{}|l{}u~]{|v~|q{}v~|Yv~}U{|v~}o{}v~}Q{|v~}T{}v~M{}v~C{|"
"}t~}6{|t~}|D{}w~}^{}x~|s{|m~y}q~|k{|v~fv~|e{}w~}n{|u~}`{}u~|l{|}y~}g{}w~}n{|}t~}`{}w~}L{}w~}P{}u~}jv~|h{}w~}hv~"
"|Y{}w~}M{}w~}W{}w~}nt~^{}w~}V{}w~|bv~|h{}w~|mq~e{}u~|n{}u~|a{}w~}P{}u~|n{}u~|c{}w~}k{|v~|d{|y~}k{|u~|Y{|v~|X{|u"
"~n{|u~Z{}r~}]{}s~}n{|r~e{}v~lv~}X{|v~|Z{|u~E{|w~}E{}w~M{|w~|  u{|v~p{|t~|_s~|s{|u~]u~|P{}v~}s{|s~|`u~|k{|Ww~}T{"
"}v~}s{|s~|`w~}m{|w~}Wv~Lv~Tw~}r{}v~}Tv~_w~}mv~mv~hw~}m{|w~}`v~}p{}v~|_t~|q{|v~|`v~}q{|t~|Zw~}Q{|kv~|Y{}w~}S{}v~"
"pt~|Z{}w~y}w~}[{}s~|rs~}_v~}s{}w~}V{}s~}W{}v~|Ew~}Lw~|M{|w~|  r{|v~|s{}s~}^u~}ov~|_w~|s{}w~|[v~}pu~]v~|Nw~}m{|w"
"~}Y{|s~}Xv~m{}w~|a{|u~p{|u~|fv~}t{}x~}x~}t{}v~ev~}w{}w~w{|v~}`{|w~}q{|w~}_{}v~|w{}w~v{}v~`t~|q{|v~|`v~}p{}v~U{}"
"w~|Uv~|r{|v~b{|v~fv~|bu~|M{}w~}O{|u~}t{|u~}\\{|k~}|`{}w~}hv~|Z{|v~X{}u~|n{}u~|`{|@{}w~@{|Xn~|X{|i{|Y{|n~} xv~}U"
"{|v~}vy~}S{|v~T{|v~|jv~}Y{|w~}Lw~|H{|v~|*{}x~}i{}x~}${}~}s{|y~ S{}x~}i{}x~}   ;{|u~p{|u~|Ux~}w{|x~}  Ey~|s{|~}T"
"{}x~}o{}j~}k{|w~k{}x~}a{}x~}o{}j~}h{}v~}W{|v~fv~|h{|v~fv~|h{|v~fv~|h{|v~fv~|h{|v~fv~|h{}w~}f{}w~}p{|v~l{|v~U{}u"
"~|l{|}y~}c{}w~}M{}w~}M{}w~}M{}w~}D{}w~}M{}w~}M{}w~}M{}w~}Z{|v~n{|}s~c{}w~|mq~e{}u~|n{}u~|d{}u~|n{}u~|d{}u~|n{}u"
"~|d{}u~|n{}u~|d{}u~|n{}u~|d{}v~|l{|u~|et~|n{}u~|c{|u~n{|u~b{|u~n{|u~b{|u~n{|u~b{|u~n{|u~X{|v~|V{}w~}Mw~}x{|p{}v"
"~c{|v~p{|t~|a{|v~p{|t~|a{|v~p{|t~|a{|v~p{|t~|a{|v~p{|t~|a{|v~p{|t~|k{|v~p{|q~j{|gu~|Pu~|k{|_u~|k{|_u~|k{|_u~|k{"
"|Vv~Lv~Lv~Lv~U{|v~}r{}v~}^w~}m{|w~}`v~}p{}v~|_v~}p{}v~|_v~}p{}v~|_v~}p{}v~|_v~}p{}v~|W{}u~Vu~|q{}v~|_{}v~pt~|`{"
"}v~pt~|`{}v~pt~|`{}v~pt~|Y{}s~}Xt~|q{|v~|Y{}s~} Lu~}p{}u~|au~}p{}u~|au~}p{}u~|au~}p{}u~|au~}p{}u~|W{}x~}N{}s~} "
"M{|v~|Ev~} py~|Jy~|M{}t~O{|u~}Xw~}kw~}_{|t~}w|}u~}]{}w~}ov~|Xr~|Y{}t~}y|     tt~|r{}x~}$v~}\"w~t{|w~X{}v~}y|y{|"
"y~y|}t~|_{|x~}ow~}tw~|m{|t~|r{|}q~}&w~}J{}w~ t{}w~L{}v~ u{|v~|Pw~|Pu~|t{}v~|\\s|}w~}r|a{}v~}Nx~}|p{}t~O{}w~}]{}"
"y~}|q{}t~|\\{}v~|s{}u~Y{|v~|T{}u~|r{}u~|_{~}|r{|}u~|T{}v~M{}v~@{|}w~}6{|w~}|A{}w~}^{|w~r{|o~}{}s~}iv~}f{}w~}e{}"
"w~}q|y}s~|_{}t~|p{|}w~}g{}w~}r|y}q~}_{}w~}g|`{}w~}O{}t~}o{|}u~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}mt~_{}w~}h|i{}w~|bv~"
"|h{}w~|m{}r~dt~}|r{|t~|`{}w~}Ot~}q{|t~}b{}w~}jv~}d{|w~}|p{|}u~}X{|v~|W{}u~|q{}u~|Z{|r~|]{|s~|mr~f{|v~|l{|v~|Y{|"
"v~|[{|u~}b|^{|w~}E{|w~|N{|w~|  tv~}r{}s~|_w~y}x~}|w{|}u~|]{|u~|p{|}|^t~y|x{|}w~}w~|`{|u~|n{|y~|Xw~}St~y|x{|}w~}"
"w~|`w~}m{|w~}Wv~Lv~Tw~}q{}v~}Uv~_w~}mv~mv~hw~}m{|w~}`{}v~}r{}v~}^s~}s{|v~}_{}v~}s{|s~|Zw~}Qy~}|o{}w~}X{|v~}|U{|"
"v~}s{|s~|Z{|q~Z{|s~qs~|`{}w~}qv~}Vs~|X{}v~|Dw~}Lw~|M{|w~|  qu~|u{}w~|v~}_s~|s{|u~^{}w~t{}w~}Z{|v~}|t{|}v~|]{}v~"
"|ny|^w~}m{|w~}Xs~|Y{}w~}m{|w~}a{|t~|s{}t~}f{}v~}v{|w~{w~|v{}v~}e{}v~}x{}w~x{}u~_{|w~}q{|w~}^u~}|y{}w~x{}u~}`s~}"
"s{|v~}_{|v~}|t{|}v~|U{|v~}|W{|v~|t{|v~|bu~f|v~}c{}v~}h|_{}w~}Vs}t~}v{}t~s}`{|y}t~y}|]{}w~}hv~|Z{|v~Wt~}|r{|t~|#"
"{}w~ vp~| {|p~} wv~}T{}v~}wy~}v{}~Z{|v~S{}x~|hx~}X{|w~}Lw~|G{}w~}){|w~|m{|w~|\"{|}q{} R{|w~|m{|w~| XY| ${|u~}r{"
"|t~}Ux~}w{|x~}  E{}qy|T{|w~c{}x~gw~|lw~}a{|w~c{}x~e{}v~}Vv~}f{}w~}hv~}f{}w~}hv~}f{}w~}hv~}f{}w~}hv~}f{}w~}hv~|f"
"{|v~pv~}l{|v~}h|h{}t~|p{|}w~}c{}w~}g|a{}w~}g|a{}w~}g|a{}w~}g|X{}w~}M{}w~}M{}w~}M{}w~}Z{|v~r|x}q~b{}w~|m{}r~dt~}"
"|r{|t~|bt~}|r{|t~|bt~}|r{|t~|bt~}|r{|t~|bt~}|r{|t~|d{|v~|j{|v~}f{}s~}|r{|t~|a{}u~|q{}u~|a{}u~|q{}u~|a{}u~|q{}u~"
"|a{}u~|q{}u~|X{|v~|V{}w~}Mw~}xy~}y|wy|u~|bv~}r{}s~|`v~}r{}s~|`v~}r{}s~|`v~}r{}s~|`v~}r{}s~|`v~}r{}s~|jv~}r{}w~}"
"|u~|o{|}y~g{|u~|p{|}|_{|u~|n{|y~|`{|u~|n{|y~|`{|u~|n{|y~|`{|u~|n{|y~|Wv~Lv~Lv~Lv~T{}u~}|x{|}u~}]w~}m{|w~}`{}v~}"
"r{}v~}^{}v~}r{}v~}^{}v~}r{}v~}^{}v~}r{}v~}^{}v~}r{}v~}V{}u~V{|v~}r{}v~}^{|v~}s{|s~|`{|v~}s{|s~|`{|v~}s{|s~|`{|v"
"~}s{|s~|Xs~|Xs~}s{|v~}Ws~| K{}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~^{}u~}x|{x|}t~U{}x~}N{|s~| M"
"{|w~|D{}w~| q{|y~}K{|y~}L{}v~|N{}v~Ww~}kw~}^{|j~}\\v~|o{}w~}X{}s~W{|^~}    -s~}v|}v~}$v~}#{|w~t{|x~}X{}e~|^w~|o"
"{|w~|v{}w~k{|s~}v|}t~y}v~}'{}w~Jw~} t{}w~L{}v~ u{|v~|Q{|w~O{|u~}w|}u~}\\{|e~|ab~`u~w}|x}r~|O{}w~}]{}v~w}|x}s~}Z"
"t~}w|}t~X{}w~}S{|t~y}v|}t~}^v~y}y|y}s~|S{}v~M{}v~={|}~}6{|y~}|?{}w~}]w~}q{}r~|y{}u~}h{|v~|f{|v~e{}c~|]{}s~y}v|y"
"}t~}g{}b~|^{}c~}`{}w~}N{}r~y}v|y}r~|h{}w~}hv~|Y{}w~}M{}w~}W{}w~}lt~`{}d~}i{}w~|bv~|h{}w~|lr~cr~}v|}s~}_{}w~}Ns~"
"y}v|}s~}a{}w~}j{|v~|e{|s~}u|}r~W{|v~|Vs~}v|y}t~|Xs~}\\{|s~|m{}t~}fv~}j{}v~Y{|v~|[{}\\~}^{|w~}Dw~}N{|w~|  t{}u~y"
"|x{|}w~y}w~|_w~}{k~|[{|t~}|wy|}x~|^{|k~y|w~|_{|t~}|vy|y}w~|Xw~}S{|k~y|w~|`w~}m{|w~}Wv~Lv~Tw~}p{}v~}Vv~_w~}mv~mv"
"~hw~}m{|w~}_{}u~}|x{|}u~}]w~y}w~y|yy|}u~|^{}u~}|x{|}w~}w~|Zw~}Qv~}y|v{|}u~|Wm~[{}u~}w|}v~}w~|Y{}s~}Yt~}q{}t~|a{"
"}v~p{|v~|W{}t~W{}d~Uw~}Lw~|M{|w~|  q{|u~}|y{|}v~{|s~br~}y|yy|}u~|^{|w~}v{}v~X{}u~}y|{y|}u~}\\{|t~}|vy|y}y~}^w~}"
"m{|w~}X{}t~Xv~|lv~|b{|s~}v|}q~x}hu~}|{y|w~}{}w~}|{|}u~c{}u~}|}w~|}t~|_{|w~}q{|v~}_{|s~}v~}s~}_w~y}w~y|yy|}u~|^{"
"}u~}y|{y|}u~}S{}r~}Z{}v~}|x{|}v~}b{|Z~c{}c~}_{}w~}Vk~v{}l~|^{|v~Y{}w~}hv~|Z{|v~Vr~}v|}s~|\"{}w~ ur~| y{|r~} vv~"
"}St~}y|y~}{y|}x~`{}b~}a{}~|f{~}W{|w~}Lw~|G{|w~}({|v~}|s{|}v~|  E{|v~}|s{|}v~| X{|Z~} ${|s~}y|{y|}q~}|}Xx~}w{|x~"
"}   l{}x~|c{}x~h{}x~}m{|w~|`{}x~|c{}x~f{|v~}V{|v~|f{|v~i{|v~|f{|v~i{|v~|f{|v~i{|v~|f{|v~i{|v~|f{|v~i{|v~dv~|r{|"
"v~k{|b~g{}s~y}v|y}t~}c{}c~}a{}c~}a{}c~}a{}c~}X{}w~}M{}w~}M{}w~}M{}w~}Z{|b~}a{}w~|lr~cr~}v|}s~}`r~}v|}s~}`r~}v|}"
"s~}`r~}v|}s~}`r~}v|}s~}b{|x~|h{|x~}f{}o~}v|}s~}_s~}v|y}t~|_s~}v|y}t~|_s~}v|y}t~|_s~}v|y}t~|W{|v~|V{}w~}Mw~}xk~}"
"a{}u~y|x{|}w~y}w~|`{}u~y|x{|}w~y}w~|`{}u~y|x{|}w~y}w~|`{}u~y|x{|}w~y}w~|`{}u~y|x{|}w~y}w~|`{}u~y|x{|}w~y}w~|j{}"
"u~y|x{|}u~y{|t~}|vy|}v~f{|t~}|wy|}x~|^{|t~}|vy|y}w~|_{|t~}|vy|y}w~|_{|t~}|vy|y}w~|_{|t~}|vy|y}w~|Wv~Lv~Lv~Lv~S{"
"}j~}\\w~}m{|w~}_{}u~}|x{|}u~}\\{}u~}|x{|}u~}\\{}u~}|x{|}u~}\\{}u~}|x{|}u~}\\{}u~}|x{|}u~}U{}u~V{}t~}|x{|}u~}\\{"
"}u~}w|}v~}w~|_{}u~}w|}v~}w~|_{}u~}w|}v~}w~|_{}u~}w|}v~}w~|X{}t~Ww~y}w~y|yy|}u~|W{}t~ I{}h~}\\{}h~}\\{}h~}\\{}h~"
"}\\{}h~}T{}x~}Ms~ K{|y~}C{|w~ p{}x~K{}x~Kw~|L{}x~|Ww~}kw~}]{|l~}\\{|v~n{|w~}X{|s~U{}`~}    -{|h~|$v~}#{}x~}t{}x"
"~}X{|}g~|^{}x~}m{}w~}y|}v~|j{|g~}y{}v~}({|w~|L{|w~| t{}w~L{}v~ u{|v~|Q{}x~}N{}k~}[{|e~|ab~`e~|N{}w~}]{}g~}Y{|i~"
"|Xv~|R{|g~}]i~|R{}v~M{}v~;y|5{|<{}w~}]{|w~|p{|v}|w{|x}|e{}v~dv~}f{}e~}|[{}d~|g{}d~}\\{}c~}`{}w~}M{}c~}|g{}w~}hv"
"~|Y{}w~}M{}w~}W{}w~}kt~a{}d~}i{}w~|bv~|h{}w~|l{|s~b{}f~|^{}w~}M{}f~|`{}w~}iv~}e{|c~V{|v~|Uf~}W{}t~|[s~l{}t~|g{}"
"v~hv~}Z{|v~|[{}\\~}^{|w~}D{}w~N{|w~|  sj~{}w~|_w~}{|m~|Y{}i~|]{|m~|{|w~|^{|f~|Xw~}R{|m~|{}w~|`w~}m{|w~}Wv~Lv~Tw"
"~}o{}v~}Wv~_w~}mv~mv~hw~}m{|w~}^h~\\w~}{k~|\\k~y|w~|Zw~}Qg~}V{|n~Zk~{}w~|Y{|s~|Y{}u~}q{|t~a{|v~|o{}v~W{|u~|W{}d"
"~Uw~}Lw~|M{|w~|  p{|l~|ys~be~}\\{}v~x}u~V{}j~}Z{|h~}^w~}m{|w~}X{|u~|Y{|w~}k{}w~}b{|w~}m~|s~h{|m~xm~|b{}g~|^{|w~"
"}pr~a{|f~}^w~}{k~|\\{}j~}R{|r~}Y{}l~}a{}Z~}d{}c~}_{}w~}Vk~v{}l~|^{|v~Y{}w~}hv~|Z{|v~U{}f~|!{}w~ tt~| w{|t~} uv~"
"}R{}i~`{}b~}`{|?{|w~}Lw~|Fw~}&{}t~w}t~}  A{}t~w}t~} V{|Z~} ${|w~}m~|s~Xx~}w{|x~}   m{|x~}b{}x~hw~lk~k{|x~}b{}x~"
"fv~}U{}v~dv~}j{}v~dv~}j{}v~dv~}j{}v~dv~}j{}v~dv~}j{}w~}d{}w~}r{}w~}k{|b~f{}d~|c{}c~}a{}c~}a{}c~}a{}c~}X{}w~}M{}"
"w~}M{}w~}M{}w~}Z{|d~}|`{}w~|l{|s~b{}f~|^{}f~|^{}f~|^{}f~|^{}f~|`{|~|f{|~}f{|w~|}f~|]f~}]f~}]f~}]f~}V{|v~|V{}w~}"
"Mw~}xl~}_j~{}w~|_j~{}w~|_j~{}w~|_j~{}w~|_j~{}w~|_j~{}w~|ii~w{|f~e{}i~|]{|f~|^{|f~|^{|f~|^{|f~|Wv~Lv~Lv~Lv~R{}l~"
"}[w~}m{|w~}^h~Zh~Zh~Zh~Zh~){|f~Zk~{}w~|^k~{}w~|^k~{}w~|^k~{}w~|X{|u~|Ww~}{k~|V{|u~| H{|j~|Z{|j~|Z{|j~|Z{|j~|Z{|"
"j~|S{}x~}M{}u~} I{}Ax~} pw~|Lw~|L{|y~|Jy~|Vw~}kw~}[{}o~|[{}w~}mv~Wt~}T{|}b~}    +{}l~}\"v~}#w~|tw~|U{|}l~}]{|w~"
"ko~|h{|j~}|w{}u~({}w~L{}w~ s{}w~Lv~| u{|v~|Qw~}M{|m~}Z{|e~|ab~`g~}|M{}w~}]{}h~|W{|k~W{}v~P{|i~|\\k~}P{}v~Mv~|  "
"i{}w~}\\{}w~Jv~}d{}v~f{}g~}|X{|}h~}e{}g~}|Z{}c~}`{}w~}L{|}g~}|e{}w~}hv~|Y{}w~}M{}w~}W{}w~}jt~b{}d~}i{}w~|bv~|h{"
"}w~|ks~a{|i~}\\{}w~}L{|i~}^{}w~}i{|v~|e{}f~}U{|v~|T{}i~|Ut~Z{}u~}l{|t~g{|v~|h{|v~|[{|v~|[{}\\~}^{|w~}D{|w~N{|w~"
"|  s{|l~|{}w~|_w~}x{}q~}|W{|j~|[{}p~|y{|w~|]{|g~|Xw~}P{}q~}|y{}w~|`w~}m{|w~}Wv~Lv~Tw~}n{|v~}Xv~_w~}mv~mv~hw~}m{"
"|w~}]{}l~}[w~}{|m~|Zm~|{|w~|Zw~}Qh~|T{|o~Z{|m~|{}w~|Xs~X{}u~|pu~}av~}m{}w~}Wu~V{}d~Uw~}Lw~|M{|w~|  o{|n~|w{}u~b"
"f~}Z{}p~}T{}l~}X{|i~}^w~}m{|w~}Wu~Xv~|k{|v~b{|w~y|o~|{}t~g{|o~|x{|o~}`{}i~|]{|w~}p{}s~_{}j~}|]w~}{|m~|Z{}l~}P{|"
"s~}X{}n~}`X~d{}c~}_{}w~}Vk~v{}l~|^{|v~Y{}w~}hv~|Z{|v~T{|i~} {{}w~ sv~| u{|v~} tv~}Q{}j~`{}b~}#{|w~}Lw~|G{|w~}${"
"}m~}  ={}m~} T{|Z~} ${|w~y|o~|{}t~Xx~}w{|x~}   mw~|b{}x~i{}x~|lk~kw~|b{}x~g{|v~Tv~}d{}v~jv~}d{}v~jv~}d{}v~jv~}d"
"{}v~jv~}d{}v~k{|v~|d{|v~rv~|k{|b~e{|}h~}a{}c~}a{}c~}a{}c~}a{}c~}X{}w~}M{}w~}M{}w~}M{}w~}Z{|g~}|]{}w~|ks~a{|i~}["
"{|i~}[{|i~}[{|i~}[{|i~}/{|w~|y{|i~}Z{}i~|[{}i~|[{}i~|[{}i~|U{|v~|V{}w~}Mw~}xm~|^{|l~|{}w~|_{|l~|{}w~|_{|l~|{}w~"
"|_{|l~|{}w~|_{|l~|{}w~|_{|l~|{}w~|i{|l~}u{|g~d{|j~|\\{|g~|]{|g~|]{|g~|]{|g~|Wv~Lv~Lv~Lv~Q{|}p~}|Zw~}m{|w~}]{}l~"
"}X{}l~}X{}l~}X{}l~}X{}l~}){|w~}l~}Y{|m~|{}w~|^{|m~|{}w~|^{|m~|{}w~|^{|m~|{}w~|Wu~Vw~}{|m~|Tu~ E{|}p~}|V{|}p~}|V"
"{|}p~}|V{|}p~}|V{|}p~}|Qw~}Lu~|  i{}y~| q{|w~}M{|w~}K{|}I{|}Uw~}kw~}Y{|y}w~y}|Yv~|m{}w~|X{}u~|Q{|}e~}    *{|}p~"
"}|!v~}#w~t{|w~Py|x}y~x}y|[w~|j{}r~|e{|n~}|t{}u~){|w~|N{|w~| s{}w~Lv~ t{|v~|R{|w~|L{|}p~|Y{|e~|ab~`y|}l~}|K{}w~}"
"]{|}k~|S{}o~|Vv~}N{|m~}Z{}n~}|O{}v~Mv~  h{}w~}[v~L{|v~|d{|v~|g{}k~y}y|T{|}m~}|c{}m~x}y|W{}c~}`{}w~}J{|}k~}|c{}w"
"~}hv~|Y{}w~}M{}w~}W{}w~}it~c{}d~}i{}w~|bv~|h{}w~|k{|t~_{|m~}|[{}w~}J{|l~|]{}w~}h{}w~}c{|}k~}|T{|v~R{|}m~|S{}v~}"
"Z{|u~|kt~gv~}f{}v~[{|v~|[{}\\~}^{|w~}Cw~|O{|w~|  q{}p~}x{}w~|_v}vy}w~y}|S{}m~}Xy}w~y}|w{|w}|[{|l~}|Vw~}N{|}w~y}"
"|w{}w~|`v}lw}|Wv~Lv~Tv}m{|u}Yv}_w~}mv~mv~hw~}m{|w~}\\{|n~|Zw~}x{}q~}W{}q~}|y{|w~|Zw~}Q{|}l~}P{|y}s~X{}q~}x{}w~|"
"X{}u~}X{|u~o{}v~|b{}w~}kv~}X{}w~}V{}d~Uv~Lw~|M{|w~|  n{|}q~}u{|}w~bv~{}o~}|X{|r~|R{|}p~}|U{}l~}|^w~}m{|w~}W{}w~"
"}Xw}|i{|w}b{|w~|{|q~|y{|t~f{|q~|v{|q~|^{|l~}[{|w~}os~]{|}o~}|[w~}x{}q~}W{|}p~}|M{|}v~}W{|p~|`{|X~|e{}c~}_{}w~}V"
"k~v{}l~|^{|v~Y{}w~}hv~|Z{|v~R{|m~}| y{}w~ rx~| s{|x~} sv~}P{|}n~}|`{}b~}#{|w~}Lw~|Ty|pv~|\"y|}u~}y|  9y|}u~}y| "
"R{|Z~} ${|w~|{|q~|y{|t~Xx~}w{|x~} y}|  q{}x~}aw}j{|w~kk~l{}x~}aw}gv~}U{|v~|d{|v~|l{|v~|d{|v~|l{|v~|d{|v~|l{|v~|"
"d{|v~|l{|v~|d{|v~|l{|v}bv}|t{}w~}j{|b~c{|}m~}|_{}c~}a{}c~}a{}c~}a{}c~}X{}w~}M{}w~}M{}w~}M{}w~}Z{|m~x}y|Z{}w~|k{"
"|t~_{|m~}|X{|m~}|X{|m~}|X{|m~}|X{|m~}|.w~}v{|}n~}|X{|}m~|X{|}m~|X{|}m~|X{|}m~|S{|v~|V{}w~}Mv|wy|}u~y}|Z{}p~}x{}"
"w~|]{}p~}x{}w~|]{}p~}x{}w~|]{}p~}x{}w~|]{}p~}x{}w~|]{}p~}x{}w~|g{}o~|r{|l~}|a{}m~}Y{|l~}|Y{|l~}|Y{|l~}|Y{|l~}|U"
"v~Lv~Lv~Lv~O{|y}v~y}|Xw~}m{|w~}\\{|n~|V{|n~|V{|n~|V{|n~|V{|n~|(w~|{|n~|V{}q~}x{}w~|\\{}q~}x{}w~|\\{}q~}x{}w~|\\"
"{}q~}x{}w~|W{}w~}Vw~}x{}q~}R{}w~} B{|t}|P{|t}|P{|t}|P{|t}|P{|t}|Nw~}  3{|~}     ;f|    '{|y}w~}y|  8{|y~|X{|x~}"
"h{|}w~}|ay|y}w~y}| rw~}N{}w~ ?{|w~| D{}w~I{|y}w~y}|%b|\\{|x}u~y}|!y|y}u~y}y|O{|y}w~y}| {{y|}u~y}|Vy|y}v~}y| u{|"
"w~|  B{|v~| 1{|y}u~y}|  o{|x}u~y}y| Fv~|  7y|y}v~y}| {{y|y}q~|#y|y}u~y}y| {{|y}v~y}y|   a{|w~}C{}x~}O{|w~|  oy}"
"v~}|vv|!{|}t~y}|!{|y}t~y}|Sv|Av~\"v|Lv~ Rv|mv|mv|hv|lv|Z{|y}u~}|Xw~}v{|}w~y}|T{|}w~y}|w{|w~|Zv|Ny|y}u~y}| {{|y}"
"w~}|uw|W{|u}|Wv}|o{|v}av|ju|Xv~| sv~Lw~|M{}w~|  ly|}v~}|Uv~yy|}v~y}|S{|y}~y}|N{|y}v~y}|Qy|y}v~x}|[v|m{|w~}W{|w~"
"|#{|w~|x{|}w~}|v{|}y~y}c{|y}x~y}ry}x~y}|Z{|y}s~}y|G{}w~}|Zy|v~}|Ww~}v{|}w~y}|T{|y}v~y}| x{|y}w~}|    Ry|y}v~y}|"
"   Zy| rv~}M{|y}u~}|]`| Iw~|T{|y~}|u{|u~       5{|w~|x{|}w~}|v{|}x~}Wx~}w{|x~} {}y~}  r{|y}|Kw~|L{|y}|Hv~|    E"
"{|y}u~y}|      qy|y}v~y}|Sy|y}v~y}|Sy|y}v~y}|Sy|y}v~y}|Sy|y}v~y}|+{|y~}r{|y}v~y}|R{|y}v~y}y|S{|y}v~y}y|S{|y}v~y"
"}y|S{|y}v~y}y|  oy}v~}|vv|Zy}v~}|vv|Zy}v~}|vv|Zy}v~}|vv|Zy}v~}|vv|Zy}v~}|vv|d{|}v~y}|n{|y}u~y}y|\\{|}t~y}|U{|y}"
"t~y}|T{|y}t~y}|T{|y}t~y}|T{|y}t~y}|Rv|Lv|Lv|Lv|!v|lv|Z{|y}u~}|R{|y}u~}|R{|y}u~}|R{|y}u~}|R{|y}u~}|'{}x~|w{|y}u~"
"}|S{|y}w~}|uw|Z{|y}w~}|uw|Z{|y}w~}|uw|Z{|y}w~}|uw|Vv~|Vw~}v{|}w~y}|Qv~|    Mw~|                K{|y~|  e{|w~Nw~"
"| ?{}w~ Cw~}      .{}w~  @{|v~|d{}|     Kv~|   !u~|     J{|w~}C{|w~O{|w~|     9w~} Iv~   bw~}9{|w~|    X{|v~ rv"
"~Lw~|M{}w~|  <v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}          )v~}Iy~}  gw~|T{|u~y}s~|       5{|w~|Ax~}w{|x~} {"
"{x~|   0{|v~    ?{}y~}         R{|}        5x~|         O{|y~}  &{|v~Uw~}D{|v~    Lw~|                K{|y~|  d"
"{}x~}P{}w~ >w~| D{|w~|      .w~|  ?{|v~}g{|x~|     M{|v~    {|u~|     K{|w~}Bw~|P{|w~|     :{}w~} Iw~}   bw~}9{"
"|w~|    X{}w~| r{}w~|Mw~|Mv~  ;v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}          )v~}Iy~}  gw~|T{|l~|       4{|w~"
"|Ax~}w{|x~} {{}y~}   /v~|    ?x~|                  f{|x~         M{}  %{}w~|Uw~}D{}w~|    Lw~|                K"
"{|y~|  d{|w~Pw~| ?{|w~ C{}w~      .{|w~  ={|u~}|l{|u~|     N{}v~    {{|u~|     L{|q~}H{}x~}V{}q~|     :v~| Iw~}"
"   bw~}9{|w~|    Xv~ q{}w~}Mw~|N{|v~  ;v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}          )v~}Iy~}  gw~|T{|}o~}|  "
"     3{|w~|Ax~}w{|x~} {{|x~|   0v~}m{}    N{|x~                  e{}y~}            Rv~Tw~}Dv~    S{}x~x{|w~|   "
"             K{|y~|  c{}x~}R{}x~} >{|x~| Cw~}      .{|x~|  ;{}t~}|sy|}t~|     N{|v~}    y{|u~|     M{|q~}H{|w~V"
"{}q~|     ;{}v~ I{|w~}   bw~}9{|w~|    Y{}w~} q{|v~}|Ow~|P{|}v~}  ;v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}      "
"    )v~}Iy~}  gw~|Q{|y}v~y}|       1{|w~|Ax~}w{|x~} yx~|   0{}v~|p{|~}    N{|x~|                  f{|x~        "
"    S{}w~}Tw~}E{}w~}    S{}x~|y{|w~                J{|y~|  bw~|Sw~| >{}y~}        K{}y~}  9{|p~x}q~}|     N{|u~"
"|    x{|u~     M{|q~} y{}q~|     K{|}|p{|u~| I{}w~|   bw~}9{|w~|    Z{|v~ o{}q~}Tw~|U{|p~  :v~  S{|w~}W{|w~|#{|"
"w~| j{}w~ s{}w~Uw~}          )v~}Iy~}  gw~|        W{|w~|Aw|vx| y{|x~}   0{|u~|s{}x~}    N{|x~|                "
"  f{|x~|            U{|v~Sw~}F{|v~    R{|x~}y{}w~                J{|y~|  b{|x}|T{|x}|             w{}g~}|     Q"
"x|y}u~}    v{|u~     N{|p} yp}|     K{|x~}y|wy|}u~} J{|}v~   aw~}9{|w~|    \\{|}v~} nq~}Tw~|U{|q~|  :v~  S{|w~}"
"W{|w~|#{|w~| j{}w~ s{}w~Uw~}          )v~}Iy~}  gw~|        W{|w~| :{|}w|}w~|   /t~y}x|y}v~}    U{|}|x{|w~|    "
"              f{}x~|            W{|}v~}Sw~}H{|}v~}    Qq~|                J{|y}               *{|}l~}|     O{}q"
"~    tt|            `{|i~} Lr~|   aw~}9{|w~|    `{}q~ l{}s~}Tw~|U{|s~}|  9v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~"
"}          )v~}Iy~}  gw~|        W{|w~| :{|q~   .{|i~}    U{|q~                  ly}w|}w~|            [{}q~Rw~}"
"L{}q~    P{}r~                                M{|y}u~y}y|     L{}r~|                R{|j~} Ks~}   `w~}9{|w~|   "
" `{}r~| jy|v}|Tw~|U{|u}|  6v~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}          )v~}Iy}|  gw~|        W{|w~| :{|r~| "
"  -{|k~}|    U{|r~}                  l{}r~}            Z{}r~|Rw~}L{}r~|    O{}t~                               "
"       k{}t~}           -{|`}|    `{|}m~}| Jt~}   _w~}9{|w~|    `{}s~| :w~|   cv~  S{|w~}W{|w~|#{|w~| j{}w~ s{}"
"w~Uw~}          )v~}           d{|w~| 9y}w~y}   ){}o~}|    S{|}u~}|                  k{}r~            Y{}s~|Qw~"
"}L{}s~|    M{}w~}                                      j{}w~}|           +{}`~}    ]{|x}v~y}| Gw~y}   ]w~}9{|w~"
"|    `{}v~}| 8w~|   cv~  S{|w~}W{|w~|#{|w~| j{}w~ s{}w~Uw~}                      g{|w~|     8{|}v~y}|    Ly|   "
"               g{|y}w~}|            X{}v~}|Ow~}L{}v~}|    Iy|                                                  "
"l{}`~}                Ww~|                                                                                     "
"                                            L{}`~}                Ww}|                                         "
"                                  r{" };

// Define a 104x128 binary font (huge sans).
static const char *const data_font_huge[] = {
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                        FY  AY "
"'Z      ;W      @Y  @Y 'Z    Y  @Y (Z        :Y  ?Y (Z          0Y  ?Y (Z    >X                                "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                         )X  AX '\\ )XAV 7YDY -]      BY  BY '[ +YEY 2X  AY (\\ -YDY   'XAU 3Y  AY (\\ )XAV 8YD"
"Y      LY  AY (\\ ,YEY #Y                                                                                      "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                  (X  CX '^ +[CU 6ZEY .`      C"
"X  CY '] -ZEZ 2X  CY (^ .ZEZ   )[CU 2Y  CY (] *[CU 7ZEZ      LY  CY (] -ZEZ %Y                                 "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                        'Y  EY '^ ,^FV 6ZEY /b      CX  DX '_ .ZEZ 2Y  DX '_ /ZEZ   +_FV 1X  CX (_ ,^FV 7ZEZ   "
"   KX  CX (_ .ZEZ &Y                                                                                           "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                             %Y  GY '` .aHV 6ZEY 1e      DY  FX"
" 'a /ZEZ 1Y  FX '` /ZEZ   +aHV 0X  EX '` .aHV 7ZEZ      JX  EX (a /ZEZ &X                                      "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                   #X  GX 'XNX 0dKW 6ZEY 1f      DY  HX &WMX 0ZEZ 0X  GX 'XMW 0ZEZ   ,dLX /X  GX 'WMX 0dLX 7ZEZ"
"      IX  GX 'WMX 0ZEZ 'X                 :T                                                                   "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                    ;X  IX 'XLX 1o 5ZEY 2ZLY   "
"   CX  IX &WKW 0ZEZ /X  HX (XLX 1ZEZ   ,o .Y  HX (WKX 1o 6ZEZ      IY  IY (WKW 0ZEZ (X                 <Z      "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                  =X  KX 'XJX 3WKd 5ZEY 3XGX      CX  JX 'WIW 1ZEZ .X  JX (XJX 2ZEZ   -WKd -X  "
"IX (WIW 2WKd 6ZEZ      HX  IX (WIW 1ZEZ )X                 =^                                                  "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                     >X  MX &WH"
"W 3VHa 4ZEY 3WDW      CX  LX 'WGW 2ZEZ -X  LX 'WHW 2ZEZ   -VHa +X  KX (XHW 3VHa 5ZEZ      GX  KX (WGW 2ZEZ )X  "
"               ?b                                                                                              "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                         ?W  MW &WFW 4VF^ 3ZEY 4WBV      BW  MX 'WEW 3ZEZ ,W  M"
"X 'WFW 3ZEZ   -VF^ )X  MX 'WFW 4VF^ 4ZEZ      FX  MX 'WFW 3ZEZ *X                 ?d                           "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"             ?W  X 'WDW 5UC[ 2ZEY 4VAV      AW  X &WDW 4ZEZ +W  NW 'WDW 4ZEZ   -UC[ 'W  MW 'WDW 5UC[ 3ZEZ      "
"EW  MW 'WDW 4ZEZ +X                 ?f                                                                         "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                              @X \"X 'WBW 6UAW 0ZEY 4V@V      B"
"X !W &WBV 4ZEZ +X !W 'WBW 5ZEZ   .VAW $W  W 'WBW 6UAW 1ZEZ      DW  W 'WBV 4ZEZ +W                 >f          "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                              ?X #W 'W@W      U?V      AX #W &W@V    NX #W &V@W        9W \"W 'W@V          .W "
"\"W 'W@V   !W                 >XHX                                                                             "
"         3Y                                                                                                    "
"                                                                                                               "
"                                                                                                               "
"                                                                           6W $W &V>V      U?V      @W $W &W>V "
"   NW $X 'V>V        8W $X (W>V          /X $W 'W>V   #W                 >XFX                                  "
"                                                    5Z                                                         "
"                                                                                                               "
"                ,Z                                                                                             "
"                                                                                             GZ                "
"                    #U?V                                                           NY  7Z ,X      CVCW      MY "
" 7Z ,X   $Z  7Z ,X        >Z  6Y ,X          4Z  7Y +W    7Y                                 @Z                "
"                                                                                                               "
"                                                         +Z                                                    "
"                                                                                                               "
"                       HY                                    \"U?V                                             "
"              MY  8Y ,Y      CVBV      LY  9Z ,Y   #Z  9Z ,Z        >Z  8Y ,Y          3Y  8Z ,Y    9Y         "
"                        ?Z                                                                                     "
"                                                                                                   *Y          "
"                                                                                                               "
"                                                                 IY                                    !U?V    "
"                                                       LY  :Y ,[ $R>U   ,V@V      MZ  :Y +Z   #Y  9Y +Z      ?R"
">U 8Y  9Y +Z %S?U        HY  :Z ,[    ;Y                                 ?[                                    "
"                                                                                                               "
"                                     )Y                                                                        "
"                                    8U                                                                         "
"    9Y                                     V@U                                                           JY  <Y"
" +[ 'XAU   ,V@V      LY  ;Y +\\   #Y  ;Y +\\      CXAU 7Y  ;Z ,\\ )XAV        HY  ;Y +[    <Z                  "
"               ?U                                                    ;T        $W /W                           "
"                                                                                   8e   !f      LY    Y     LX "
"   L]   :Y  <Y  NX 0X  >Y                                 @Y /X 0Y           K`            .X                  "
"  ^                                                  =ZEY                          @Y                          "
"           NVAV                                          <P              -X +Y  =Y +] )[CU 7YDY 4V@V      KY  ="
"Y +] ,YDY 5Y  =Y *] .YDY 5[  M[CU 6Y  <Y ,] *[CV 7YDY      Y  =Y +] ,YEZ !Y =Y  FYDY                 8X        "
"   EU                                                    :T        %W .X                                       "
"                                                                       9e   !f      KY   !Y     LY   \"a   :Y  "
"<Y  NX 0X  >Y                                 E^ /X 0_          %f            1]                   'c          "
"                                        @ZEZ                          AY                                     MV"
"CW                                          <R              4a .Y  >X *^ +]DU 7ZEZ 5U>U      JY  ?Y *^ -YEZ 4Y "
" ?Y *^ .ZEZ 5[  ]DU 5Y  >Y +^ ,]DU 6ZEZ      Y  ?Y +_ .ZEZ \"Y <Y  FYEZ                 :[           FU        "
"                                 7Y          -T 7W#W <Y    9X -W  DU             KY    HZ \"\\      4Z    M[ \""
"Y             LZ        +\\        8]                 >Z    G[    G\\                 @e   !f      JX   !Y     "
"LY   %d   :Y  <Y  NX 0X  >Y                                 Ha /X 0b          *j    L]        D_               "
"    +g                 A[                      LY        8Z -ZEZ   \"Y          1o )V    FX  NZ  FY            "
"%Y    ,X  NX*Z NW              3WEW    H\\                       #[ !Z \"[ \"[ \"[    G[7T              8g 0Y  "
"@Y +_ ,_FV 7ZEZ 5U>U      IY  @Y +` .YEZ 3X  ?X *` /ZEZ 4[:P 8_FV 4X  ?Y +` ._EU 6ZEZ      NX  @Y *_ .ZEZ #Y ;Y"
"  FYEZ                 ;]           GU                                         <b          1T :]'X @b    >W ,X "
" FV             a   \"d -g      >d   (d +b            %b        4f        Bg                 Ie   \"e   \"h    "
"             Ge   !f      IX   \"Y     LY   &e   :Y  <Y  NX 0X  >Y                                 Jc /X 0c    "
"      -n   $g        I`                   .j        >a        ;e    HU        .U        +b        Ac 2ZEZ   'b "
"         5o -]    Na (c  KY          .Y #_   8Y!W'Y\"X.c$X              3XGX    Mf                       -e +d "
",e ,e ,e   \"e=V              ;k 1Y  BY +XNW .aGV 7ZEZ 5V@V      HX  AY +XNW .YEZ 3Y  AY *WNW /ZEZ 4\\>T 9`GV 3"
"X  AY +XNW .`GV 6ZEZ      NY  AX *XNW /ZEZ $Y :Y  FYEZ                 <_           IU   (Q  LZ 4Z2Z 1Q        "
"                      &g   %Z +XCX    MT <a)W Ah $X  HX +X  GV           GX 3e )_ /j 4n  L] ?y /i C~S =i 0g    "
"        +g    L\\ 8t (m Ks 2~R E} <o HZ(Z :Z \"Z 4Z,] LZ 2_'_(^-Z Ck :q 0k ?q *n J~d'Z(Z*Z LZ=Z.\\.Z7Z(Z([$Z'~^"
" @e 3X  Ff )\\    MY   #Y     LY   (g   :Y  <Y  NX 0X  >Y                                 Kd /X 0e          0p "
"  (m        Lb                   1m ,\\ 5~S E~R Ah 'Z :~]+[;Z;Z Ik    LW    DX    DW        /i   ?Y(Y   4h 5ZEZ"
" ,\\ ,h        7\\ -o .`   $f -h  NY    No     %_ %c   @_\"X-_\"W0h&W   .\\ $\\ \"\\ #\\ #\\ )g 5~a Lm D~S I~S "
"H~R H~R 6Z !Z !Z \"Z :r 8^,Y Bk 2k 2k 2k 2k   (kAX+Z(Z#Z(Z$Z(Z$Y'Y&[%[ MZ  Im 1X  CY *WMX /bHV 7ZEZ 5V@V      G"
"X  CY *WLW /YEZ 2Y  CY *WLW 0ZEZ 3[AW :bHV 3Y  BX *WLW 0bHV 6ZEZ      MY  CX *XMX 0ZEZ $X 9Y  FYEZ             "
"    =a M~i        7U   (Q  N_ 9_8_ 3R                              )k   'Z +XCX +X@X 4T >e,X Cl &X  IX *X  GV  "
"         GX 5i 0d 2p ;u !^ ?y 2o F~S @n 4j            /l    N\\ 8x .r Nx 7~R E} >t KZ(Z :Z \"Z 4Z-] KZ 2_'_(^-Z"
" Ep =t 5o Au 1u N~d'Z(Z)Z MZ<Z/\\/Z5Z*['[&Z&~^ @e 3X  Ff )]    MY   $Y     LY   )h   :Y  <Y  NX 0X  >Y         "
"                        Le /X 0e          1r   +r        c                   3o -\\ 5~S E~R Dn *Z :~]+[;Z;Z Ko "
"   Y    EX    EY        2m   @Y)Y   6l 7ZEZ 0e 2k        >e 1o 0c   'j /i  X   !r     (b 'g   Eb\"W0c#X0i(W   -"
"\\ $] #\\ $] #\\ (f 6~b r F~S I~S H~R H~R 6Z !Z !Z \"Z :w =^,Y Ep 6p 7p 7o 7p   ,oDY+Z(Z#Z(Z$Z(Z$Y'Y%Z%Z LZ  Kp"
" 1X  DX *WKW /WMYJV 6ZEZ 5V@V      GY  EY *WKX 0YEZ 1Y  EY *XKW 1ZEZ 2[EZ :WMZKV 1Y  DX *WKX 1WLYKW 6ZEZ      L"
"Y  EY *WKW 0ZEZ %X 8Y  FYEZ                 >c M~h        7T   (S !a <b:b 6S          %|                  $o   "
")Z +XCX +W?W 3T ?g.X Dp (X  IX )X  HV           HY 6l 7i 5t <v #_ ?y 3p F~S Aq 8n            3p (Y $^ 9z 2v!{ :"
"~R E} Az NZ(Z :Z \"Z 4Z.] JZ 2`)`(_.Z Gt ?w :s Cx 5x!~d'Z(Z)Z N[<Z/\\/Z5[,[%Z'[&~^ @e 2X  Gf *_    MX   $Y     "
"LY   )h   :Y  <Y  NX 0X  >Y                 >X               8f /X 0f          3t   -s        c                "
"   4q /^ 6~S E~R Fr ,Z :~]+[;Z;Z Ms   #[    FX    F[        4n   @Y*Y   6m 7ZEZ 3k 5l        Bk 4o 1f   )k 0k #"
"X   #u     (b (i   Fb#X0c#W/k+X   .^ %] $^ %] $^ (d 5~b\"v H~S I~S H~R H~R 6Z !Z !Z \"Z :{ A_-Y Gt :t ;t ;s ;t "
"  0sGY*Z(Z#Z(Z$Z(Z$Y'Y$Z'[ LZ  Ls 2X  FX *WIW 1WJc 6ZEZ 4VBV      EY  FX *XJW 0YEZ 0X  EX )WJW 1ZEZ 1[I^ <WJc 0"
"X  EX )WJW 2WJZNW 5ZEZ      KX  FY *WIW 1ZEZ &X 7Y  FYEZ                 ?d M~h        8U   )T #e ?d=e 8U      "
"    *~Q                  &r   *Z +XCX +W?W 3T @i/W Dq (X  JX (X  HV           HX 7o <m 7x >x %_ ?y 5r F~S Ct :p"
"            6s /e *^ 9| 6z#~ =~R E} B}!Z(Z :Z \"Z 4Z/\\ HZ 2`)`(_.Z Iw @y >w Ez 9z!~d'Z(Z)[ Z;Z0]/Z4Z,Z$[(Z%~^ "
"@e 2X  Gf +a    MX   %Y     LY   *i   :Y  <Y  NX 0X  >Y                 >Y               9f /X 0g          5v  "
" 0u        d                   6_K_ 0^ 6~S E~R Gu .Z :~]+[;Z;Z w   &]    GX    G]      6U &o   ?Y+Y 7X )n 7ZEZ "
"6p 7m        Eo 6o 2h   *l 1l %X   #v     (b )k   Gb$X/c$X/l,W   -^ &_ %^ &_ %^ 'b 4~b$z J~S I~S H~R H~R 6Z !Z "
"!Z \"Z :~ D_-Y Hw =v >w >w >w   4wIX)Z(Z#Z(Z$Z(Z$Y'Y$[)[ KZ  Mt 1X  HX )WHW 2VHb 6ZEZ 4WDW      DX  GX )WHW 1YE"
"Z /X  GX )WHW 2ZEZ 0[M` ;VHb /X  GY *WHW 3VHb 5ZEZ      JX  GX )WHW 2ZEZ 'Y 7Y  FYEZ                 ?e M~f    "
"    7U   )U %g Bh@g :W          .~T                  't   +Z +XCX ,X@X 3T Ak1X Er (X  JX 'X  IV           HX 8q"
" =m 7y ?y '` ?y 6s F~S Dv <r            8u 4m /_ 9~ :~%~Q ?~R E} D~Q\"Z(Z :Z \"Z 4Z0\\ GZ 2`*a(`/Z Jz Bz Az F{ "
";{!~d'Z(Z(Z Z;Z0^0Z3Z.[#[*Z$~^ @X %X  :Y ,c    MX   &Y     LY   +^   .Y  <Y  NX 0X  >Y                 >Y      "
"         :] %X &]          5]C\\   1v        Nc                   7\\D\\ 1_ 6~S E~R Iy 0Z :~]+[;Z;Z!y   (_    H"
"X    H_      7U 'p   ?Y,Y 6X *o 7ZEZ 8t 9YH]        Ht 9o 3i   *XG[ 1VE[ &Y   %x     (b *[I[   Hb$W.c%X.VE[-X  "
" ._ &_ %_ '_ %_ '` 4~c%} L~S I~S H~R H~R 6Z !Z !Z \"Z :~Q F`.Y Jz @z Az Ay Az   7zKX(Z(Z#Z(Z$Z(Z$Y'Y#[*Z JZ  Na"
"J_ 2X  IX )WGW 2VG` 5ZEZ 4XFX      CX  IX )WFW 2YEZ .X  IX )WFW 3ZEZ /j 8VG` -X  HX *WFW 4VG` 4ZEZ      IX  IX "
")WGW 2ZEZ 'X 6Y  FYEZ                 ?XKX M~f        7T   )W 'i DiAi ;X          1~V                  (w   -Z "
"+XCX ,X@X 3T AZI[2W Es (X  KX &X  IV           HX 9s >m 7z @z )a ?y 7t F~R Dx >t            9v 8s 2` :~P <~Q&~S"
" A~R E} E~T$Z(Z :Z \"Z 4Z2] FZ 2a+a(`/Z K| C{ C} H| =|!~d'Z(Z(Z!Z9Z1^1Z2[0[!Z+[$~^ @X $X  ;Y -e    MX   'Y     "
"LY   +[   +Y  <Y  NX 0X  >Y                 >Y               :[ #X #Z          6\\?[   2v        F\\           "
"        8Z@[ 2` 7~S E~R J{ 1Z :~]+[;Z;Z#}   +`    HX    Ia      8U (q   >Y-Y 6X +p 7ZEZ 9bMb ;U@Y        JbMb :"
"n 3ZIZ   +T@Y 2R>Y 'X   %y     (XLV +ZEZ   IXMW%X.YMW%W-R>Y.W   -` '_ &` '_ &` '` 4~c'~R N~S I~S H~R H~R 6Z !Z "
"!Z \"Z :~S Ha/Y K| B| C| D} D|   9|MX'Z(Z#Z(Z$Z(Z$Y'Y\"Z+[ JZ  N]B\\ 2X  JX *WEW 3UE_ 5ZEZ 3YJY      AX  JW )WE"
"W 2YEZ -X  KX (WFW 3ZEZ .f 5UE_ ,X  JX )WFW 4VF_ 4ZEZ      HX  KX )WEW 3ZEZ (X 5Y  FYEZ                 @YJW M~"
"e        7U   *X (j EkCk =Y          3~X                  )x   -Z +XCX ,W?X 3T BYEY3X Ft (X  KX %X  JV         "
"  IX 9u ?m 7{ A{ *a ?y 8u F~R Ez @v            :v :w 4` :~Q >~S'~U C~R E} G~V$Z(Z :Z \"Z 4Z3] EZ 2a+a(a0Z M~P D"
"| E~P I} ?}!~d'Z(Z'Z\"Z9Z1^1Z1Z0Z [,Z#~^ @X $X  ;Y .g    MW   'Y     LY   +Y   )Y  <Y  NX 0X  >Y               "
"  >Y               :Z \"X \"Z          7[=Z   3aE[        E[                   9Z>[ 3` 7~S E~R L~ 2Z :~]+[;Z;Z$"
"~P   -b    IX    Jc      9U )r   >Y.Y 5X ,]DX 7ZEZ ;\\>\\ <R;X        M]>\\   0XDX   ,R=Y  MX (X   %hEW     (SG"
"V ,YAY   JSHW%W-SGW&X GX/W   ,` (a '` (a '` (a 5~d(~S N~S I~S H~R H~R 6Z !Z !Z \"Z :~T Ia/Y L~P F~P F~P F~P F~P"
"   <~X&Z(Z#Z(Z$Z(Z$Y'Y\"[-[ IZ  \\>Z 1X  LX )VCW 4UD] 4ZEZ 2f      ?X  LX )WDW 3YEZ ,W  KX )WDW 4ZEZ -b 2UD] *W"
"  KX )WDW 5UD] 3ZEZ      GW  LX (VCW 4ZEZ )X 4Y  FYEZ                 @XIX M~d        7U   *Y *l GmDl ?[       "
"   6~Z                  *`C\\   -Z +XCX ,W?W 2T CYCY5X E]CZ (X  LX $X  JV           IX 9]E^ @m 7aGb B^Ec ,b ?y "
"9aF[ F~R E_C_ B_E^            ;]E_ ={ 7b ;~R @cBb'~V D~R E} HeBc$Z(Z :Z \"Z 4Z4] DZ 2b-b(a0Z NbCb E} GbCb J~ Aa"
"B_!~d'Z(Z'Z#[9Z2_1Z0Z2[ N[.Z\"~^ @X $X  ;Y /i    MW   (Y     LY   ,Y   (Y  <Y  NX 0X  >Y                 >Y    "
"           :Y !X !Y          8[;Z 1\\ 0\\:U        D[                   ;Z<Z 4b 8~S E~R M~R 4Z :~]+[;Z;Z%bCb   "
"/d    JX    Ke      :U )]BW   =Y/Y 5X ,[?U   3Z8[ &W        NZ7Z   2XBW    EX  LW )X   %iEW      KV -Y?Y   @W&X"
"!W&W EW0X   -b )a (b )a 'a )a 5~d)dCb N~S I~S H~R H~R 6Z !Z !Z \"Z :~V Kb0Y MbCb HbCb HbCb HbCb HbCb   >bCh%Z(Z"
"#Z(Z$Z(Z$Y'Y![.Z HZ  Z;Z 1X  NX )WBV 5VBZ   $e      >W  MX )WBW   !X  MX )WBW   #` /UBZ (W  MX )WBW 6UBZ       "
" 9X  MW (WCW    MX 3Y                    GXHW M~d        8U   *[ +m HnFn A]          9~\\                  +^=Y"
"   -Z +XCX -X@X 2U DXAX5W E\\=V (X  LX #X .R@V?Q          ,X :\\A\\ @m 7\\>_ CY<_ -c ?y :^=V F~Q E]>^ D]@]     "
"       <Z@^ @~P 9b ;Z=d Aa;^'Z>j E~R E| Ha8^$Z(Z :Z \"Z 4Z5] CZ 2b-b(b1Z `<_ FZ@d I`=` K[@d C_:Z ~b&Z(Z'Z#Z8Z2`"
"2Z0[4[ LZ/[\"~^ @X #X  <Y 0\\N]    NX   )Y     LY   ,Y   (Y  ;X  NX 0X  >Y                 >Y               ;Z "
"!X !Y          8Z9Y 6d 4[5R        CZ                   ;Y:Z 5b 8~R D~Q MbAb 8` =~]+[;Z;Z&`=`   1f    KX    Lg "
"     ;U *\\=T   =Y0Y 4X ,Z;R   5Z3Y &W       !Y3Y   3W@W    EW  LX *W   %jEW      KV -X=X   @W'X W'X EX1W   ,b "
"*b (b )b )b )b 7ZH~R)a:] N~R H~R G~R H~R 6Z !Z !Z \"Z :Z>j Lb0Y N_<` J`<_ J`=` J`=` J`=`   @`=e%Z(Z#Z(Z$Z(Z$Y'Y"
" Z/[ HZ !Z9Y 0W  X )WAW 6VAW   \"d      <W  X (VAW    X  X (V@V   &a .VAW &X  NW (V@V 6UAW        6X  X )WAW   "
" NW 2Y         N\\ #[ \"\\ #\\ #[  MXHW L~b        7U   +\\ ,n IoGp C_          ;~]                  ,]:X   -Z "
"+XCX -X@X 8c LX@X7X E[:T (X  MX \"X /TAVAT          .X :\\?\\ Am 7Y9] CT4] .c ?Y  J]8S  Z E\\;\\ E]=[          "
"  <W;\\ B~T ;b ;Z7_ C_5['Z7e GZ  MZ '`3[$Z(Z :Z \"Z 4Z6] BZ 2b-b(b1Z!_8^ GZ;` K_9_ LZ:` D]5W 3Y 9Z(Z&Z$Z7Z3`3Z."
"Z4Z JZ0Z  \\ ?X #X  <Y 1\\L]    NX   *Y     LY   ,Y   (Y      8X  >Y                 >Y               ;Y  X !Y "
"         8Y8Y 6f 6Z2P        BY                   <Z9Z 7c 7\\  Z (`;` >j BZ(Z+[;Z;Z'_9_   3h    LX    Mi      <"
"U *[:R   <Y2Z 4X -Z8P   6Y/X 'W       #Y/Y   6W>V    EW  KW +W   %kEW      KV .X;W   @W'W NW(X CW2X   -c *c )b "
"*c )c +c 7ZHZ 2_5[ NZ !Z  Z !Z  >Z !Z !Z \"Z :Z7d Mc1Y ^8_ K^8^ L_8^ L_9_ L^8_   B_9b$Z(Z#Z(Z$Z(Z$Y'Y [1[ GZ !Z"
"8Y 0W !W (V?W      I`      :X !W (V?W    X \"X (W@W   *d    EX !W (W@W          0X \"X (V?W   !W 1Y        #d ,"
"e +d +d ,e #XHW LZ#Z        7U   +] -o KqHp C_          <c                   2]7V   -Z +XCX -W?X <l#X?X7W E[7R "
"(X  MX \"Y 0VCVCV          .X :[<[ B\\IZ 7V5] DQ0] 0XNZ ?Y  K\\4Q !Z E\\9\\ F\\;[            =U8[ DdAc =d <Z5^ "
"E^1Y'Z3b HZ  MZ (_/Y$Z(Z :Z \"Z 4Z7] AZ 2c/c(c2Z!]4] HZ9^ L^5^ MZ8^ E\\0T 3Y 9Z(Z&Z%Z6Z3`3Z-Z6[ J[2Z  \\ >X #X "
" <Y 2\\J]    NW   *Y     LY   ,X   'Y      8X  >Y                 >Y               ;Y  X  X          9Z7X 6g 7Y"
"        #Z                   =Y8Z 7d 7[  Z )_7_ Bp EZ(Z+[;Z;Z(^5^   5j    MX    Nk      =U +[7P   <Z3Y 3X -Y   "
" MX+W 'V       $X+X   7V=W    FW  KW ,W   $kEW      KV .X;X   AW(X NW(W BW2W   ,d +c *d +c *d +c 7ZHZ 3^0X NZ !"
"Z  Z !Z  >Z !Z !Z \"Z :Z3a Nc1Y!^5] L]4] N^5^ N^5^ N^5]   C^5_#Z(Z#Z(Z$Z(Z$Y'Y N[2Z FZ \"Z7Y /W #W (W>V      H^"
"      8X #W (W>V    NW \"W (W>W   .h    EW \"X )W>W          0W #X (V=V   \"W 0Y        &j 1i 0j 1j 1i &X <Z#Y "
"       7U   +_ /p KrJr Ea          >`                   .\\5U   -Z +XCX -W?W =r'X>W8X EZ  ;X  NY !X 1XDVDX 2X  "
"      &X ;[;[ BWDZ 7T2\\ \"\\ 1XMZ ?Y  L\\  2Z E[7[ G\\9[            >S5[ F`7` ?YNY <Z3\\ F]-W'Z0` IZ  MZ )^+W$"
"Z(Z :Z \"Z 4Z8] @Z 2YNX/XNY(c2Z\"]2] IZ7] N]2] MZ6] G\\-R 3Y 9Z(Z&[&Z6Z4XNW3Z-[8[ HZ3[ !\\ =X #X  <Y 3\\H]    N"
"W   +Y     LY   ,X   'Y      8X  >Y                 >Y               ;Y  X  Y          :Y6Y 7i 9Y        \"Y   "
"                >Y6Y 7YNY 6[ !Z *^3] Dt GZ(Z+[;Z;Z)]2]   6l    NX    m      >U +Z   !Y4Z 3X -Y    NW(W (W      "
" &X)X   8V<V +X  DW  LW ,W   $lEW      KV .W9W   AW(W MW)X CW2W   +YNY ,YNZ +YNY ,ZNY +YNY +YNY 9ZGZ 4^.W NZ !Z"
"  Z !Z  >Z !Z !Z \"Z :Z1` d2Y\"]2] N]2] ]2]!^2]!]2]   E]2]\"Z(Z#Z(Z$Z(Z$Y'Y MZ3[ FZ \"Z6X .V $W 'V<V      GZ   "
"   5W $W 'V<V    NW $W 'V<V   2m    EW #W (V<V          /W $W (W=W   #W 0Y        (n 6o 5n 5n 6n (X ;Z%Z       "
" 7U   ,a 0q LrJr Fc          A_                   ,\\2S   -Z +XCX .X@X ?u(W=X:X DY  :X  NX  Y 2ZFVFZ 2X        "
"'X :Z9[ CR?Z 7R/\\ \"[ 1XMZ ?Y  L[  2[ F[5Z G[7Z            >R4[ G^1^ AZNY <Z2[ G]*U'Z.^ IZ  MZ )](U$Z(Z :Z \"Z"
" 4Z9] ?Z 2YNX0YNY(d3Z#]0] JZ6\\ N\\/\\ NZ5\\ G[  <Y 9Z(Z%Z&Z6Z4XNX4Z,Z8Z FZ4Z  [ <X \"X  =Y 4\\F]       #Y     "
"LY   -Y   'Y      8X  >Y                 >Y               ;Y  X  Y          :Y6Y 7j :Y        \"Y              "
"     >Y6Z 9YMY 5[ \"Z *]1] Hy IZ(Z+[;Z;Z)\\/\\   8n    X   !o      ?U ,[    Y5Y 2X -Y    W&W )W       'W%W   9V"
"<V +X  DW  LW     )mEW      KV /X9X   BW)X MW)W BW3X   ,YMY ,YMY ,ZNZ -YMY +YNZ -YMY 9ZGZ 5]*U NZ !Z  Z !Z  >Z "
"!Z !Z \"Z :Z/_!d2Y#]0]!]0]\"]0\\!\\/\\\"]0]   F\\0]#Z(Z#Z(Z$Z(Z$Y'Y M[5[ EZ \"Y5X            +P                "
"       %_K[                              CY        *r 9q 8r 9r 9q *X ;Z%Z      >Q  JT   ,b 0q MsKs Ge          "
"C^                   *[0R   -Z +XCX .X@X @v)X=X:W CY  :X  Y  NX 1[HVH[ 1X        'X ;Z7Z 0Z 7P,[ ![ 3XLZ ?Y  M["
"  1Z EZ4[ I[5Z            ?P1Z I^-] BYLY =Z1[ H\\(T'Z-^ JZ  MZ *\\$S$Z(Z :Z \"Z 4Z:] >Z 2YMX1XMY(YNZ4Z$].\\ JZ5"
"\\!\\-\\ Z4[ GZ  ;Y 9Z(Z%Z'Z4Z5XNX5Z*Z:[ F[6Z  [ ;X \"X  =Y 5\\C[       #Y     LY   -Y   'Y      8X  >Y        "
"         >Y               ;Y  X  Y          :Y6Y 7k ;Y        \"Z                   @Z5Y 9YLY 5[ #Z +\\.] J| KZ"
"(Z+[;Z;Z*\\-\\   :p   !X   \"q      @U ,Z    NY6Y 1X -X    W#V *W       (W#W   :U;V +X  DW  LW     )mEW      KV"
" /X9X   BW*X LW*X BW3W   +YLY -YMY ,YLY -YMY ,YLY -YMZ ;ZFZ 5\\'S NZ !Z  Z !Z  >Z !Z !Z \"Z :Z-^\"e3Y#\\.]#].\\"
"#\\-\\#\\-\\#\\-\\   H\\.]$Z(Z#Z(Z$Z(Z$Y'Y L[6Z DZ \"Y5Y                                    /[G[               "
"               DY        +u =u <u ;u =u ,X :Y&Z      >S  LU   ,c 1q MtLt Hf          E]                   )[.Q "
"  -Z +XCX .W?X Bx)X=X;X DZ  :X  X  MY 0ZIVIZ /X        'X ;Z7[ 1Z  AZ ![ 4XKZ ?Y  MZ  0Z EZ3Z I[5Z             "
"Z J])\\ CYLY =Z1[ I\\%R'Z+] KZ  MZ +\\\"R$Z(Z :Z \"Z 4Z;] =Z 2YMX1XMY(YNZ4Z$\\,\\ KZ4[\"\\+[ Z4\\ I[  ;Y 9Z(Z$Z"
"(Z4Z5WLW5Z*[<[ DZ7[ !\\ ;X \"X  =Y 6\\A[       $Y     LY   -Y   'Y      8X  >Y                 >Y              "
" ;Y  X  Y          :Y6Y 7l <Y        !Y                   @Y4Z :YLY 4[ $Z ,\\,] M~Q MZ(Z+[;Z;Z+\\+\\   <r   \"X"
"   #s      AU ,Z    MY7Y 1X -Y   \"W!V :f       (V!W   ;U;V +X  EX  MW     (mEW      KV /W7W   BW*W KW+X BW3X  "
" +YLY .YKY -YLY .YKY -YLY .ZLY ;ZFZ 6\\%R NZ !Z  Z !Z  >Z !Z !Z \"Z :Z,^#YNZ3Y$\\,\\#\\,\\$\\,\\%\\+\\%\\,\\ MP"
" NP N\\-]$Z(Z#Z(Z$Z(Z$Y'Y KZ7[ Dq :Z4X                                    /XC[                              EY "
"       -x @x >x ?x @x -X :Z'Z      ?U  MU   -e 2q MtLt Ig          E[                   'Z,P   -Z +XCX .W?W By)"
"X<W;W CZ  :X  X  MY .ZKVKZ -X        (Y <Z5Z 1Z  A[ !Z 4XKZ ?Y  N[  1Z DZ3Z IZ3Y             NY K\\%[ EYKZ >Z0Z"
" J\\#Q'Z*\\ KZ  MZ +[ Q$Z(Z :Z \"Z 4Z<] <Z 2YMY3XLY(YMZ5Z%\\*\\ LZ4[\"[*\\!Z3[ IZ  :Y 9Z(Z$Z)[4Z6XLW5Z)Z<Z BZ8Z"
" !\\ :X !X  >Y 7[>[       %Y     LY   -Y   'Y      8X  >Y                 >Y               ;Y  X  Y          ;Y"
"5Y 7UH_ <Z        \"Z                   AY3Y ;YKZ 4[ %Z ,[*\\ N~S NZ(Z+[;Z;Z+[*\\   =\\NXM[   #X   $\\MXN\\    "
"  BU ,Z  *P DY8Y 0X -Y   #W NV @k       )V NV   <V;V +X  EW  NY     )nEW      KV /W7W   BW+X KW+W CY4X   +YKZ /"
"YKY .ZLZ /YKY .ZKY /YKY <ZEZ 7\\#Q NZ !Z  Z !Z  >Z !Z !Z \"Z :Z+]#YMZ4Y%\\*\\%\\*\\&\\*[%[)[%[*\\ R!R [-_%Z(Z#Z"
"(Z$Z(Z$Y'Y K[9[ Ct =Y3X                                    /U@[                 \"Q            EY        .z B{ "
"B{ Az B{ /X :Z'Y      >V  U   -g 4r NvNu Ji *\\ 5X.X 6\\ 7Z1Z M[                   '[    8Z +XCX /X@X C`MTL_)W;"
"W<X CY  9X !Y  LX ,ZMVMZ +X        (X ;Z5Z 1Z  A[ !Z 5XJZ ?Y  NZ  0Z DY2Z J[3Z      )Q   Q   JZ M[!Z FYJY >Z0Z "
"J[ 'Z)\\ LZ  MZ ,\\ \"Z(Z :Z \"Z 4Z=] ;Z 2YLX3XLY(YMZ5Z%[([ LZ3[$\\)\\\"Z3[ IZ  :Y 9Z(Z$Z)Z3Z6XLX6Z(Z>[ B[:Z !"
"\\ 9X !X  >Y 8[<[       &Y     LY   -Y   'Y      8X  >Y                 >Y               ;Y  X  Y          ;Y5Y "
"7RB] =\\        $Z                   BY2Y ;YJY 3[ &Z -[(\\!~U Z(Z+[;Z;Z,\\)\\   ?\\MXL[   $X   %\\LXM\\      CU"
" ,Y *Q\"R DY9Y 0X -Y   #V=_?V Cm       *V LV   <U;V +X  FX \"[     (nEW      KV /W7W   BW+W JW,X F[3W   *YJY 0Z"
"KZ /YJY /YKZ /YJY /YJY =ZEZ 7[!P NZ !Z  Z !Z  >Z !Z !Z \"Z :Z*]$YMZ4Y%[([%[(['\\)\\'\\)\\'\\)[!T#T\"\\-`&Z(Z#Z("
"Z$Z(Z$Y'Y J[:Z Bw @Y6[                                    .Q<[                 #S            GY        /`Da E`C"
"` DaD` C`Da E`C` 0X 9Y(Z      ?X !U   .h 4r NvNu Kk .c 9X.X 7^ 7Y1Y M[                   &Z    7Z +XCX /X@X C\\"
"ITFY)W;W=X BY  9X !X  KY +YNVNZ *X        (X ;Z4Z 2Z  @Z !Z 6YJZ ?Y  Z  /Z DY2Z JZ1Y      ,T   T   MZ N[ NZ HZJ"
"Y >Z0Z K[ &Z(\\ MZ  MZ ,[ !Z(Z :Z \"Z 4Z>] :Z 2YLX3XLY(YLZ6Z&['\\ MZ3[$['[\"Z2Z IZ  :Y 9Z(Z#Z*Z2Z7XLX7Z'[@[ @Z;"
"[ ![ 8X !X  >Y 9[:[       'Y     LY   -Y   'Y      8X  >Y                 >Y               ;Y  X  Y          ;Y"
"5Y %\\ =]        %Y                   BY2Z =ZJY 3\\ 'Z .\\'[#cLZLb!Z(Z+[;Z;Z,['[   @\\LXK[   %X   &\\KXL\\     "
" DU -Z +S$T EY:Y /X -Z   %V?fBU Eo       +VEg=V   =V<V +X  GX *b     &nEW      KV /W7W   BW,X JW,W Nb2X   +ZJY "
"0YIY /YJY 0YIY /YJZ 1YIY =ZEZ 8\\  NZ !Z  Z !Z  >Z !Z !Z \"Z :Z)\\$YLZ5Y&\\'['['\\(['['['['['[#V%V#[-a&Z(Z#Z(Z$"
"Z(Z$Y'Y IZ;Z Ay BY9^                                     G[                 %U            HY        0]<^ G^=^ F"
"^<] E]<^ G^=^ 1X 9Z)Z      @Z \"U   .i 5r NvNu Lm 2h ;X.X 7^ 7Y1Y N[                   &[    7Z +XCX /W?X D[GTC"
"V)W;W=W AZ  :X \"Y  KY *j (X        (X <Z3Z 2Z  @Z !Z 6XIZ ?Y  Z  0Z DZ2Z JZ1Z      0W   V   Y NZ KZ IYIZ ?Z0Z "
"K[ &Z(\\ MZ  MZ -[  Z(Z :Z \"Z 4Z?\\ 8Z 2YKX5XKY(YLZ6Z&[&[ MZ3[%[&\\#Z2[ JZ  :Y 9Z(Z#Z+Z1Z7WJW7Z&Z@Z >Z<Z ![ 7X"
"  X  ?Y :[8[     \"\\ 3YBZ  \\ ,ZAY 4\\ &Y \"Z 0YAZ     \"X  >Y .Y3Y 3Z '\\  MZ )Z  ;Z 2^ +Y               ;Y  "
"X  Y        6Y /Y5Y $[ =`  G^ !Z    IZ             M\\     #Y2Z =YIZ 3\\ (Z .[%[%aIZI`\"Z(Z+[;Z;Z-[%[   B\\KXJ["
"   &X   '\\JXK\\      H\\ 1Z ,U&V EY;Y /X ,Z   'V@jDV Gp       +UDj?V   >V<V +X  GW )`     $nEW      KV /W7W   "
"BW-X IW-X N`0W   *YIZ 1YIY 0YHY 1YIY 0ZIY 1YIZ ?ZDZ 8[  MZ !Z  Z !Z  >Z !Z !Z \"Z :Z(\\%YLZ5Y&[&['[&[)\\&[)[%[)"
"[&[$X'X%[-b&Z(Z#Z(Z$Z(Z$Y'Y I[=[ Az CY;` 5\\ $] $\\ \"\\ #\\ $] 8\\/[ 3\\ '\\ #\\ \"[ \"[          \"[ &Z &[ !["
" #\\ #[ ![    G[@W            IYBZ        J]8] I\\7\\ H]8] I]8] I\\7\\ 2X 8Y*Z      @Z \"U   .k 5q N~o Mm 4l =X"
".X 7^ 7Z3Z NZ                   %Z    6Z +XCX /W?W D[FT@S)W;W>X AZ  :X \"Y  JX (f &X        )X ;Z3Z 2Z  @Z !Z 7"
"XHZ ?Y !Z  /Z CY1Y JZ1Z      2Y   Y  $Z Z HY JYHY ?Z/Y L[ %Z'\\ NZ  MZ -[  Z(Z :Z \"Z 4Z@\\ 7Z 2YKX5XKY(YKZ7Z'["
"$[ NZ2Z%[%[#Z2[ JZ  :Y 9Z(Z#[,Z1Z8XJW7Z%ZB[ >[>Z !\\ 7X  X  ?Y ;[6[     (e 7YE` (e 3aEY 8c 2r 5`DX GYEa (X  NX "
"0X1Z 8Y FXD`9` YD` -c 9XD` /aEX :XD] 6g 7t BX0Y LY)Y+X6Z6X)Z/Z NX)Y I} 2Y  X  Y        9_>W KY5Y #[ =c  h >XD` "
"AT#X 5Y 6X0X LY'Y ?RCW ?~Y!X?X?X ;d 'r!~W KZ1Y =YHY 2\\ )Z /[$[%_GZG_#Z(Z+[;Z;Z-[%[   C\\JXI[   'X   (\\IXJ\\  "
" (Y  d 5Z -W(X FY<Y .X ,[   (UAmDV Iq       ,VDl@U   >V=W +X  HX )^   ,Y1Y HnEW      KV 0X7W   BW-W HW.X M^/X )"
"Y +YHY 2YHZ 1YHY 2ZHY 1YHY 2ZHY ?ZDZ 9[  LZ !Z  Z !Z  >Z !Z !Z \"Z :Z'[%YKZ6Y'\\%[)[$[*[%[)[%[)[%[%Y)Z&[.d'Z(Z#"
"Z(Z$Z(Z$Y'Y H[>Z @{ DY=b ;f -f -f ,e -f -f Ae7c ;e /b )c *c *c 'Y  NX  NX  X  E[ >XD` -c )c *b *c )c '\\ &bDX L"
"X0X GX0X GX0X GX0X KY)X KYE` ?Y*Y     8[4\\ K[3[ J\\4[ I[4\\ K[3[ 3X 8Z+Z      AZ !U   /m 6q N~o No 6o ?X.X 8_ "
"6Y3Z Z                   $Z    6Z +XCX 0X@X DZET>Q)W;W>W ?Y  :X \"X  IY 'b $X        )X ;Z2Y 2Z  @Z !Z 8YHZ ?Y "
"!Z  0[ CY1Y JZ1Z      5\\   \\  'Z!Z FY LZHZ @Z/Y L[ %Z&[ NZ  MZ .[  NZ(Z :Z \"Z 4ZA\\ 6Z 2YKX6YKY(YKZ7Z'[$[ NZ"
"2Z&[#Z#Z2[ JZ  :Y 9Z(Z\"Z,Z1Z8XJX8Z%[D[ <Z?[ \"\\ 6X  X  ?Y <[4[     -l :YGd ,k 9eGY :h 5r 8eGY GYGe +Y  NX 0X3"
"\\ 8Y FYGd=c!YGe 2h ;YGd 3eGX ;YG` 9m :t BY1Y LZ+Z+Y7[7Y*[1Z MY+Z J~ 2Y  X  Y        <eAW KY5Y \"Z <f 'o CYFd D"
"Y(Y 5Y 6Y1Y MY'Z CUE\\ B~Y!Y@X@Y =h 0z\"~W KY0Y >ZHY 1\\ *Z /[#['^EZE^$Z(Z+[;Z;Z.[#Z   C[IXH[   (X   ([HXI[   ("
"Z $k 9Z .Y*Z FY=Y .X ,\\   *UAnCU J^CW       -VCmAV   ?W>V *X  IX (a   /Y1Y HnEW      KV 0X7W   BW.X HW.W La3X "
"(Y ,ZHY 2YGY 2ZHZ 3YGY 1YHZ 3YGY @ZCZ 9[  LZ !Z  Z !Z  >Z !Z !Z \"Z :Z'\\&YJY6Y'[$[)[$[*[$[+[#[+[$[&[+\\([.e'Z("
"Z#Z(Z$Z(Z$Y'Y GZ?Z ?| EY>c >l 4l 3l 2l 3l 4l Gl=h @k 5h /h /h /h )Y  Y  NX  Y  E[ ?XFd 1g .h /h /h /h )\\ )hHX "
"LY0X HY0X GX0X GX0Y LZ+Y KYGd AY*Y     9[EXD[ M[1[ L[1[ K[1[ M[1[ 4X 8Z+Y      A[ !T   /n 6q N~o q 8q @X.X 8` 7"
"Y3Y Z                   $Z    5Z +XCX 0X@X DYDT EW;W?X ?Y  :X #Y  IY %^ \"X        )X <Z1Z 3Z  @Z !Z 8XGZ ?Y !Z"
"  0Z BY2Z JY0Z      8_   _  *Z!Y DX LYFY @Z/Y M[ $Z&[ NZ  MZ .[  NZ(Z :Z \"Z 4ZB\\ 5Z 2YJX7XJY(YJZ8Z([#[ NZ2Z&["
"#[$Z2[ JZ  :Y 9Z(Z\"Z-Z/Z9XJX9Z#ZDZ :Z@Z \"\\ 5X  NX  @Y =[1Z     1q <YIh 0o =hHY <l 7r 9hIY GYHg ,Y  NX 0X4\\ "
"7Y FYIg@g#YHh 6l =YIh 7hHX ;YHa ;q <t BY1Y KY+Y*Y8\\8Y([3[ MY+Y I~ 2Y  X  Y        =gCX KY6Z !Z <i -q CYHh F[*Y"
" 5Z 7Y1Y NZ&Y EWG` D~Y!Y@X@Y >k 5}\"~W KY0Z ?YGZ 1[ *Z /Z\"[(]CZD^%Z(Z+[;Z;Z.[#[   CYHXGY   'X   'YGXHY   'Z &o"
" ;Z /[,[ FZ?Y -X +\\   +UBoBU LZ>W       -UBnAU   >W@W *X  JX 'c   1Y1Y HnEW      KV /W7W   BW.W GW/X Lc5W 'Y ,"
"YFY 4ZGY 2YFY 3YGZ 3YFY 3YGZ AZCZ 9Z  KZ !Z  Z !Z  >Z !Z !Z \"Z :Z&[&YJZ7Y'[#[*Z\"Z+[#[+[#[+[#[&[-\\'[/YM[(Z(Z#"
"Z(Z$Z(Z$Y'Y G[A[ ?} FY?] :p 8q 8q 7q 8q 8p LqAl Do 9l 3l 3l 3l +Y  Y  NX  Y #i @XHh 5k 2l 3l 3k 2l +\\ +lKX KY0"
"X HY0X GX0X GX0Y KY,Z KYIh CZ,Z     :ZCXC[ [/[ N[.Z MZ.[ [/[ 5X 7Y,Z      AZ !U   /o 7p M~n s :s AX.X 8` 7Z4Y Y"
"                   #Z    5Z +XCX 0W?X EYCT EW;W@X >Z  ;X #Y  HX #Z  X        *X ;Z1Z 3Z  @Z !Z 9XFZ ?Y \"Z  /Z "
"BY2Z KZ0[      <b   a  -[\"Y BX MYFY @Z0Z M[ $Z%[ Z  MZ .Z  MZ(Z :Z \"Z 4ZD] 4Z 2YJX7XJY(YJZ8Z([\"[ Z2Z&Z\"[$Z2"
"[ JZ  :Y 9Z(Z!Z.Z/Z9WHW9Z\"ZF[ :[BZ \"\\ 4X  NX  @Y >[/Z     4t =YJj 3q >kJY >o 8r ;kJY GYJk .Y  NX 0X5\\ 6Y FY"
"JiBi$YJk 8o ?YJj 9kJX ;YJc <r <t BY1Y KZ-Z)X8\\8Y'Z4[ LZ,Y I~ 2Y  X  Y        ?jDX KY6Y  Z ;k 1r CYIj G]-Z 5Z 7"
"Y1Y NZ&Z HYHb E~Y!Y@X@Y @n 8~P\"~W KY0Z ?YFY 0[ +Z 0[!Z)]BZB]&Z(Z+[;Z;Z.Z\"[ LQ  GWGXFW  HQ /X /Q*Q @WFXGW   &Z"
" (q ;Z .[BVB[ DY@Z -X *]   .UC^EXBU LX<W       .VBWC[AU   ?WAW )X  KX %c   2Y1Y HnEW      KV /W7W   BW/X GW/W J"
"c7X 'Y ,YFY 4YFZ 3YFY 4YEY 3YFY 4ZFY AYBZ :[  KZ !Z  Z !Z  >Z !Z !Z \"Z :Z&[&YIZ8Y([\"[+[\"[,[\"Z+Z!Z,[\"[%[/\\"
"&Z/YL[(Z(Z#Z(Z$Z(Z$Y'Y F[BZ >Z@d GY@\\ :t ;t <u ;t ;t ;t tDn Gr <o 6o 6o 6o ,Y  Y  NX  Y &l @XIj 8o 5o 6n 6o 5o"
" -\\ ,nLW JY0X HY0X GX0X GX0Y KY,Y JYJj CY,Y     :ZBXBZ!Z+Z Z,Z Z,Z!Z+Z 6X 7Z-Z      BZ  U   0q 7o M~n s ;u BX."
"X 9a 6Y5Z!Y                   \"Z    5Z +XCX C~d&YCT EW;W@W =[  <X #Y  HY $Z  X        *X ;Z1Z 3Z  @Z !Z :YFZ ?"
"Y \"Z  0Z AZ3Z KZ0[ 5Z \"[  ?e   d  0Z\"Y AY YEZ AZ0Z MZ #Z%[ Z  MZ /[  MZ(Z :Z \"Z 4ZE] 3Z 2YJY9XIY(YIZ9Z(Z![ "
"Z2Z'[!Z$Z2[ JZ  :Y 9Z(Z!Z/[/Z:XHW9Z\"[H[ 8ZC[ \"[ 3X  NX  @Y ?[-Z     5v ?YKm 6r ?mKY ?q 9r <mKY GYKm /Y  NX 0X"
"6[ 4Y FYKkEl%YKm ;r @YKl ;mKX ;YKd >t <t BY1Y JY-Y(Y9]9Y&Z5Z JY-Y H~ 2Y  X  Y        @lFX JY6Y  NY 9k 4s CYJl H"
"^.Y 4[ 8Y1Y NY$Y J[Ie G~Y!Y@X@Y Ap ;~R\"~W KY0Z @YEZ 0[ ,Z 0Z [*\\AZA\\&Z(Z+[;Z;Z/[![ NS  GUFXEU  HS 0X 0S,S @U"
"EXFU   %Z )r ;Z -[G^G[ CZAY ,X )]   /UC[>TAU NX;W )P9P     =UAWAYAU   >XDX )X  LX  HY   3Y1Y HnEW      KV /W7W "
"AP9P 9W0X FW0X ?Y8W &Y -YEZ 5YEY 4ZFZ 5YEY 4ZEY 5YEY BZBZ :[  KZ !Z  Z !Z  >Z !Z !Z \"Z :Z%['YIZ8Y([!Z+Z![,Z![-"
"[![-[!Z$[1\\&[/XJZ(Z(Z#Z(Z$Z(Z$Y'Y EZCZ =Z;` HYA[ 8u <u =v <v =u <u!uGr Js =r 9r 9r 9r .Y  Y  NX  Y (o AXJl :q "
"7q 9r 9q 7q .\\ -y IY0X HY0X GX0X GX0Y KZ-Y JYKl DY-Z     ;ZAXAZ\"Y)Y!Z*Z\"Z*Z\"Y)Y 6X 7Z-Y      BZ  NT   0s 8o"
" L~m!u =w CX.X 9b 7Y5Y Y                   \"Z    5Z +XCX C~d&YCT EX<WAX <Z  <X #X  GY &^ \"X        *X ;Z0Y 3Z"
"  @Z !Y 9XEZ ?Y \"Z  0Z AZ3Y JZ/Z 5Z \"[  Ag   g  4[\"X ?X YDY AZ0Z MZ #Z%[ Z  MZ /[  MZ(Z :Z \"Z 4ZF] 2Z 2YIX9"
"XIY(YIZ9Z(Z Z Z2Z'[![%Z2[ JZ  :Y 9Z(Z!Z/Z.Z:XHX:Z!ZHZ 6ZDZ \"\\ 3X  NY  AY @Z*Z     6w @YLo 9t @oLY At :r =oLY "
"GYLo 0Y  NX 0X7[ 3Y FYLmGn&YLo =t AYLo >oLX ;YLe ?u <t BY1Y JY-Y(Y9]9X%[7Z IZ.Y H~ 2Y  X  Y        AnGX JY7Z  N"
"Z 9k 6t CYKn I^/Z 5\\ 8Y1Y Z$Z L\\Jg H~Y!Y@X@Y Br =~S\"~W LZ/Y @YDY /[ -Z 0Z NZ+\\@Z@\\'Z(Z*Z;Z;Z/[![ U  GSEXDS"
"  HU 1X 1U.U @SDXES   $Z +t ;Z ,[JbJ[ AYBY +X (^   2UCZ9QAU NW:W *Q:Q     >VAW?XAU   ?ZHY (X  MX  EX   4Y1Y HnE"
"W      KV /W7W AQ:Q :W0W EW1X <X:X &Y -YDY 6ZEZ 5YDY 6ZEZ 5YDY 5YEZ CZBZ :Z  JZ !Z  Z !Z  >Z !Z !Z \"Z :Z%['YHZ"
"9Y(Z Z+Z Z-[![-[![-Z [$[3\\%[0XI[)Z(Z#Z(Z$Z(Z$Y'Y E[E[ =Z9^ HYBZ 6v =v >w =w >v =v\"vIt Lt >t ;t ;t ;t /Y  Y  N"
"X  Y *r BXKn <s :t ;t ;s :t /\\ /{ IY0X HY0X GX0X GX0Y JY.Z JYLo FZ.Y     :Y@X?Y$Y'Y#YIP5PIY\"Y.PIY$Y'Y 7X 6Z/Z"
"      CZ  NU   1u 8m K~m\"w ?^C] CX.X 9b 7Z6Y X                   \"Z    4Z +XCX C~d&XBT EX=XAW ;[  =X $Y  GY ("
"b $X        +X :Y/Z 4Z  @Z \"Z :XDZ ?Y \"Y  0[ @Y4Z JZ/Z 5Z \"[  Dj   j  8[\"X =X\"ZDY AZ0Z N[ #Z$[!Z  MZ /Z  L"
"Z(Z :Z \"Z 4ZG] 1Z 2YIX:YIY(YHZ:Z)[ [!Z2Z'Z [%Z2[ J[  ;Y 9Z(Z Z0Z-Z;XHX;Z NZJ[ 6[FZ \"\\ 2X  MX  AY AZ(Z     7x"
" AYMq ;u AqMY Bv ;r >qMY GYMp 0Y  NX 0X8[ 2Y FYMoIp'YMq ?v BYMp ?qMX ;YMf ?u <t BY1Y JZ/Z(Y:^:Y$[9[ HY/Z H~ 2Y "
" X  Y        BpHX JY7Z  MY ;o 9u CYLp J_0Y 4\\ 8Y1Y Y#Z M]Jh I~Y!Y@X@Y Ct ?~T\"~W LZ/Y AZDY .[ .Z 1[ NZ+[?Z?['Z"
"(Z*Z;Z;Z/Z NZ!W  GQDXCQ  HW 2X 2W0W @QCXDQ   #Z ,u ;Z +[MfM[ ?YCY +X '_   4UDZ'U W:W +R;R     >U@W?XAU   >j (X "
" NX  CX   5Y1Y HnEW      KV /W7W AR;R ;W1X EW1W :X<X %Y .ZDY 6YCY 5YDZ 7YCY 5YDZ 7ZDY DZAZ ;[  JZ !Z  Z !Z  >Z "
"!Z !Z \"Z :Z$Z'YHZ9Y)[ [-[ [.[ Z-Z NZ-Z [#[5\\$Z0XH[)Z(Z#Z(Z$Z(Z$Y'Y D[FZ <Z7] IYBY 5w >w ?x >x ?w >w#wKv Nu ?v"
" =v =v =v 0Y  Y  NX  Y +s BXLp >u <v =v =u <v 0\\ 0{ HY0X HY0X GX0X GX0Y JZ/Y IYMp EY.Y     ;Y?X?Y%Y%Y$YJR7RIY$"
"Y.RJY%Y%Y 8X 6Z/Y      CZ  MU   2v 8m K~m#y @[>\\ DX.X :c 7Z7Z!Y                   \"Z    4Z +XCX C~d&XBT DW=XB"
"X :[  >X $Y  FY +f &X        +X ;Z/Z 4Z  AZ !Z ;YDZ ?YFP -Z?Q  BZ ?Z5Z JZ/Z 5Z \"[  Gj   Ii  ;[\"X1Q,W\"YCZ BZ1"
"Z MZ \"Z$[!Z  MZ /Z  LZ(Z :Z \"Z 4ZH] 0Z 2YHX;XHY(YHZ:Z)Z N[!Z2Z([ NZ%Z2Z I[  ;Y 9Z(Z Z1Z,Z;XGW;Z N[L[ 4[H[ #\\"
" 1X  MX  AY BZ&Z     8^Ga AYN[H_ <cI\\ B`I[MY CaH_ <r ?`H[NY GYNr 1Y  NX 0X9[ 1Y FYNqJp'YMq @aJa CYN[H_ A`I[MX "
";YNg @`E[ <t BY1Y IY/Y&X:^:Y#Z:[ GY/Y G~ 2Y  X  Y      JW5V B`M_JX IY8Z  LY =r ;cL_ CYM^Na J`1Y 5^ 9Y1Y!Z\"Z ^K"
"j J~Y!Y@X@Y D_I` A~U\"~W LY.Y AYCZ .[ /Z 1Z MZ,\\?Z?\\(Z(Z*Z;Z<[/Z NZ\"Y  ;X  ;Y 3X 3Y2Y 3X    EZ -hM[ ;Z *~Q >"
"YDY *X )b   6UDY%U V9W ,S<S     >U@W>W@T   =h 'X  X  AW   5Y1Y HnEW      KV /X9X AS<S <W1W DW2X 9W<W $Y .YCZ 7Y"
"CY 6YBY 7YCY 6ZCY 7YCZ EZAZ ;[  JZ !Z  Z !Z  >Z !Z !Z \"Z :Z$Z'YGZ:Y)[ NZ-[ [.Z N[.Z NZ.[ NZ\"[7\\$[1XFZ)Z(Z#Z("
"Z$Z(Z$Y'Y CZGZ ;Z6\\ IYCY 4^Ga ?^Ga @_Hb ?^Ga ?^Ga ?^Ga$^GaMaI`!bH\\ @aI` ?aI` ?aI` ?aI` 1Y  Y  NX  Y ,u CXM^Nb"
" @aKa >aJa ?aJa ?aKa =`Ja 1\\ 0`Ic GY0X HY0X GX0X GX0Y IY0Z IYN[H_ FZ0Z     <Y>X>Y&X#X%YJT9TIY&Y.TJY&X#X 8X 5Y0"
"Z      CZ ;P4U   1w 9l J~m#z B[;[ EX.X :d 7Y7Y X                   )~Q   #Z +XCX C~d&XBT DW=XCX 9\\  ?X $Y  FY "
"-j (X        +X ;Z/Z 4Z  AZ \"Z :XCZ ?YM_ 5ZE^  IZ >Y6Z IZ0[ 5Z \"[  Jj   Ci  ?\\\"X6\\2X#YBY BZ1Z MZ \"Z$[!Z  "
"MZ 0[  LZ(Z :Z \"Z 4ZI] /Z 2YHX;XHY(YGZ;Z)Z N[!Z3[([ NZ%Z2Z H[  <Y 9Z(Z NZ2Z,Z<XFW;Z MZLZ 2ZHZ #\\ 0X  MX  AY C"
"Z$Z     9Y>^ BcB] >_?W C^CYNY C]A] 4Y /]Bc GYNYD^ 2Y  NX 0X;\\ 0Y FYNXC\\KYD](YNYC] A]B^ DcB] C^CYNX ;YNZDQ A\\"
";V 5Y .Y1Y IY/Y&Y;_;Y\"Z;Z FZ0Y $[ 2Y  X  Y      M];\\ F]E[JX IY9[  LY >ZKf =]=V CYNYC] K`2Z 5^ 9Y1Y!Z\"Z!^JZM^"
" K~Y!Y@X@Y E]C^ CaHl\"~W LY.Z BYBY .\\ 0Z 1Z M[-[>Z>[(Z(Z*Z;Z<[0[ N[$[  <X  <[ 4X 4[4[ 4X    EZ ._KUHV ;Z )~ <Y"
"EY *X *e   8UDY$T!W:X .U=T     ?U?W>W@U   =f &X !X  @W   5Y1Y HnEW      KV /X9X AT=T =W2X DW2W 8W=X $Y .YBY 8ZC"
"Z 7YBY 8ZCZ 7YBY 8ZBY FZ@Z ;Z  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z$[(YGZ:Y)[ NZ-Z MZ.Z N[/[ N[/[ NZ![9\\#[2YFZ)Z(Z#Z(Z"
"$Z(Z$Y'Y C[I[ ;Z5\\ JYCY 4X=^ @X=] @Y=] ?Y>^ @X=^ @X=^%X=l@\\\"_?W A]@\\ @]@\\ @^A\\ @^A\\ 1Y  Y  NX  Y -w DXNY"
"C] A^C^ ?^C^ A^B] @^C^ ?^C^ 2\\ 1^C_ FY0X HY0X GX0X GX0Y IY0Y HcB] FY0Y     ;X=X=Y(Y#Y'YJV;VIX&X.VJY(Y#Y 9W 4Z1"
"Z      DZ =S4U   2y 9j I~l#{ BZ9Z EX.X :d 7Z8Y!Y                   *~R   #Z +XCX C~d'YBT DX?XBW 7\\  @X $Y  FY "
"/ZNVNZ *X        ,X :Z/Z 4Z  AZ #Z :XBZ ?o 9ZGc  MZ =Z8[ HY0\\ 6Z \"[  Li   >j  C\\\"X8aGVBW$ZBZ CZ2Z LZ \"Z#Z!"
"Z  MZ 0[  LZ(Z :Z \"Z 4ZJ] .Z 2YHX<YHY(YFY;Z)Z MZ!Z3[([ N[&Z3[ H]  >Y 9Z(Z NZ2Z,Z<XFX<Z LZN[ 2[JZ \"[ /X  LX  B"
"Y DZ\"Z     :U7\\ Ca>\\ @^:T C\\?b D\\=\\ 5Y 0\\>a Ga?\\ 2Y  NX 0X<\\ /Y Fa@\\MX@[(b@\\ B]?\\ Da?] D\\?a ;b 1Z6"
"S 5Y .Y1Y IZ1Z&Y;_;X![=Z DY1Y #[ 2Y  X  Y      `>` I\\B[KX IY:\\  LY ?ZDa ?\\7R Cb?\\ F[3Y 5_ 9Y1Y\"Z Y!]IYJ] L"
"~Y!Y@X@Y F\\?\\ D^Ai\"~W LY.Z CZBZ .\\ 1Z 1Z LZ.[=Z>[(Z(Z*Z;Z<[0[ N[%\\  <X  <\\ 5X 5\\4\\ 5X    EZ /^IUFT ;Z ("
"| ;YFY )X +h   :TDY#U\"W:X /V?V     ?U?W>XAU   <c $X \"X  ?X   6Y1Y HnEW      KV .W9W @U>V ?W3X CW3X 8X>W #Y /Z"
"BZ 9YAY 8ZBZ 9YAY 8ZBZ 9YAY FZ@Z ;Z  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z$[(YFZ;Y)Z MZ-Z MZ/[ MZ/[ N[/Z M[![;\\\"[3YE[*"
"Z(Z#Z(Z$Z(Z$Y'Y B[JZ :Z4[ JYCX 3U8\\ @U8\\ AV8\\ @U7\\ AU7[ @U8\\%U8h=\\$]9T B\\=\\ B\\=\\ B\\=\\ B\\<[ 2Y  Y  "
"NX  Y .x Da?\\ C]?] A]?] B\\?] B]?] A]?] 3\\ 2]?] FY0X HY0X GX0X GX0Y IZ1Y Ha?] GY1Z     <X<X<X(X!X'XJX=XJY(X.X"
"JX(X!X 9W 4Z1Y     >~d W5T   2{ 9i H~k$} DZ7Z FX.X :d 7Z9Z!X                   )~R   #Z   0~d&XBT DX?XCX 6\\   "
" =Y  EY 0ZMVMZ +X        ,X :Z/Z 4Z  B[ %\\ :XBZ ?q ;YHg  Z <Z:[ GZ1\\ 6Z \"[  i M~c Nj  G\\!W9eIVBX%Y@Y CZ3[ M"
"[ \"Z#Z!Z  MZ 0Z  KZ(Z :Z \"Z 4ZK] -Z 2YGX=XGY(YFZ<Z*[ MZ!Z3[(Z M[&Z3[ H^  ?Y 9Z(Z NZ3Z*Z=XFX=Z Kf 0[L[ #\\ /X "
" LX  BY        JS4[ C`<\\ A\\5Q D[;` E[9Z 5Y 1\\<` G`<Z 2Y  NX 0X=\\ .Y F_=[MV=[)`<[ D\\<\\ E`<[ E[;_ ;` 0Z3Q 5"
"Y .Y1Y HY1Y%Y<`<Y [?[ DZ2Y $[ 1Y  X  Y     !cBc J[?YLX HY<]  JX @Y?_ @[ '`<[ EZ4Z 5` :Y1Y\"Z Z#\\GYI\\ EZ:Z IY@"
"X@Y FZ;[ E]>\\ 0Z 6Y.Z CYAZ -\\ 2Z 1Z LZ.[=Z=[)Z(Z*Z;Z<Z/Z LZ&\\  ;X  ;\\ 6X 6\\2\\ 6X    EZ /\\GUCQ ;Z 'z 9YGY"
" )X -ZN_   ;TDX\"U\"W;Y 0W@W     ?T>W>X@T   ;a #X #X  =W   6Y1Y GmEW      KV .X;X @W@W @W3W BW4X 6W?X #Y /Y@Y :"
"ZAY 8Y@Y 9YAZ 9Y@Y 9YAZ GZ@Z ;Z  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z#Z(YFZ;Y)Z M[/[ MZ/[ MZ/Z LZ/Z M[ [=\\!Z3YD[*Z(Z#Z"
"(Z$Z(Z$Y'Y AZKZ 9Z4[ JYDY 3R3[ AR3[ BS3Z @S4[ AS4[ AR3[&R3e:[&]6R C\\:[ D\\:[ D\\:[ D\\:[ 3Y  Y  NX  Y /_B] E_<"
"[ C[;[ B\\<\\ C\\<\\ C[;\\ C\\<\\ 3\\ 3\\<\\ FY0X HY0X GX0X GX0Y HY2Z H`<[ FY2Y     ;X<X<X)X NX)YKZ?ZJX(X/ZKX)X"
" NX ;X 3Y2Z     >~d#Z6U   3} :h G~k%~P EY5Y FX.X ;ZNY 6Y9Z!X                   *~R   \"Z   0~d&YCT CXAXBW 5]   "
" >Y  EY 2ZKVKZ -X        ,X :Z/Z 4Z  BZ &] :XAZ ?s =YJk #[ ;[=[ FZ1\\ 6Z \"[ #j L~d Ki  J\\!X:hKVAW%Y@Y CZ5\\ L"
"[ \"Z#Z!Z  MZ 0Z  KZ(Z :Z \"Z 4ZL] ,Z 2YGX=XGY(YEZ=Z*[ M[\"Z4['Z LZ&Z4[ F`  BY 9Z(Z MZ4Z*Z=XEW=Z Jd .ZLZ #\\ .X"
"  LX  BY        JQ1[ D_:[ B\\ ([9_ F[7Z 6Y 1[:_ G^9Z 3Y  NX 0X>\\ -Y F^;b;Z)_:Z D[:\\ F_:[ G[9^ ;_ /Y  EY .Y1Y "
"HY2Z$Y=a=Y NZ@[ BY3Z %[ 0Y  X  Y     \"eCd L[>YLX HY>^  IY AY=] @Z &_:Z DY4Y 5a :Y1Y\"Z Z$\\GYG\\ EY9Y IY@X@Y G"
"Z9[ G\\;[ 0Y 5Y.Z DZ@Y ,\\ 3Z 1Z LZ.Z<Z=[)Z(Z*Z;Z<Z/Z LZ'\\  :X  :\\ 7X 7\\0\\ 7X    EZ 0\\FU -Z &x 8YHY (X -YK"
"_   >UDX!T\"X<Y 1XAX     ?T>W>X@U   :] !X $X  <W   6Y1Y GmEW      KV .Y=X ?XAX AW4X BW4W 5W@X \"Y 0Z@Y :Y@Z 9Y@"
"Y :Z@Y 9Y@Z ;Z@Y HZ?Z <[  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z#Z(YEZ<Y*[ M[/[ M[0Z LZ/Z LZ/Z M[ N[?\\ Z3XBZ*Z(Z#Z(Z$Z(Z"
"$Y'Y @ZM[ 9Z3[ KYDY 3P0Z AP0Z BQ0Z AQ0Z BP0Z AP0Z&P0b7Z'\\2P CZ7Z DZ7Z DZ7Z DZ7Z 3Y  Y  NX  Y 0]<Z E^:Z D[9[ C["
":\\ E\\:[ D[9[ C[:\\ 4\\ 3[9[ GY0X HY0X GX0X GX0Y HZ3Y G_:[ GY2Y     <X;X;X*X NX)XJ[A\\JX*X/[JX*X NX ;X 3Z3Z   "
"  >~d&^7U   4~ 9f E~i%~R GY4Y FX.X ;ZNZ 7Y9Y!X                   )~R   \"Z    NW?W BYCT CYBXCX 6_    ?Y  EZ 5ZI"
"VIZ /X        ,X :Z.Y 4Z  C[ )_ :YAZ ?t >YKn %Z 9\\A\\ EZ1\\ 6Z \"[ &j I~d Hi  N\\ W:jLVAW&Z@Z DZ8^ KZ !Z#[\"Z "
" MZ 0Z  KZ(Z :Z \"Z 4ZM] +Z 2YGY?XFY(YEZ=Z*Z L[\"Z4['Z LZ&Z4[ Fc  EY 9Z(Z MZ5Z)Z>XDW=Z Ic .[NZ #\\ -X  KX  CY  "
"      )Z D^8[ D\\ '[8^ FZ5Z 7Y 2[8^ G]8Z 3Y  NX 0X?[ +Y F]9`9Y)^9Z E[8[ F^8Z GZ8^ ;^ .Y  EY .Y1Y GY3Y#Y=WNX=Y M"
"ZAZ AY3Y %[ /Y  X  Y     #gEf N[<YMX HYBb  IY BY;] BZ %^8Z DY5Y 5b ;Y1Y#Z NZ$[FYF[ EY9Y IY@X@Y HZ8[ H\\9[ 1Y 5Y"
".Z DZ@Z ,\\ 4Z 2[ LZ.Z<Z<Z)Z(Z*[<Z<Z/Z LZ(\\  9X  9\\ 8X 8\\.\\ 8X    EZ 1\\EU -Z %^E] EhIg 6X .YI_   ?UEX T!W="
"Z 2YBY     @U>W>W?U   7W <~d BX  ;W   6Y1Y GmEW      KV -X=X ?YBY BW4W AW5X 5W@W !Y 0Y?Z ;Y?Y :Z@Z ;Y?Y :Z?Y ;Y"
"?Y HZ?Z <[  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z#Z(YEZ<Y*[ LZ/[ M[0Z LZ/Z LZ0[ LZ M[A\\ NZ4XAZ*Z(Z#Z(Z$Z(Z$Y'Y @[NZ 8Z3"
"[ KYDY  AZ !Y  Y  Z !Z !Z 5`5Z([ %Z5Z FZ5Z FZ5Z FZ5Z 4Y  Y  NX  Y 1\\:[ F]8Z F[7[ E[8[ E[8[ E[8[ E[8[ 4\\ 4[9\\"
" GY0X HY0X GX0X GX0Y GY4Z G^8Z GZ4Z     <X;X:W+X LX*WH[C\\IX*X0[HW+X LX <X 2Y4Z     =~d(`7T   4~Q 9e E~i%~R GY3"
"Y GX.X ;YMZ 7Z;Z!X                   *~R   !Z    X@X BZDT BXCYDX 6`    ?Y  DY 7[HVH[ 1X        -X 9Z.Y 4Z  D[ 7"
"m 9X@Z ?v AZLp &Z 8^H_ DZ1\\ 6Z \"[ (i F~d Ei #\\ NW;lMV@W'Y>Y D~P JZ !Z#[\"~Q Dy Z  K~] :Z \"Z 4ZN] *Z 2YFX?XF"
"Y(YDZ>Z*Z L[\"Z5\\([ LZ&Z5\\ Eg  JY 9Z(Z MZ5Z)Z>XDX>Z Ib ,f $\\ ,X  KX  CY        (Y D]6Z D[ '[7^ GZ4Z 7Y 2Z6] "
"G]7Z 4Y  NX 0X@[ *Y F]8^8Z*]7Z FZ6[ G]6Z I[7] ;] -X  DY .Y1Y GY3Y#Y=WNX=X L[CZ ?Y4Y &[ .X  NX  Y     $iGh Z:XNX"
" GYHg  HY CY8\\ CY $]7Z DY6Y 4b ;Y1Y#Z MZ&[EYE[ FY9Y IY@X@Y HZ7[ I[7[ 2Y 5~V DY>Y +\\ 5Z 2Z KZ/[<Z<[*Z(Z)Z<Z<Z/"
"ZIuIZ)\\  8X  8\\ 9X 9\\,\\ 9X    EZ 1[DU -Z $Z@[ EhJh 6X /YF_   ATDX U\"X?[ 3ZCZ     @U>W>W?U     K~d CX  ;X  "
" 6Y1Y FlEW      KV -Y?Y ?ZCZ CW5X AW5W 5XAX !Y 0Y>Y <Z?Z ;Y>Y <Z?Z ;Y>Y ;Y?Z JZ>~Q3[  I~Q G~Q F~Q G~Q 5Z !Z !Z "
"\"Z :Z#Z(YDZ=Y*[ LZ/Z L[0Z L[0Z LZ0[ LZ L[C\\ N[5X@Z*Z(Z#Z(Z$Z(Z$Y'Y ?e 7Z3[ KYDY  @Y  Y !Z  Y  Y  Y 4_4Y)[ %Z3"
"Y GZ3Y FZ4Y FZ4Y 4Y  Y  NX  Y 1[8Z F\\7Z F[7[ EZ6[ G[6[ G[6Z EZ6[   <Z9^ HY0X HY0X GX0X GX0Y GY4Y F]6Z GY4Y    "
" ;W:X:X,X LX+XG[E\\GW*W0[GX,X LX <X 2Z5Z     =~d(`8U   4~R 9c D~h%~T HX2Y GX.X <ZLY 6Y;Z!X                   *~"
"R   !Z    X@X BZDT BZGZCW 6b    @Y  DY 8ZFVFZ 2X        -X 9Z.Y 4Z  DZ 7l 8X?Z ?w BZMr ([ 7s C[3] 6Z \"[ +i C~d"
" Cj '\\ NW;nNV@W(Z>Y D~ IZ !Z#[\"~Q Dy![  K~] :Z \"Z 4h )Z 2YFX@YFY(YDZ>Z*Z KZ\"Z5\\([ LZ&Z6\\ Ck  Y 9Z(Z LZ6Z("
"Z?XDX?Z G` *d #[ +X  KX  CY        'Y E]6[ F[ &Z5] GY2Y 7Y 3Z4\\ G\\6Z 4Y  NX 0XA[ )Y F\\7]6Y*\\5Y G[5Z G\\5Z I"
"Z5\\ ;] -X  DY .Y1Y GZ5Z#Y>XMW>Y K[E[ ?Y5Y &[ .Y  NX  Y     $XIZHZIY!Z:XNX GYHf  GY DY6[ CY $\\5Y CX6Y 5c ;Y1Y#"
"Z MZ&[EYDZ FY9Y IY@X@Y IZ5Z IZ5Z 2Y 5~V EZ>Y *[ 5Z 2Z KZ/[<Z<[*Z(Z)Z<Z=[0[IuIZ*\\  7X  7\\ :X :\\*\\ :X      L["
"CU -Z %Z>Z EiKh 6X /XC^   BTDX U\"YA\\ 4ZCZ N~d  &U>W?X>T     K~d EY  :W   5Y1Y EkEW      KV ,YAY =ZCZ DW6X @W6"
"X 5W@W   'Z>Y <Y=Y <Z>Z =Y=Y ;Y>Z =Z>Y JZ>~Q3Z  H~Q G~Q F~Q G~Q 5Z !Z !Z \"Z :Z#[)YDZ=Y*[ LZ/Z KZ0Z L[1[ LZ0[ L"
"Z K[E\\ M[6Y@Z*Z(Z#Z(Z$Z(Z$Y'Y >d 7Z2Z KYDY  @Y  Y  Y  NY  Y !Y 4^3Z*Z $Z3Z HZ3Z HZ3Z HZ2Y 5Y  Y  NX  Y 2[6Z G"
"\\6Y FZ5[ G[5Z GZ5[ GZ5[ G[5Z   =[:_ HY0X HY0X GX0X GX0Y GZ5Y F\\5Z GY5Z     <X:X:X,W JW+XF[G\\FX,X1[FX,W JW <X "
"2Z5Y     <~d'UNY9U   5~T H[LaM[!~g&~V JY1X GX.X <ZLZ 7Y;Y X                    Z    3Z    W?X AZET A\\M\\CX 7d "
"   BZ  DY 8XDVDX 2X        -X 9Z.Y 4Z  E[ 7j 7Y?Z ?x CZNt )Z 5p @Z3] 6Z \"[ .i @~d @i *\\ MW<^Ib@W(Y=Z E| GZ !Z"
"\"Z\"~Q Dy![  K~] :Z \"Z 4f 'Z 2YEXAXEY(YCZ?Z*Z KZ\"Z6\\'[ LZ&Z8] An $Y 9Z(Z LZ7Z'Z?XDX?Z F_ *c #\\ +X  JX  DY "
"       'Y E\\4Z FZ %Z4\\ HZ1Y 8Y 3Z4\\ G[4Y 4Y  NX 0XC\\ (Y F[6]6Y*[4Y GZ4[ H\\4Z JY4\\ ;\\ ,X  DY .Y1Y FY5Y!Y?"
"XMX?Y JZF[ >Z6Y &[ .Y  NX  Y     %WEYJYEX#Z8a GYHe  FY DX4[ DY $\\5Y CY8Z 5d <Y1Y$Z LZ'[DYD[ GY9Y IY@X@Y IY4Z J"
"[5[ 3Y 6~W EY=Z *[ 6Z 2Z KZ/Z;Z<[*Z(Z)Z<Z=Z/[IuI[,\\  6X  6\\ ;X ;\\(\\ ;X      LZBU -Z %Y<Z FjMi 6X 0X@]   CTD"
"W NU!ZE^ 5ZCZ M~d  &T=W@X=T     K~d FY  :X   5Y1Y EkEW 3Z    CV +ZEZ ;ZCZ EW6W ?W7XA]\"XAX   'Y=Z =Y=Y <Y<Y =Y="
"Y <Z=Y =Y=Z KY=~Q3Z  H~Q G~Q F~Q G~Q 5Z !Z !Z \"Z Ew5[)YCZ>Y*Z KZ/Z KZ0Z L[1[ L[1[ LZ J[G\\ L[7Y?Z*Z(Z#Z(Z$Z(Z$"
"Y'Y >c 6Z2Z KYDY  ?Y  X  NX  NY  Y  Y 4\\1Y+[ %Z1Y HY1Y HY1Y HY1Y 5Y  Y  NX  Y 3[5Z G[5Z HZ3Z GZ4[ HZ4Z HZ3Z GZ"
"4[   >Z9` IY0X HY0X GX0X GX0Y FY6Z F\\4Z GY6Y     ;W9X9W-X JX,WD[I\\DW,W1[DW-X JX =X 1Y6Z     <~d'RKY:U   5~U J"
"~T$~g'~X KY1X GX.X <YKZ 7Z<Y W                    NZ    3Y    NW?W @\\GT @jCW 7f    CZ  DY 7VCVCV 1X        .X "
"8Z.Y 4Z  F[ 6h 5X>Z ?y DgF` *Z 2k >Z4^ 6Z \"[ 1j >~d =i -[ LW=\\C_?W)Y<Y Ez EZ !Z\"Z\"~Q Dy![  K~] :Z \"Z 4e &Z"
" 2YEXAXEY(YCZ?Z*Z KZ\"Z8^'[ L['Z:_ @p 'Y 9Z(Z KZ8Z'Z@XBW?Z F^ (b $\\ *X  JX  DY        &X E[2Y FZ &Z3\\ HY0Y 8Y"
" 3Y2[ G[4Y 4Y  NX 0XD\\ 'Y F[5[5Y*[4Y HZ2Z H[3Z KZ3[ ;[ ,Y  DY .Y1Y FY5Y!Y?WLX?Y J[GZ <Y7Z '[ -Y  NX  Z     'WC"
"YKXBV#Z8` FYHc +YCY EY4[ DY $[4Z CX8Y 5e <Y1Y$Z KZ([DYCZ GY9Y IY@X@Y IY3Z KZ3Z 3Y 6~W EY<Y )[ 7Z 2Z KZ/Z;Z;Z*Z("
"Z)[=Z=Z/[IuI[-\\  5X  5\\ <X <\\&\\ <X      LZBU -Z &Y:Y FjNj 6X 0X?]   EUEX NU!s 6ZCZ L~d  &T=WAY=T     K~d GX"
"  9Y   5Y1Y DjEW 3Z    CV *]M] 9ZCZ FW7X5X3W7WCc%XBX5Y   JY<Y >Z=Z =Y<Y >Z=Z =Y<Y >Z=Z LZ=~Q3Z  H~Q G~Q F~Q G~Q"
" 5Z !Z !Z \"Z Ew5[)YCZ>Y*Z KZ/Z KZ0Z KZ1[ L[1Z KZ I[I\\ K[8Y>[+Z(Z#Z(Z$Z(Z$Y'Y =a 5Z2Z KYDY  ?Y  Y  X  MX  Y  Y"
" 4\\1Y+Z $Y0Y IZ1Y IZ1Y IZ0X 5Y  Y  NX  Y 3Z3Y GZ3Y HZ3Z HZ2Z IZ2Z IZ3Z GZ3Z   >Z:a IY0X HY0X GX0X GX0Y FZ7Y E["
"3Z GY6Y     ;W9X9W-W HW,WC[K\\CW,W2[CW-W HW =X 1Z7Z     <~d NX:U   5~V M~X%~e&~Y LX0Y HX.X =ZJY 6Y=Z W         "
"           NZ    3Y    X@X ?]IT ?hCW 7h2X   ;Y  CY 7TAVAT 1X        .X 8Z.Y 4Z  G\\ 6g 5X=Z ?X?a EeB^ +Z /f ;[5"
"^     4i ;~d :i 1[ LW<Z?]?W*Z<Z Fx CZ !Z\"Z\"~Q Dy![  K~] :Z \"Z 4e &Z 2YEXBYEY(YBZ@Z*Z KZ\"Z9^&[ L['[Ad >r *Y "
"9Z(Z KZ8Z'Z@XBX@Y D\\ &` $\\ )X  JX  DY        &X E[2Z HZ %Z3\\ IZ/X 8Y 4Z2[ GZ3Y 4Y  NX 0XE\\ &Y FZ4[5Y*[4Z IZ"
"2Z H[2Y KY2[ ;[ +X  DY .Y1Y FZ7Z!Y?WLX?X H[IZ ;Y7Y '[ ,Y  NX  NY  *Q   NV@WLW?U#Z8` FYHd .^FY EX2[ DX $[3Y CX8Y"
" 5YMY <Y1Y$Z KZ(ZCYCZ GY9Y IY@X@Y JY2Z L[3Z 3Y 6~W FZ<Z )[ 8Z 2Z KZ/Z;Z;Z*Z(Z)[=Z>[/[IuI[.\\  4X  4\\ =X =\\$\\"
" =X      MZAU -Z &X8Y G~W 6X 0W<\\   FUEX MT iNW 8[D[ K~d  &T=WE\\<T     K~d HX  NQ<Y   4Y1Y CiEW 3Z    CV )k 7"
"ZC[ HW7W5Y3W8XFh>Q<YAW5Z   KZ<Z ?Y;Y >Z<Z ?Y;Y >Z<Z ?Z<Y LZ=~Q3Z  H~Q G~Q F~Q G~Q 5Z !Z !Z \"Z Ew5[)YBZ?Y*Z KZ/"
"Z KZ0Z KZ1[ L[1Z KZ H[K\\ J[8X=[+Z(Z#Z(Z$Z(Z$Y'Y <` 5Z2Z KYDZ  ?X  Y  Y  NX  NX  NX 4[/Y,Z $Y/Y JY/Y JY/Y JY/Y "
"6Y  Y  NX  Y 3Z3Z HZ3Y IZ1Z IZ2Z IZ2Z JZ1Z IZ2Z   ?Z:b IY0X HY0X GX0X GX0Y EY8Z E[2Y GZ8Z     ;W9X9X.W HW-XB[M"
"\\BW,W3[BX.W HW =X 0Y8Z     ;~d NY;U   6~X!~[%~c&~Z LX0Y HX.X =ZJZ 7Y=Y N~l                  4Z    3Y    X@X ?`L"
"T >eBX<U\"[M\\4Y   ;Y  CZ 7Q?V?Q 0X        .X 8Y-Z 5Z  H\\ 5j 9Y=Z ?T9_ Ec>] ,Z 1j <[7_     7i 8~d 7i 5[ KW=Z="
"\\?W*Y:Y F{ FZ !Z\"Z\"~Q Dy![1j&~] :Z \"Z 4e &Z 2YDXCXDY(YBZ@Z*Z KZ\"Z<a&Z K['} <s ,Y 9Z(Z KZ9Z%ZAXBXAZ E] &_ $"
"\\ (X  JY  EY        &Y F[2Z HZ %Y1[ IY.Y 9Y 4Z1Z GZ3Z 5Y  NX 0XF\\ %Y FZ4Z3Y+Z2Y IZ1Z I[2Z LY1Z ;[ +X  DY .Y1Y "
"EY7Y NX@XKW@Y G[K[ :Y8Y ([ ,Z  NX  NY /[(R   NU?XNW=U%Z7_ EYHg 3bHY FY1Z DX $Z2Y CY:Y 5ZMZ =Y1Y$Z KZ)[CYBY GY9Y"
" IY@X@Y JY1Y LZ1Z 4Y 6~W FY;Z *[ 7Z 2Z KZ/Z;Z;Z*Z(Z(Z=Z>[/[IuI[/\\  3X  3\\ >X >\\\"\\ >X      MZAU -Z 'X6X 5c "
"%X 1X;\\   GUEX MT NgMW 9[D[ J~d  &T=m;T     K~d In 4TA[   4Y1Y BhEW 3Z    DX )i 5[D[ IX9W5Z3W8WFj?TA[BX5Z   KY"
";Z @Z;Z ?Y:Y @Z;Z ?Z;Y ?Y;Z NZ<~Q3Z  H~Q G~Q F~Q G~Q 5Z !Z !Z \"Z Ew5[)YAY?Y*Z KZ/Z KZ1[ KZ1[ L[1Z KZ G[M\\ IZ8"
"X<[+Z(Z#Z(Z$Z(Z$Y'Y <_ 4Z2Z KYD[  @X  NX  Y  NY  X  NX 3Z/Y-Z $Z/Y KZ/Y KZ/Y KZ/Y 6Y  Y  NX  Y 4Z2Z HZ3Y IZ1Z I"
"Z1Z JY1Z JZ1Z IZ1Z   @Z;XNZ JY0X HY0X GX0X GX0Y EY8Y D[2Z GY8Y     ;X9X8W.W HW-W@hAW-X4[@W.W:[:W =X 0Z9Z      I"
"[ 7Y<U   6~Y\"~^'~c'~\\ MX/X HX.X =YIZ 7Z>Y ~m                  4Z    3Y    W?X >g =cAW?]'[K\\5Y   ;Y  CZ %V  M"
"X        /X 7Y-Z 5Z  H[ 4l ;X<Z ?Q4^ Fb<] .[ 3o ?[7_     :i    5j 9[ JW=Y;[?W+Z:Y F~ IZ !Z\"Z\"~Q Dy![2l'~] :Z "
"\"Z 4f 'Z 2YDXCXDY(YAZAZ*Z KZ\"~%Z K['| 9s .Y 9Z(Z JZ:Z%ZAXBXAZ E] %] #[ 'X  IX  EY        &Y FZ0Y HY %Z1[ IY.Y"
" 9Y 4Y0Z GZ2Y 5Y  NX 0XG[ #Y FZ4Z3Y+Z2Y JZ0Z IZ0Y MZ1Z ;Z *Y  EY .Y1Y EY8Z NYAXKXAY FZL[ 9Y9Y ([ +Y  MX  NZ 4b,"
"S   U=`=U%Z6^ EYHi 6dIY FY1Z DY %Z2Y BX:Y 5ZLY =Y1Y%[ KZ)ZBYBZ HY9Y IY@X@Y JY1Z MZ1Z 4Y 6~W GZ:Y +\\ 7Z 2Z KZ/Z"
";Z;Z*Z(Z([>Z>Z.[IuI[0\\  2X  2\\ ?X ?\\ \\ ?X      MY@U 8y ;X6X 4a $X 1X9[   HUEX MT MeLW :[D[ I~d  &T=l:T     "
"K~d Io 5m   3Y1Y AgEW 3Z    Nl 2g 3[D[%lDX5Z>mDXFk@mAW5[   LZ:Y @Y:Z ?Y:Y @Z:Y ?Y:Z AZ:Y NZ<~Q3Z  H~Q G~Q F~Q G"
"~Q 5Z !Z !Z \"Z Ew5[)YAZ@Y*Z KZ/Z KZ1[ KZ1[ L[1Z K[ Gh HZ9X;[+Z(Z#Z(Z$Z(Z$Y'Y ;] 3Z2Z KYC[  AX  NX  Y  NY  Y  X"
" 3Y.Y-Z $Y.Y KY.Y KY.Y KY.Y 6Y  Y  NX  Y 4Z1Y HY2Y IZ1Z IY0Z KZ0Z KZ1Z IY0Z   @Y;XMZ JY0X HY0X GX0X GX0Y DY9Y D"
"Z0Y GY9Z     ;W8X8W.W HW-W?f?W.W4[?W.W:[:W =X 0Z9Y      HZ 5X<U   6~Z$~`'~a&~\\ NY/X HX.X =YHY 7Z?Z ~m         "
"         4Z    3Y    W?W <i >_@XAa*[I\\6Y   ;Y  CZ %V  MX        /X 7Y-Z 5Z  I[ 3n >X;Z  ] G`9\\ .Z 4s @[9`    "
" =i    /i ;Z IV=Y9Z>V+Z:Z G~P JZ !Z\"Z\"~Q Dy!Z1l'~] :Z \"Z 4g (Z 2YDYEXCY(YAZAZ*Z KZ\"}$Z K['z 5r /Y 9Z(Z JZ;Z"
"$ZAW@WAZ F_ %\\ $[ &X  IX  EY        &Y FZ0Y IZ %Y/Z IY.Y 9Y 4Y0Z GY1Y 5Y  NX 0XH[ \"Y FY3Z3Y+Z2Y JZ0Z IZ0Y MY0"
"Z ;Z *Z  FY .Y1Y DY9Y MYAWJXAY F[MZ 8Z:Y )[ +Z  MX  N[ 7g1U   U<^;U&Z6^ EYHj 9gJY FX/Y CY &Z2Y BY<Z 6ZKZ >Y1Y%Z"
" J[*ZBYBZ HY9Y IY@X@Y KY0Z MY/Y 4Y 6~W GZ:Z ,[ 6Z 2Z KZ/Z;Z;Z*Z(Z([>Z?[.ZHuI[1\\  1X  1\\ @X @\\ M\\ @X      NZ"
"@U 8y ;W4X 5` #X 1X8Z   HUEX MT LbJW ;ZC[ H~d  &T=j8U     L~d Io 5l   2Y1Y @fEW 3Z    Nl 0c 0[CZ&lDW5[>mEXE\\N^"
"AlAX6\\   LZ:Z AY9Y @Z:Z AY9Y @Z:Z AY9Z!Z;~Q3Z  H~Q G~Q F~Q G~Q 5Z !Z !Z \"Z Ew5[)Y@ZAY*Z KZ/Z KZ1[ KZ1[ L[1Z K"
"[ Ff GZ:X:[+Z(Z#Z(Z$Z(Z$Y'Y :\\ 3Z2Z KYC\\  BY  X  NX  NY  Y  X 3Y-X-Y #Y-X KY-X KY-X KY-X 6Y  Y  NX  Y 5Z0Y HY"
"2Y IY/Y JZ0Z KZ0Z KY/Z KZ/Y   AZ;WKY JY0X HY0X GX0X GX0Y DY:Z DZ0Y FY:Y     :WK~KW.WK}KW-W>d>W.W5[>W.W:[:W =X /"
"Y:Z      IZ 4Y=T   6~[%~b'~_%~\\ NY/X HX.X >ZHY 6Y?Y N~m                  4Z    3Y   !X@X ;l @[>WBe,ZG\\7Y   ;Y"
"  CZ %V ;~c        LX 7Y-Z 5Z  J\\ 2n @Y;Z  N\\ G`8\\ /Z 5u A\\<b     ?i    *i ?Z IW=X8Z>V+Y8Y G~R LZ !Z\"Z\"~Q"
" Dy![2l'~] :Z \"Z 4h )Z 2YCXEXCY(Y@ZBZ*Z KZ\"|#Z K['x 0q 1Y 9Z(Z IZ<Z$ZBX@XBY F` %[ $\\ &X  IX  EY        &Y FZ"
"0Z JZ %Y/Z JY,X 9Y 5Z0Z GY1Y 5Y  NX 0XI[ !Y FY3Z3Y+Y1Y JZ/Y IZ0Y MY/Y ;Z *[  GY .Y1Y DY9Y MYBXIWBY Dg 7Y;Z *[ +"
"[  MX  M[ :l6W   T:\\:U&Y5] DYHk :hKY GY/Z DZ 'Z2Y BY<Y 5ZKZ >Y1Y%Z IZ*YAYBZ HY9Y IY@X@Y KY/Y MY/Y 4Y 6~W GY9Z "
"-[ 5Z 2[ LZ/Z;Z;Z*Z(Z'[?Z?[.[IuI[2~n BX B~n AX A~m AX      NZ@U 8y <X4X 4_ #X 1X7Z   IUEX MT J^HW <ZCZ F~d  &T="
"g5T     -X ,o 5k   1Y1Y >dEW 3Z    Nl ._ ,ZCZ'lEX6\\>mEWDVCZBkAX6]   LY8Y BZ9Z AY8Y BZ9Z AY8Y BZ9Z!Z;~Q3Z  H~Q "
"G~Q F~Q G~Q 5Z !Z !Z \"Z Ew5[)Y@ZAY*Z KZ/Z KZ1[ KZ1[ L[1Z KZ Ee FZ;Y:[+Z(Z#Z(Z$Z(Z$Y'Y :[ 2Z2Z KYB\\  CY  X  NX"
"  NY  Y  Y 4Y-Y.Y #Y-X KY-X KY-Y LY-Y 7Y  Y  NX  Y 5Z0Z IY2Y JZ/Z KZ/Y KY/Z KY/Z KZ/Y#~d$Z<WJY JY0X HY0X GX0X G"
"X0Y DZ;Y CZ0Y FY:Y     :WK~KW/WJ}JW.W=b=W.W6[=W/W9[9W >X /Z;Z      JZ 2X>U   6~\\'~c&~^$~Z MY/X HX.X >YGZ 7Z@Y "
"N~m                  4Z    3Y   !X@X :n 'WBg.ZE\\8X   :Y  CZ %V <~e        NX 6Y-Y 4Z  K\\ #a AX:Z  M\\ H_6[ 0Z"
" 6aI` A]?c     ?f    $f ?Z IW>Y7Y>V,Z8Z HZ8` MZ !Z\"Z\"Z  MZ 1[2l'Z(Z :Z \"Z 4ZN] *Z 2YCXFYCY(Y@ZBZ*Z KZ\"{\"Z "
"K['v +o 2Y 9Z(Z IZ<Z#YBX@XCZ Fa %Z %\\ %X  HX  FY        6i FZ0Z JZ %Y/Z JY,X 9Y 5Z/Y GY1Y 5Y  NX 0XK\\  Y FY3Z"
"3Y+Y1Y JY.Y IY/Z NY/Y ;Z *\\  HY .Y1Y DZ;Z LXBXIWBY Ce 6Y;Y )[ -\\  LX  L\\ >q:X  !U:[9U&Y5] DY?d =jLX FY/Z C[ "
")Y1Y AX=Z 6ZIY >Y1Y%Z IZ*YAYAY HY9Y IY@X@Y KY/Y NZ/Z 5Y 5Y-Y HZ8Y .[ 4Z 1Z LZ/Z;Z;Z*Z(Z'[?Z@[-[ L[3~o BX B~o BX"
" B~o BX      NZ@U 8y <X4X 4^ \"X 1X6Y   IUEX MT GW *ZCZ E~d  &T=g5T     -X ,o 5i   /Y1Y <bEW 3Z    Nl *W 'ZCZ(l",
"EW6]>mFXDS?YBi?W5] CY 4Z8Y BY7Y BZ8Z CY7Y AY8Z CZ8Y!Y:Z <Z  HZ !Z  Z !Z  >Z !Z !Z \"Z Ew5[)Y?ZBY*Z KZ/Z KZ1[ KZ"
"1[ L[1Z KZ Dc E[=Y9[+Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z2Z KYB^ &i 0i 1i /i 0i 0i Ej-Y/Z $Z-Y MZ-Y MZ-Y LY-Y 7Y  Y  NX  Y 5Y/"
"Z IY1X JZ/Z KZ/Z LY.Y LZ/Z KZ/Z$~d$Z=WIZ KY0X HY0X GX0X GX0Y CY<Z CY/Z GZ<Z     :WK~KW/WJ}JW.W<`<W.W7[<W/W9[9W "
">X .Y;Y      JZ 1Y?U   6~\\(~e'~]\"~X LX.X HX.X >YFY 7ZAZ N~m                  4Z    3Y   !W?X 9p +XCi0ZC\\9X  "
" :Y  CZ %V <~e        NX 6Z.Y 4Z  L\\  M^ CY:Z  L[ H^4Z 0Z 7^A^ C_Ce     ?c     Mc @Z HW>X6Y>V,Y7Z HZ5^ NZ !Z\""
"Z\"Z  MZ 1[2l'Z(Z :Z \"Z 4ZM] +Z 2YBXGXBY(Y?ZCZ*Z KZ\"z![ LZ&w 'k 3Y 9Z(Z IZ=Z\"ZCX@XCZ Gc &Z &\\ $X  HX  FY   "
"     >q FY.Y JY $Y/Z JY,X 9Y 5Y.Y GY1Y 5Y  NX 0XL\\  NY FY3Z3Y+Y1Y JY.Z JY/Z NY/Y ;Y (^  KY .Y1Y CY;Y KYCXIXCY "
"Bc 4Y<Y *[ 2a  KX  La Du?Z  !U9Z8T'Z5] DY9^ >\\IYMX FY/Z B\\ +Y1Y AY>Y 5ZIZ ?Y1Y%Z IZ*YAYAY HY9Y IY@X@Y KY/Y NZ"
"/Z 5Y 5Y-Y HZ8Z 0\\ 4Z 1Z LZ/Z;Z;Z*Z(Z&[@Z@[-[ L[4~p BX B~o BX B~p CX      NY?U 8y <W2W 3] \"X 1Y7Y   IUEX MT  "
" JZCZ  8X  &T=WIZ6T     -X ,o 3e   -Y1Y :`EW 3Z    Nl   (ZCZ)lFW5UNV>mFWCQ;XAe>X6UNW CY 4Y7Z DZ7Y BZ8Z CY7Z CZ7"
"Y CY7Z#Z:Z <Z  HZ !Z  Z !Z  >Z !Z !Z \"Z :Z#[)Y?ZBY*Z KZ/Z KZ0Z KZ1[ L[1Z KZ Ca D[>Y8[+Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z3[ "
"KYA^ /q 9r 9q 7q 8q 9r Mq,Y/Z $Y,Y MY,Y MY,Y MZ-Y 7Y  Y  NX  Y 5Y.Y IY1X JZ/Z KY.Z LY.Y LZ/Z KY.Z$~d$Y=XIZ KY0X"
" HY0X GX0X GX0Y CY<Y BY/Z FY<Y     9WK~KW/WJ}JW.W;^;W.W8[;W/W9[9W >X .Y<Z      K[ 1Y@U   6~](~f'~[ ~V KX.Y IX.X"
" ?ZFY 6YAZ N~m                  4Z    3Y   !W?W 6p -WCk1ZB\\;Y   :Y  CZ %V <~e        NX 6Z.Y 4Z  M\\  J] EY9Z "
" L[ H^4[ 2[ 8\\<\\ BbKi     ?`     Ha @Z HV=X5X>W-Y6Y HZ2\\ Z !Z\"Z\"Z  MZ 1[2l'Z(Z :Z \"Z 4ZL] ,Z 2YBXGXBY(Y?Z"
"CZ*Z KZ\"x N[ LZ&x #f 3Y 9Z(Z HZ>Z\"ZCW>WCZ Hd &Z &[ #X  HX  FY        At FY.Y JY $Y/Z JY,Y :Y 5Y.Y GY1Y 5Y  NX"
" 0XM\\  MY FY3Y2Y+Y1Y JY.Z JY.Y Z/Y ;Y (b  Y .Y1Y CY;Y KYCWHXCY Bb 3Y=Y *[ 6e  JX  Ke KzF^  !U9Y7T'Z4[ CY7] @[E"
"XNX GZ.Y Ai 9Y1Y AY>Y 5YHZ ?Y1Y&[ IZ+ZAYAY HY9Y IY@X@Y KY/Y NZ.Y 5Y 5Y-Y IZ6Y 0[ 3Z 1Z LZ/Z;Z;Z*Z(Z&\\AZA[,[ L["
"4~p BX B~o BX C~q CX      NY?U 8y <W2W 3\\   )Y6Y   JUEX NU   KZCZ  7X  &T=WGY7T     -X    J^   *Y1Y 7]EW 3Z   "
"     8ZCZ 4X6UMV GX-X=^;W6UMW CY 4Y6Y DZ7Z CY6Y DZ7Z CY6Y DZ7Z#Z:Z <Z  HZ !Z  Z !Z  >Z !Z !Z \"Z :Z#[)Y>ZCY*Z K"
"Z/Z KZ0Z L[1[ L[1Z KZ B_ C[>X7[+Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z3[ KY@_ 5u <u <t :t <u <u!t,Y/Y #Y,Y MY,Y MY,Y MY,Y 7Y  Y "
" NX  Y 6Z.Y IX0X JY-Y KY.Z MZ.Y LZ.Y KY.Z$~d$Y>XHZ KY0X HY0X GX0X GX0Y BY=Y BY.Y FY=Z     9WK~KW/WJ}JW.W:\\:W.W"
"9[:W/W9[9W >X .Z=Y      JZ /X@U   6~^*~g&~Y N~V KX.Y IX.X ?ZFZ 7ZBY L~l                  4Z    3Y   \"X@X 3n /X"
"CZIZ2Z@\\<Y   :Y  BY %V <~e        Y 6Z.Y 4Z  N\\  G\\ FX8Z  K[ I]2Z 2Z 8\\9[ BsNZ     ?]     B^ @Y GV=W4X>W.Z6"
"Z IZ1[ Z !Z#[\"Z  MZ 1[2l'Z(Z :Z \"Z 4ZK] -Z 2YBXHYBY(Y>ZDZ*Z KZ\"v L[ LZ&z !c 4Y 9Z(Z HZ>Z\"ZDX>XDY Ge 'Z '[ "
"\"X  GX  GY        Dw FY.Y JY %Z/Z J~W :Y 5Y.Y GY1Y 5Y  NX 0XN\\  LY FY3Y2Y+Y1Y JY.Z JY.Y Z/Y ;Y 'e $Y .Y1Y CZ=Z"
" KYDXGWDY @a 3Z>Y +[ 5d  IX  Ic L~d  !U8X7T'Z4[ CY5\\ AZCa GY-Y @h 9Y1Y @X?Z 6ZGY ?Y1Y&[9X9Z+ZAYAZ IY9Y IY@X@Y "
"KY/Z Y-Y 5Y 5Y.Z IZ6Z 2[ 2Z 1Z M[/Z;Z<[*Z(Z%[AZB\\,[ LZ3~p BX B~o BX C~q CX      NY?U 8y <W2W 2[   (Y7Y   ITDW "
"NU   M[CZ  6X  &T=WFY8T     -X        EY1Y 1WEW 3Z        7ZC[ 6W6ULV HX+W JX7ULW CY 5Z6Z EY5Y DZ6Z EY5Y DZ6Z E"
"Z6Y$Z9Z <Z  HZ !Z  Z !Z  >Z !Z !Z \"Z :Z#[)Y>ZCY*Z KZ/Z KZ0Z L[1[ L[1[ LZ A] B[?X6Z*Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z3[ KY?"
"_ 8w ?x ?w =w >w >w$~u/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Z.Y IX0X JY-Y KY.Z MZ.Z MY-Y KY-Y$~d$Y?XFY KY0X HY0X GX0"
"X GX0Y BY>Z BY.Y EY>Y     8WK~KW/WJ}JW.W;]:W.W:[9W/W9[9W >X -Y>Z      KZ .YAU   6~^*~g%~W L~T JX.Y IX.X ?YEZ 7Z"
"CZ L~k                  :y    KY   \"X@X 0m 1WCYEY3Y>\\=X   9Y  BY %V <~e   =l    X 5Z.Y 4Z  \\  E[ GY8Z  JZ I]"
"2Z 2Z 8[7[ BqMZ     ?^     C^ @Y GV=W4X>V-Y5Z IZ0[!Z !Z#[\"Z  MZ 1[2l'Z(Z :Z \"Z 4ZJ] .Z 2YAXIXAY(Y=YDZ*Z L[\"s"
" I[ LZ&[Cc  Na 5Y 9Z(Z HZ?Z YDX>XEZ Hg (Z (\\ \"X  GX  GY        Fy FY.Y KZ %Z/Z J~W :Y 5Y.Y GY1Y 5Y  NX 0e  KY"
" FY3Y2Y+Y1Y KZ.Z JY.Y Y.Y ;Y &h (Y .Y1Y BY=Y IXDXGWDY ?_ 1Y?Z ,[ 4b  GX  Ga L~c   T6V6T'Z4[ CY4\\ CZ@_ GY-Y >f "
"9Y1Y @Y@Y 5YFZ @Y1Y&Z8X9[,ZAYAZ IY9Y IY@X@Y KX.Z Y-Y 5Y 5Y.Z IY5Z 3[ 1Z 1Z M[/[<Z<[*Z(Z%\\BZC\\+[ LZ3~p BX B~o "
"BX C~q CX    DX 4Z?U -Z (W2W 2Z   'Z7X   ITDX U   MZCZ  5X  &U>WEY9T     -X        EY1Y 1WEW 3Z        6ZCZ 7X7"
"UKV HW*W KX6ULW CY 5Y5Z FZ5Z EY4Y FZ5Z EZ5Y EY5Z%Z9Z <Z  HZ !Z  Z !Z  >Z !Z !Z \"Z :Z#Z(Y=ZDY*[ LZ/Z KZ0Z L[0Z "
"LZ0[ LZ A] B[@X5Z*Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z4[ JY>` <y @y Ay ?y @y @y%~v/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Z.Y IX0X JY"
"-Y KY-Y MZ.Z MY-Y KY-Y$~d$Y?WEY KY0X HY0X GX0X GX0Y BZ?Y AY.Y EY>Y     8WK~KW/WJ}JW.W<_;W.W;[8W/W9[9W >X -Z?Z  "
"    LZ -YBU   5~^*~h%~U J~R IX.Y IX.X @ZDY 6YCZ LW                   'y    JY   \"W?X ,j 3WCYCY4Y=\\>X   9Y  CZ"
" %V <~e   =l    X 5Z.Y 4Z !\\  C[ IY7Z  JZ I]2Z 3[ 9[5[ BoLZ     ?a     Ia @Y HW>X3W>V.Z4Y IZ/Z!Z !Z#[\"Z  MZ 0"
"Z Z'Z(Z :Z \"Z 4ZI] /Z 2YAXIXAY(Y=ZEZ*Z L[\"o DZ LZ&Z<^  M_ 5Y 9Z(Z GZ@Z ZEX>XEZ I[MZ (Z )\\ !X  GX  GY        "
"Gz FY.Y KZ %Y-Y J~W :Y 5Y.Y GY1Y 5Y  NX 0c  IY FY3Y2Y+Y1Y KZ.Z JY.Y Y.Y ;Y %j +Y .Y1Y BY=Y IYEXGXEY >] 0Y?Y ,[ "
"3`  EX  E_ L\\Cx   NT6V6T'Z4Z BY2Z CY>^ GY-Y ;c 9Y1Y @YAZ 6ZEY @Y1Y&Z8X9[,ZAYAZ IY9Y IY@X@Y KX.Z Y-Y 5Y 5Y.Z JZ"
"4Y 4\\ 1Z 1[ NZ.[<Z<Z)Z(Z$\\CZD]*Z LZ3~p BX B~o BX C~q CX    DX 4Z?U -Z (W2W 2Z   'Z7X   ITDX U   MYBY  4X  &U>"
"WDX:U     -X        EY1Y 1WEW 3Z        5YBY 7W6UKV IX*W KW6UKW CY 6Z4Y FZ5Z FZ4Z GZ4Y EY4Z GZ4Y%Y8Z <[  IZ !Z "
" Z !Z  >Z !Z !Z \"Z :Z#Z(Y=ZDY*[ LZ/Z L[0Z L[0Z LZ0[ LZ B_ BZAY5Z*Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z5\\ JY=` ?{ B{ Bz @z B{ "
"B{'~x/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Z.Y IX0X JY-Y LZ-Y MZ.Z MY-Y KY-Y$~d$Y@WDY KY0X HY0X GX0X GX0Y AY@Z AY.Y "
"DY@Z     8WK~KW/WJ}JW.W=a<W.W<[7W/W9[9W >X ,Y?Y      LZ +XBU   6~_+~i%~U I~P HX.Y IX.X @ZDZ 7YCY KX            "
"       (y    JY   \"W?W (h 5XCXAX5Z<\\@Y   9Y  CZ $T ;~e   =l    X 5Z/Z 4Z \"\\  AZ IX6Z  JZ I\\1[ 4Z 8Z3Z AmKZ"
"     ?d     d AZ HW>X3W>V.Z4Z JZ.Z\"[ \"Z#[\"Z  MZ 0Z Z'Z(Z :Z \"Z 4ZH] 0Z 2YAYKX@Y(Y<ZFZ*[ M[\"Z /Z LZ&Z:\\  K"
"^ 6Y 9Z(Z GZAZ NZEW<WEZ IZL[ )Z *\\  X  FX  HY        H{ FY.Y KZ %Y-Y K~X :Y 5Y.Y GY1Y 5Y  NX 0c  IY FY3Y2Y+Y1Y"
" KZ-Y JY.Y Y-X ;Y $l .Y .Y1Y AY?Y HYEWFXEX =\\ .Y@Y -[ 2b  GX  Ga LY=s   LT6W7T'Z4Z BY2Z DY=^ GY-Z =d 9Y1Y ?XAY"
" 5YDZ AY1Y&Z8X9[,ZAYAZ IY9Y IY@X@Y KX.Z Y-Y 5Y 5Y.Z JZ4Z 5[ 0Z 0Z NZ-Z<Z<Z)Z(Z#\\DZD\\)Z LZ3~p BX B~o BX B~p CX"
"    DX 4Z?U -Z (W2W 2Z   &[9X   IUEX T s AXAY  4X  &U>WCX;U     -X        EY1Y 1WEW 3Z      Is 0YAX 8W6UJV IW)W"
" LX7UJW CY 6Z4Z GY3Y FZ4Z GY3Y FZ4Z GY3Z'Z8Z <[  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z#Z(Y<ZEY*[ M[/[ M[0Z LZ/Z LZ/Z LZ "
"Ca CZBY4Z*Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z5\\ JY<` A| C| C{ A{ C| C|(~y/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Y-Z JX0X JY-Y LZ-Y"
" MZ.Z MY-Y KY-Y$~d$YAWCY KY0X HY0X GX0X GX0Y AY@Y @Y.Y DY@Y     7WK~KW/XK}KX.W>c=W.W=[6W/X:[:X >X ,Y@Z      M[ "
"+YCT   5~`,~i$~S H~P HX.Y IX.X @YCZ 7ZDY KX                   )y    HX   #X@X (TNc 6WCX@X5Y:\\AX   8Y  CZ   :~e"
"   =l   !X 4Z/Z 4Z #\\  @[ KY6Z  IZ I[0Z 4Z 9Z2[ @jJZ     ?f    %g AZ HW>X3W>V.Y2Y JZ.Z\"[ \"Z#Z!Z  MZ 0Z Z'Z(Z"
" :Z \"Z 4ZG] 1Z 2Y@XKX@Y(Y<ZFZ*[ MZ!Z /Z LZ&Z8[  K] 6Y 9Z(Z FZBZ NZFX<XFY I[KZ )Z +\\  NX  FX  HY        I| FY."
"Y KZ %Y-Y K~X :Y 5Y.Y GY1Y 5Y  NX 0d  JY FY3Y2Y+Y1Y KZ-Y JY.Y Y-X ;Y #m 0Y .Y1Y AY?Y HYFXEWFY =\\ .YAY ,[ 2d  I"
"X  Ic LW8n   JU7W7T'Y2Y BY1Z EY<\\ FY-Z @g 9Y1Y ?YBY 6ZDZ AY1Y&Z8X8Z,Y@YAZ IY9Y IY@X@Y LY-Y Y-Y 5Y 5Y.Z JY3Z 6["
" /Z 0Z [-[=Z=[)Z(Z#]EZE\\(Z LZ2~o BX B~n AX A~n BX    DX 4Z?U -Z (X4X H~W   <\\:W   HUDX!T s AZCZ  5X  %T>WBX<U"
"     -X        EY1Y 1WEW       \"s 1ZCZ 9X7UIV JX)W LW7UIW CY 6Y2Y HZ3Z GY2Y HZ3Z GY2Y HZ3Z'Z8Z <[  IZ !Z  Z !Z"
"  >Z !Z !Z \"Z :Z#Z(Y<ZEY)Z M[/[ M[0[ MZ/Z LZ/Z M[ Dc DZCY3Z*Z(Z#Z(Z$Z(Z$Y'Y 9Z 2Z6\\ IY:` D} D} D| B| D} D})~z"
"/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Y-Z JX0X JY-Y LZ-Y MY-Z MY-Y LZ-Y$~d%ZBXCY KY0X HY0X GX0X GX0Y @YAY @Y.Y DYAZ "
"    7W8X8W.W HW-W?e>W.W>[5W.W:[:W =W +ZAY      LZ *YDU   5~`,~i#~Q F} GX.Y IX.X AZBY 7ZEZ KX                   "
")y    HX   6~e 9TJ_ 7XCX?X6Y9\\BX   8Y  CZ    KX    Nl   !X 4Z/Z 4Z $\\  >Z LY5Z  IZ I[0Z 5Z 8Z1Z >fHY     =h  "
"  +i @Z HW>X3W?W/Z2Z KZ.[#[ \"Z#Z!Z  MZ 0Z Z'Z(Z :Z \"Z 4ZF] 2Z 2Y@XLY@Y(Y;ZGZ*[ MZ!Z /Z M[&Z7[  K\\ 6Y 9Z(Z FZ"
"BZ MYFX<XGZ J[IZ *Z +[  MX  FX  HY        Jb>Y FY.Y KZ %Y-Y K~X :Y 5Y.Y GY1Y 5Y  NX 0e  KY FY3Y2Y+Y1Y KZ-Y JY.Y"
" Y-X ;Y !m 2Y .Y1Y AZAZ GYGXEXGY >] .ZBY -[ 1e  JX  Ke LU4k   IU8Y8T'Y2X AY0Y EX:[ FY-Z Ah 9Y1Y >XCZ 6YBY AY1Y&"
"Z8X8Z,Y@YAZ IY9Y IY@X@Y LY-Y Y-Y 5Y 5Z/Y JZ2Z 8[ .Z 0[!Z,[=Z=[)Z(Z\"]FZG]'Z M[1]  1X  1\\ @X @\\ L\\ AX    DX 4"
"Z?U -Z (X4X H~W   ;\\;W   GTDX\"U s A[D[  6X  %T>WBX<T     ,X        EY1Y 1WEW       \"s 2[D[ 9W7UHV KX(W MX7UI"
"W CY 7Z2Z IZ3Z HZ2Z IZ3Z HZ2Z IZ3Z(Z7Z ;Z  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z$[(Y;ZFY)Z M[/[ MZ/[ MZ/Z M[/Z M[ Ee EZC"
"X3[*Z(Z#Z(Z$Z(Z$Y(Z 9Z 2Z8^ IY9` Fb=Y Eb=Y Eb=X Cb>Y Eb=Y Eb=Y*b=~V/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Y-Z JX0X JY"
"-Y LZ-Y MY-Z MY-Y LZ-Y   CZCXBY KY0X HY0X GX0X GX0Y @YBZ @Y.Y CYBY     6W8X8W.W HW-W@g@X.W?[4W.W:[:W =W *YBZ   "
"   MZ (XDU   5~`,~i\"~ D{ FX.Y IX.X AZBZ 7YEY IX                   +y    GX   6~e 9TG] 8WBW>X6Y8\\DY   8Y  CZ  "
"  KX    Nl   !X 4Z/Z 4Z %\\  =Z LX4Z  IZ I[0Z 5Z 9Z0Z <bFY     ;i    1i =Z HW>X3W?W/~S KZ-Z\"Z \"Z#Z!Z  MZ 0[!Z"
"'Z(Z :Z \"Z 4ZE] 3Z 2Y?XMX?Y(Y;ZGZ)Z MZ!Z /[ N[&Z6[  K\\ 7Y 9Z(Z FZCZ LZGX<XGZ JZH[ +Z ,\\  MX  FY  IY        K"
"]8Y FY.Y KZ %Y-Y K~X :Y 5Y.Y GY1Y 5Y  NX 0f  LY FY3Y2Y+Y1Y KZ-Y JY.Y Y-X ;Y  Mk 3Y .Y1Y @YAY FYGWDXGY >^ .YCZ ."
"[ )_  KX  L_ ES/e   FU8Z9T'Z3X AY0Y FY:[ FY-Z Cj 9Y1Y >XCY 6ZBZ BY1Y&Z8X9[,Y@YAZ IY9Y IY@X@Y LY-Y Y-Y 5Y 5Z/Y J"
"Z2Z 9\\ .Z /Z!Z,\\>Z>[(Z(Z!]GZH^'[ N[0\\  1X  2\\ ?X ?[ M\\ @X    DX 4Z?U -Z 'W4W G~W   :]>X   GTDY#U s @[D[  7"
"X  %U?WAX>U     ,X        EY1Y 1WEW       \"s 3ZC[ 9X7UHV KW(W MX7UHW CY 7~S J~S H~S I~S I~S I~S)} ;Z  IZ !Z  Z"
" !Z  >Z !Z !Z \"Z :Z$[(Y;ZFY)Z MZ-Z MZ/[ N[/[ N[/Z MZ Eg F[EX2[*Z(Z#Z(Z$Z(Z$Y(Z 9Z 2Z9^ HY7_ G]8Y F^8Y F^8X D]8"
"Y E]8Y F^8Y+^8~V/Y #~W M~W M~W M~W 7Y  Y  NX  Y 6Y-Z JX0X JY-Y LZ-Y MY-Z MY-Y LZ-Y   BYDXAY KY0X HY0X GX0X GX0Y"
" @ZCY ?Y.Y CYBY     5W9X8W.W HW-WAiAW,WA[3W.W9Y9W >X *ZCZ     6~d IYET   4~`,~i!| By EX.Y IX.X AYAZ 7ZFY IX    "
"                Z    3X   6~e 9TF\\ 9WBX=W7Z7\\EX   7Y  CZ    KX    Nl   \"X 3Z/Z 4Z &\\  ;Z M~Z %Z I[0Z 6[ 9Z/"
"Y 8ZCZ     8i 6~d 5i ;Z HW>X3W?W0~T KZ-Z\"Z \"Z$[!Z  MZ 0[!Z'Z(Z :Z \"Z 4ZD] 4Z 2Y?XMX?Y(Y:ZHZ)Z N[!Z /[ NZ%Z6["
"  J[ 7Y 9Z(Y DZDZ LZGW:WGZ K[GZ +Z -\\  LX  EX  IY        L\\6Y FY.Y KZ %Y-Y K~W 9Y 5Y.Y GY1Y 5Y  NX 0XM\\  MY "
"FY3Y2Y+Y1Y KZ.Z JY.Y Y-X ;Y  Ji 4Y .Y1Y @YAY FYGWDXGX >` /YCY .[ $\\  LX  M\\ AR+`   CT9[:U'Z3X AY0Y FY9Z FY-Z "
"D` .Y1Y >YEZ 6YAZ BY1Y&Z8X9[,ZAYAZ IY9Y IY@X@Y LY.Z Y-Y 5Y 5Z/Y KZ1Z 9[ -Z /Z\"[+[>Z>[(Z(Z ^IZJ_&[ NZ.\\  2X  3"
"\\ >X >[ \\ ?X    DX 4Z?U -Z 'X6X G~W   9^@X   GUDY$T Ns ?[CZ  8X  %U?WAY?U     ,X        EY1Y 1WEW       \"s 4"
"ZCZ 7W7UGV LX)X MW7UGW CY 8~T J~T I~S J~T I~T K~T*~ ;Z  IZ !Z  Z !Z  >Z !Z !Z \"Z :Z$[(Y:ZGY)[ NZ-Z N[.Z N[/[ N"
"[/[ NZ Fi G[FX1Z)Z(Z#Z(Z$Z(Z$Z)Z 9Z 2Z<a HY5^ I[5Y F[5Y G\\5X E\\6Y F\\6Y F[5Y+[5~V/Y #~V L~V L~W M~W 7Y  Y  NX"
"  Y 6Y-Z JX0X JY-Y LZ-Y MZ.Z MY-Y KY-Y   BYDW@Y KY0X HY0X GX0X GX0Y ?YDZ ?Y.Y BYDY     4W9X9X.W HW-XC\\L[BW,WB["
"3X.W HW >X )YCY     5~d IYFU   4~`,~i!{ @x EX.Y IX.X AY@Y 7ZGZ IX                    Z    3X   6~e 9TD[ ;XBX=X8"
"Z6\\GY   7Y  CY    JX    Nl   \"X 2Y/Z 4Z '\\  :Z M~Z %Z I[0Z 6Z 8Z/Z \"Z     5i 9~d 8i 8Z HW>X3W?W0~U LZ-Z\"[ "
"#Z$[!Z  MZ /Z!Z'Z(Z :Z \"Z 4ZC] 5Z 2Y?XNY?Y(Y:ZHZ)[ [!Z .Z NZ%Z5[  K[ 7Y 9Z(Y DZDY KZHX:XHY K[EZ ,Z .\\  KX  EX"
"  IY        LZ4Y FY.Y KZ %Z.Y KZ  <Y 5Y.Y GY1Y 5Y  NX 0XL\\  NY FY3Y2Y+Y1Y KZ.Z JY.Y Y.Y ;Y  Ff 5Y .Y1Y @ZCZ FY"
"HXCWHY ?b /YDY /[ ![  MX  M[ @Q%W   ?T9\\;U'Z3X AY0Z GX8Z FY-Z E\\ )Y1Y =XEY 6Z@Y BY1Y&Z9Y9[,ZAYAZ IY9Y IY@X@Y "
"LY.Z Y-Y 5Y 4Y/Y KZ0Z ;[ ,Z /[#Z*\\?Z?\\(Z(Z N`LZL`$Z NZ-\\  3X  4\\ JPCXCP J[\"\\ >X    DX 4Z?U -Z 'X6X G~W   "
"8^BX   FUDY%U Ns =ZCZ  9X  $U@W@X?T     +X        EY1Y 1WEW       \"s 5ZCZ 7W7UFV LW(W MX8UFW CY 8~U K~T J~U K~"
"T J~U K~T*~ ;[  JZ !Z  Z !Z  >Z !Z !Z \"Z :Z$Z'Y9YGY)[ [-[ [.Z N[.Z NZ.[ NZ G\\L[ GZGX0Z)Z(Z#Z(Z$Z(Y#Z)Z 9Z 2~ "
"GY4] J[4Y G[4Y G[4X EZ4Y FZ4Y G[4Y,[4X 1Y #Y  Y  Y  Y  9Y  Y  NX  Y 6Y-Z JX0X JY-Y LZ-Y MZ.Z MY-Y KY-Y   BYEW?Y"
" KY0X HY0X GX0X GX0Y ?YDY >Y.Y BYDY     4W9X9W-X JX,WD\\J[CW,WC[2W-X JX >X )YDZ     5~d HXFU   4~_+~i z @w DX.Y"
" IX.X BZ@Y 6YGZ IY                    Y        @~e 9TCZ ;WAX=X8Y4\\HX   6Y  CY    JX    Mj   !X 2Y/Y 3Z (\\  9Z"
" M~Z %Z I[0Z 6Z 8Z/Z \"Z     2i <~d ;i 5Z HW>X3W@W/~U LZ-[#[ #Z$Z Z  MZ /Z!Z'Z(Z :Z \"Z 4ZB] 6Z 2Y>a>Y(Y9ZIZ)[ "
"Z Z .Z [%Z4Z  JZ 7Y 9Z)Z DZEZ JYHX:XIZ KZD[ -Z /\\  JX  EX  IY        MZ3Y FY.Y JY %Z/Z JY  <Y 5Y.Y GY1Y 5Y  NX"
" 0XK\\  Y FY3Y2Y+Y1Y KZ.Z JY.Y Y.Y ;Y  Bc 6Y .Y1Y ?YCY DYIXCXIY @c /YEY /[  NZ  MX  N[     *U;^=U&Z4Y AY/Y HY7X"
" EY-Y E[ 'Y1Y =YFY 6Z@Z CY1Y&Z9Y9Z+ZAYAZ IY9Y IY@X@Y LZ/Z Y-Y 5Y 4Y0Z KZ0Z <[ +Z .Z$[)\\@Z@\\'Z(Z M~Q#Z [,\\  4"
"X  5\\ JRDXDR J[$\\ KQCXDQ   #Y 4Z?U -Z &X8X F~W   7_EY   EUDY&U Ns <ZCZ  :X  $U@W?XAU     +X        EY1Y 1WEW "
"      \"s 6ZCZ 7X8UEV MX)X MW7UFW DZ 8~U L~V K~U L~V K~U K~U+~ :Z  JZ !Z  Z !Z  >Z !Z !Z \"Z :Z%['Y9ZHY(Z [-[ Z"
"-[ Z-Z [-Z [ H\\J[ HZHY1[)Z(Z#Z(Z$Z(Y#Z)Z 9Z 2} FY2\\ KZ3Y GZ3Y GY3Y FZ3Y GZ3Y GZ3Y,Z3X 1Y #Y  Y  Y  Y  9Y  Y  "
"NX  Y 6Y-Z JX0X JY-Y KY.Z MZ.Z MY-Y KY-Y   BYFX?Y KY0X HY0X GX0X GX0Y >YEY >Y.Y BYEZ     4X:X9W,W JW+WE\\H[EX,X"
"E[1W,W JW =X )ZEY     4~d HYHU   2~^+~i Nx >u CX.Y IX.X BY?Z 7ZHY GX                    Z        A~e 9TCZ <XAW<"
"X8Z4\\JY   6Z  DY    JX        4X 1Z0Y 3Z )\\  8Z M~Z %Z I[0Z 7Z 7Z/Z \"Y     /i >~d >i 2Z GV>X3W@W0~V LZ-[\"Z "
"#Z%[ Z  MZ /[\"Z'Z(Z :Z \"Z 4ZA] 7Z 2Y>a>Y(Y9ZIZ(Z Z Z .[![%Z4[  KZ 7Y 9Z)Z CZFZ JZIX:XIZ L[CZ -Z /[  IX  DX  J"
"Y        MY2Y FY.Y JY %Z/Z JY  <Y 5Y.Y GY1Y 5Y  NX 0XJ\\ !Y FY3Y2Y+Y1Y JY.Z JY.Y Z/Y ;Y  ?a 7Y .Y1Y ?YCY DYIWBX"
"IY @d /YFY 0[  LY  MX  NZ     )U<VNW=U&Z4Y AY/Y HY8Y EZ.Y F[ &Y1Y =YGZ 7Z>Y CY1Y&Z9Y9Z+ZAYAY HY9Y IY@X@Y LZ/Y N"
"Y-Y 5Y 4Y0Z LZ.Y =[ *Z .[%Z(]AZA]'Z(Z L~\"[![+\\  5X  6\\ JTEXET J[&\\ KSDXES   $Y 3Y?U -Z &Y:Y F~W   5_GX   DU"
"CZ9QAU   DZCZ  ;X  $VAW?YBU     +X        EY1Y 1WEW          DZCZ 6W7UEV NX)X MX8UEW DY 8~V L~V L~W M~V K~V M~V"
",~P :Z  JZ !Z  Z !Z  >Z !Z !Z \"Z :Z%['Y8ZIY(Z Z+Z Z-[![-[![-[![ I\\H[ I[JY0[(Y(Z#Z(Z$Z)Z#Z)Z 9Z 2| EY1\\ LY2Y "
"HZ2Y HZ3Y FY2Y GY2Y GY2Y-Z2X 1Y #Y  Y  Y  Y  9Y  Y  NX  Y 6Z.Y IX0X JY-Y KY.Z MZ.Z MY-Y KY.Z   BYGX?Z KY1Y HY0X"
" GX0X GX0Y >YFZ >Y.Y AYFY     2W:X:X,W JW+XG\\F[FW+XF[1X,W JW =X (YEY     4~d GXHU   2kNRMk*tNq Mv <s BX.Y IY/X"
" BY>Y 7ZIZ GY                   !Z        A~e 9TBY <W@W;W8Z3\\KX   5Z  DY    JX        4X 1Z1Z 3Z *\\  7Z M~Z %"
"Z HZ0Z 7Z 7Y.Z #Z     ,i A~d Aj 0Z GV=W4X@W0~W MZ-[\"[ $Z%[ Z  MZ /[\"Z'Z(Z :Z \"Z 4Z@] 8Z 2Y>`=Y(Y8ZJZ([\"[ Z "
".[!Z$Z3Z  KZ 7Y 9Z)Z CZGZ IZIW8WIZ M[AZ .Z 0\\  IX  DX  JY        MY2Y FY.Y JY $Y/Z JY  <Y 5Z/Y GY1Y 5Y  NX 0XI"
"\\ \"Y FY3Y2Y+Y1Y JY.Z JY.Y NY/Y ;Y  ;] 7Y .Y1Y >YEY CYIWBXIX @f 0YGZ 0[  LZ  NX  NY     'U>WMW?V&Z4Y AY/Y HY8Y"
" EZ.Y FZ %Y1Y <XGY 6Z>Y CY1Y&[:Z:Z+ZAYAY HY9Y IY@X@Y LZ/Y NZ.Y 5Y 4Y0Y KZ.Z ?\\ *Z -['['\\AZB]&Z(Z K|![!Z)\\  6"
"X  7\\ JVFXFV J[(\\ KUEXFU   %Y 3Y?U -Z %Y<Y /Z    M`KY   BUC[=SAU   CZCZ  <X  #UAW>XCU     *X        EY1Y 1WEW"
"          F[CZ 6X8UDV NW)X MX8UDW DY 8~W N~W L~W M~V L~W M~W-~P :[  KZ !Z  Z !Z  >Z !Z !Z \"Z :Z%['Y8ZIY([\"[+["
"\"[,Z![-[!Z,[!Z I\\F[ J[KY/Z'Z)Z#Z)Z#Z)Z#Z)Z 9Z 2{ DY0[ MY1Y HY1Y HY2Y FY2Y HZ2Y HY1Y-Y2Y 1Z $Y  Y  Y  Z  :Y  Y"
"  NX  Y 6Z.Y IX0X JZ.Y KY.Z MZ.Y LZ.Y KY.Z   BYHX>Z KY1Y HY1Y GX0X GX0Y =YGY =Y.Y AYFY     2X;X:W+X LX*WH\\D[HX"
"*WG[0W+X LX =X (YFZ     4~d GYIU   2jLQLj*pNRNq Lt :q AX.Y IY0Y CZ>Y 6YIZ FX                   !Z        A~e 9T"
"BZ >W?W;W8Z2\\MY   4Y  DY    JX        4X 1Z1Z 3Z +\\  6Z M~Z %Z HZ0Z 8[ 7Y.Z #Z     )i D~d Ci -Z GV=W4XAW/~W M"
"Z-[\"[ $Z&[ NZ  MZ .Z\"Z'Z(Z :Z \"Z 4Z?] 9Z 2Y=_=Y(Y8ZJZ([\"[ Z -Z\"[$Z3[  L[ 8Y 9Z)Z BZHZ IZJX8XJY LZ@[ /Z 1\\"
"  HX  DX  JY        NY1Y FZ0Z JY $Y/Z JY  <Y 5Z0Z GY1Y 5Y  NX 0XH\\ #Y FY3Y2Y+Y1Y JY.Y IY/Z NY/Y ;Y  9\\ 8Y .Y1"
"Y >YEY BXJXAWJY A[N[ 1YGY 0[  JY  NX  NY     'V@WLX@U$Y5[ BY/Y HX7X DZ.Y FY $Y1Y <YIZ 6Y=Z DY1Y&[:Z:Z*YAYAY HY9"
"Y IY@X@Y LZ/Y NZ/Z 5Y 3Y1Y KY-Z ?[ )Z -[([%]CZC]%Z(Z Jy M[#[(\\  7X  8\\ JXGXGX J[*\\ KWFXGW   &Y 3Y?U -Z %Z>Z "
"/Z    K_MZ   BUC]BVBU   A[D[  >X  #VBW=XDU     *X        EY1Y 1WEW          G[D[ 5W8UCV X*X LW8UCW EZ 8~W N~X M"
"~W N~X M~W N~X.~Q :[  KZ !Z  Z !Z  >Z !Z !Z \"Z :Z&[&Y7ZJY([\"[+[\"[,[\"Z+[#[+Z\"[ J\\D[ JZKX/['Z*[#[*Z#Z)Z#Z)Z"
" 9Z 2z CY/Z MY1Y HY2Z HY2Y GY1Y HY1Y HY1Y-Y2Z 2Z $Z !Z !Z !Z  :Y  Y  NX  Y 6Z.Y IX0X JZ/Z KY.Z LY.Y LZ/Z KY.Z  "
" BYHW=Z KY1Y GX1Y GX1Y GX0Y =YHZ =Y/Z @YHY     1X;X;X*W LW)XJ\\B[IX*XI[0X*W LW <X (ZGY     3~d GYJU   1iKQKi*pN"
"RMo Jr 9q AX.Y HX0Y CZ>Z 7ZJY EY                   !Z        1X@X &TAY ?X?W;W8Z1\\NX   3Y  DY    JX        5Y 0"
"Y1Z 3Z ,\\  5Z M~Z %Z HZ0Z 8Z 6Y.Z #Z     &i G~d Fi )X FV=X5XAW0~Y NZ-[!Z $Z&[ NZ  MZ .[#Z'Z(Z :Z \"Z 4Z>] :Z 2"
"Y=_=Y(Y7ZKZ'Z#[ NZ -[#[$Z2[  M[ 8Y 9Z)Z BZHZ HYJX8XKZ M[?Z /Z 2\\  GX  CX  KY        NY1Y FZ0Z JZ %Y/Z JZ  =Y 4"
"Y0Z GY1Y 5Y  NX 0XG\\ $Y FY3Y2Y+Y1Y JZ/Y IZ0Y MY/Y ;Y  8[ 8Y .Y1Y >ZGZ BYKXAXKY B[LZ 0YHY 1[  IY  NX  Z     &VB"
"XKXBV$Y5[ BY/Y HX8Y CY/Z GY #Y1Y <YIY 6Z<Y DY1Y%Z:Z:Z*YAYAY HY9Y IY@X@Y LZ/Y NZ/Z 5Y 3Y2Z LZ,Z A[ (Z ,[)[%^DZD^"
"%Z(Z Iw L[#['\\  8X  9\\ JZHXHZ J[,\\ KYGXHY   'Y 3Z@U -Z $[B[ .Z  NW $j   @UCpBU   @[D[  ?X  \"UBW=XEU     )X "
"       EY1Y 1WEW          H[D[ 5W8UBV W*X LX8UCW F[ 9~Y ~X N~Y ~X N~Y ~X.~Q 9[  LZ !Z  Z !Z  >Z !Z !Z \"Z :Z&[&"
"Y7ZJY'[#Z)Z#[+[#[+[#[+[#[ K\\B[ K[MX.['Z*Z!Z*Z#Z)Z#Z)Z 9Z 2x AY.Z NY2Z HY2Z IY1Y GY1Y HY1Y HY2Z-X1Z 2Z $Z !Z !Z"
" !Z  :Y  Y  NX  Y 5Y/Z IX0X JZ/Z KZ/Y KY.Y LZ/Z KZ/Y   AYIW<Y IX1Y GX1Y GX1Y GY2Z =YHY <Z0Y ?YHY     0X<X;X*X N"
"X)XJ[@[KX(XK[/X*X NX <X 'YHZ     3~d FXJU   0hKQKh(nMRMo Jq 7o @X.Y HX0X BY=Z 7ZKZ DY                   \"Z    "
"    1W?X &TAY ?W>W;W8Z0e   3Y  EZ    JX        5X /Z2Y 2Z -\\  4Z M~Z %Z HZ0Z 8Z 6Z/Z $Z     #j J~d Ii   CW>X6Y"
"BX0~Y NZ-[![ %Z'\\ NZ  MZ -Z#Z'Z(Z :Z \"Z 4Z=] ;Z 2Y<]<Y(Y7ZKZ'[$[ NZ -[$[#Z1Z  M[ 8Y 8Z*Z BZIZ GZKX8XKZ N[>[ 0"
"Z 3\\  FX  CX  KY        NY2Z FZ0Y IZ %Y/Z JZ  =Y 4Y0Z GY1Y 5Y  NX 0XF\\ %Y FY3Y2Y+Y1Y JZ/Y IZ0Y MY/Y ;Y  7Z 8Y"
" .Y2Z =YGY AYKW@XKY BZJZ 1YIY 1[  HY  NX  Y     %WEYIYFW#Y5[ BY/Y HX8Y CY/Z GY #Y1Y ;XIY 6Y;Z EY1Y%Z:Z:Z*ZBYBZ "
"HY9Y IY@X@Y LZ/Y MY/Z 4Y 4Y2Y KZ,Z B[ 'Z +[+[#_FZF_$Z(Z Gt JZ$[%\\  9X  :\\ J\\IXI[ I\\/\\ K[HXI[   (Y 3Z@U -Z "
"%^F^ /Z  X \"f   >VBnCU   >[D[  @X  \"VCW<XGV     )X        EY1Y 1WEW          I[D[ 5X8UBV!W)X LW8UBW FZ 8~Y!~Z"
" ~Y!~Z ~Y ~Y0~R 9[  LZ !Z  Z !Z  >Z !Z !Z \"Z :Z'[%Y6ZKY'[$[)[$[*[$[*[%[*[$[ K\\@[ Le.[&Z*Z!Z*Z\"Z*Z#Z*[ 9Z 2v "
"?Y.Z NY2Z HX1Z IY1Y GY1Y HY2Z HX1Z.Y1Z 1Y #Y  Y  Y  Y  :Y  Y  NX  Y 5Y/Z IX0X IY/Z KZ/Y KY/Z KY/Z KZ/Y 7\\ 7ZKW"
";Y IX1Y GX1Y GY2Y GY2Z <YIY <Z0Y ?YIZ     0X<X<X)X Y(XJY>YJX(XJY/X)X Y <X 'ZIZ     3~d FYKT   /gJQJg(nMRLm Hp 6"
"m ?X.Y HY1X CZ<Y 6YKZ DY                   \"Z        1W?W %TAY @X>W;W7Y/c   2Y  EY    IX        5X /Z3Z 2Z .\\"
"  3Z M~Z &Z FY1Z 8[ 6Z/Z $Z      i L~d Li   @W>Y7YBW0Z*Y NZ-[![ %Z'[ MZ  MZ -[$Z'Z(Z :Z \"Z 4Z<] <Z 2Y<]<Y(Y6ZL"
"Z'[%[ MZ ,[%[#Z1[  N[ 8Y 8Z+[ AZJZ GZKW6WKZ NZ<[ 1Z 3[  EX  CX  KY        NY2Z FZ0Y IZ %Z1[ IY  =Y 4Z1Z GY1Y 5Y"
"  NX 0XE\\ &Y FY3Y2Y+Y1Y JZ0Z IZ0Y MZ1Z ;Y  6Y 8Y .Y2Z =YGY AYKW?WKX B[J[ 1YJY 2[  GY  NX  Y     $ZL[H[JY#Y6\\ "
"BY0Y GX8X BZ0Z GY #Y1Y ;YKZ 7Z:Y EY2Z%Z:Z:Z*ZBYBZ HY9Y IY@X@Y L[1Z MY/Y 3Y 4Z3Y LZ+Z C\\ 'Z +[,[!_GZG_#Z(Z Fq H"
"[%[$\\  :X  ;\\ H\\JXJ\\ H\\1\\ J\\IXJ\\   (Y 3Z@U -Z &x 0Z  X  c   <UAmDV   =[CZ  AX  !VDW<YHU     (X        E"
"Y1Y 1WEW          JZCZ 3W8UAV\"X*X LX9UAW G[ 9Z*Y!Z+Z Y*Y!Z+Z Y*Z\"Z+Z0Z3Z 8[  MZ !Z  Z !Z  >Z !Z !Z \"Z :Z(\\%"
"Y6ZKY&[%[)\\&[)[%[)[%[)[%[ L\\>[ Ld.[&Z*Z!Z*Z\"Z+[\"Z+Z 8Z 2s <Y-Y NX1Z IY1Z IY2Z GY2Z HY2Z HX1Z.Y1Z 1Z $Y  Y  "
"Z !Z  ;Y  Y  NX  Y 5Y/Z IX0X IY/Y JZ0Z KZ0Z KY/Y IY0Z 7\\ 6YLX<Z IX1Y GY2Y GY2Y GY2Z <YJZ <Z0Y >YJY     .X=X=Y("
"X!X'YJW<WJX&XJW/Y(X!X ;X &YIY     #[  LYLU   .fJQJf&lLRLm Gn 4k >X.Y HY2Y CZ<Z 7YKY BY                   #[    "
"    3X@X %TAY @W=W;W7Z0b   1Y  EY    IX        5X /Z3Z 2Z /\\  2Z )Z  JZ FZ2Z 8Z 5Z/Z %Z      Ki   :j   >W=X8ZC"
"W/Z*Z Z-Z N[ &Z(\\ MZ  MZ -\\%Z'Z(Z :Z \"Z 4Z;] =Z 2Y<]<Y(Y6ZLZ&[&[ MZ ,\\'[\"Z0Z  NZ 7Y 8Z+Z @ZJY FZLX6XLY N[;"
"Z 1Z 4\\  EX  BX  LY        NY2Z F[2Z HZ %Y1[ IZ  >Y 4Z2[ GY1Y 5Y  NX 0XD\\ 'Y FY3Y2Y+Y1Y IY0Z IZ1Z MZ1Z ;Y  6Y"
" 8Y .Y2Z =ZIZ @XLX?WLY C[H[ 2YKZ 3[  EX  NX  Y     $hFh\"Z7\\ BY0Y GX9Y BZ1Z FX \"Y1Y ;YKY 6Y9Y EY2Z%Z;[:Z*ZBYB"
"Y GY9Y IY@XAZ L[1Y LZ1Z 3Y 3Y3Y LZ*Z D[ &Z *[-[ aJZJa\"Z(Z Cl F\\'[\"\\  ;X  <\\ F\\KXK\\ F\\3\\ H\\JXK\\   'Y "
"2ZAU -Z 'z 1Z  X  Na   ;V@jDV   :ZCZ  BX   UDW;XIU     'X        EY2Z 1WEW          KZCZ 3X9U@V\"W*X LX9VAW H[ "
"8Z*Z\"Y)Y!Z*Z\"Z*Y!Z*Z\"Z*Z1Z3Z 8[  MZ !Z  Z !Z  >Z !Z !Z \"Z :Z(\\%Y5ZLY&[&['[&[([&[)\\'\\)[&[ L\\<[ Mc.[$Z,[!"
"[,[\"Z+Z!Z+Z 8Z 2n 7Y-Y NX1Z IY2[ IY2Z GY2Z HY2Z IY2[.Y2\\ 2Z $Z !Z !Z !Z  ;Y  Y  NX  Y 5Z0Y HX0X IZ1Z IY0Z KZ0"
"Y JZ1Z IZ1Z 7\\ 6YMX;Z IY3Z GY2Y GY2Y GY2Z ;YKY ;Z1Z >YJY     .Y>X=X'Y#Y&XIU:UJY&YJU.X'Y#Y ;X &YJZ     #Z  JXLU"
"   -dIQId%kKRKk El 2j >X.Y HY2Y CY;Z 7ZMZ BZ                   #Z        3X@X %TAX @W<W;W7Z/a   0Y  FY    IX   "
"     6X -Z4Z 2Z 0\\  2[ )Z  JZ FZ2Z 8Z 5Z/Z %Z      Hi   @j   :V=Y9ZDX/Z*Z Z-Z N\\ 'Z)\\ LZ  MZ ,[%Z'Z(Z :Z \"Z"
" 4Z:] >Z 2Y;[;Y(Y5ZMZ&\\([ LZ +['[\"Z0[  Z 7Y 8[,Z ?YKZ EYLX6XLY [:[ 2Z 5\\  DX  BX  LY        NY3[ F[2Z HZ %Y1"
"[ IZ  >Y 3Y2[ GY1Y 5Y  NX 0XC\\ (Y FY3Y2Y+Y1Y IZ2Z H[2Z LY1Z ;Y  6Z 9Y .Y2Z <YIY ?YMX?XMY CZFZ 2YKY 3[  DY  X  "
"Y     #gEf!Z7\\ BY0Y GX9Y BZ1Z FX \"Y1Y :XLZ 7Z9Z FY2Z%Z;\\<[)ZCYCZ GY9Y IZAXAZ L[1Y LZ1Z 3Y 3Y4Y KZ*Z E[ %Z )["
"/[ MdNZNd!Z(Z Ag B['[!\\  <X  =\\ D\\LXL\\ D[4\\ F\\KXL\\   &Z 3ZAU -Z (| 2Z  X  L^   9V?fBU   8ZCZ  CX   V JV "
"             CY2Z 1WEW          LZCZ 2W9V@V#X+X KW8U@W I[ 7Z*Z#Z)Z\"Z)Y#Z)Z\"Z)Y#Z)Z2Z2Z 7[  NZ !Z  Z !Z  >Z !Z"
" !Z \"Z :Z)\\$Y5ZLY%[(\\'\\(['\\(['['['[(\\ M\\:[ Ma-[$Z,Z NZ,Z![,Z!Z,[ 8Z 2Z #Y-Y NX2[ IY2[ IY2Z GY3[ HX2[ IY2"
"[.Y2\\ 2Z $Z !Z !Z  Y  ;Y  Y  NX  Y 5Z1Z HX0X IZ1Z IZ1Z JZ2Z JZ1Z IZ1Z 7\\ 6c:Z IY3Z GY3Z GY3Z GY3[ ;YKY ;[2Z ="
"YLY     ,Y?X>Y&Y%Y%YIS8SJY$YJS.Y&Y%Y :X &ZKY     #Z  IYNU   ,cISIb#jKRJi Cj 1i =X.Y GY4Y BY:Y 7ZMZ AZ          "
"         $[,P       )W?X %TBY AX<W;W7[/_   /Y  FY    IX        6X -Z5Z 1Z 1\\  1Z (Z  K[ EY2Z 9Z 4Z0[ &[      F"
"j   Ei   7W=Y;[EX/Z(Z!Z.[ M[!P'Z*] LZ  MZ ,\\&Z'Z(Z :Z \"Z 4Z9] ?Z 2Y;[;Y(Y4YMZ%[)\\ LZ +\\)[!Z/Z  Z 7Y 7Z-[ ?Z"
"LZ EZMX6XMZ Z8[ 3Z 6\\  CX  BX  LY        NY3[ F[2Y GZ %Z3\\ HZ  ?Y 3Z4\\ GY1Y 5Y  NX 0XB\\ )Y FY3Y2Y+Y1Y IZ2Z "
"H[2Y KZ3[ ;Y  6Z 9Y .Z4[ <YIY ?YMW>XMY DZDZ 2YLY 3[  DY  X  Y     \"eCd NY8^ CY0Y GX:Y @Z2Z FX \"Y1Y :YMY 6Y7Y "
"FY2Z%[<\\<Z(ZCYCZ GY9Y HYAXAY K\\3Z KZ2Z 3Y 3Z5Y LZ)Z F[ $Z ([1[ K~U Z(Z ;[ <\\)[ N[  <X  <Z B\\MXM\\ BZ3Z D\\L"
"XM\\   %Z 3ZAU -Z )~ 3Z  X  J]   9V>a@V   7YBY  CX   NV LV              BZ3Z 1WEW          LYBY 2W8U?V#W+X KX9U"
"?W J[ 7Z(Y#Z)Z#Z(Z$Z)Z\"Y(Z$Z(Y2Z2Z 7\\\"P NZ !Z  Z !Z  >Z !Z !Z \"Z :Z*\\#Y4ZMY%\\)[%[)\\&[)\\'\\)\\'\\)[ M\\8"
"[ N`-[#Z,Z NZ,Z Z-[![-[ 8Z 2Z #Y-Y NX2[ IY2[ IY3[ GY3[ HY3[ HX2[.Y3^ 2Z $Z !Z !Z !Z  <Y  Y  NX  Y 4Z2Z HX0X HZ2"
"Z IZ2Z IZ2Z IZ2Z IZ2Z 6\\ 5a:Z HY3Z GY3Z GY3Z GY3[ ;YLY :[2Y <YLY     ,Y?X?Y$Y'Y#YIQ6QIY$YIQ.Y$Y'Y 9X %YLZ     "
"$Z  HYNU   +aHSH`!hJRIg Bi /g <X.Y GY4Y CZ:Y 6YMY @[                   $Z-Q       )W?W $TBY AW;W<X6Z.]   .Y  GY"
"    HX        6X -Z5Z 1Z 2\\  0Z (Z  L[ DZ4Z 8Z 4[1Z %Z      Bj   Ki   4W=Z=\\GY.Z(Z!Z.[ M\\#Q'Z+] KZ  MZ +\\'Z"
"'Z(Z :Z \"Z 4Z8] @Z 2Y:Y:Y(Y4ZNZ%\\*[ KZ *\\+\\!Z/[ \"[ 7Y 7Z-Z >ZMZ DZMW4WMZ![7Z 3Z 7\\  BX  AX  MY        NY3"
"[ F\\4Z FZ &Z3\\ HZ  ?Y 3Z4\\ GY1Y 5Y  NX 0X@[ *Y FY3Y2Y+Y1Y HZ3Z H\\4Z KZ3[ ;Y  5Y 9Y -Y4[ ;YKY >YNX=WNY D[D[ "
"3YMY 3[  CY  X  Y     !cAb MZ9^ CZ2Z GX:Y @Z3Z EX \"Y1Y :YMY 7Z7Y FZ4[$Z<\\<Z(ZCYCY FY9Y HYAXBZ K\\3Z KZ3Z 2Y 2"
"Y6Z LZ(Z H\\ $Z (\\3[ I~R MZ(Z :Z ;\\+\\ MY  ;X  ;X @\\NXN\\ @X1X B\\MXN\\   $Z 2ZBU -Z *~Q 4Z  X  I]   :W9U;V "
"  5XAX  CX   MV NV              AZ3Z 1WEW          LXAX 2X8s+W,Y JW8t#\\ 7Z(Z%Z'Y#Z(Z$Y'Z$Z(Z$Z(Z4Z1Z 6[#Q NZ !"
"Z  Z !Z  >Z !Z !Z \"Z :Z+]#Y4ZMY$[*\\%\\*[%\\+\\%\\+\\%\\+\\ N\\6[ N^-\\#[.[ N[.[ [.Z NZ-Z 7Z 2Z #Y-Y NY4\\ IY3"
"\\ IY3[ GY3[ HY4\\ HX3\\.Y3^ 2Z $Z !Z !Z !Z  <Y  Y  NX  Y 4Z3Z GX0X HZ3Z GZ3Z IZ3[ IZ3Z GZ3Z 6\\ 5`9Z HY4[ GY4["
" GZ5[ GZ5\\ :YMY :\\4Z ;XMZ     +Y@X@Y#Z)Z\"Y(Y\"Y(Y#Z)Z 9X %ZMZ     %Z  F_   )^GSG^ NfIRHe @g -e ;X.Y GZ6Z CY9"
"Z 7ZNY ?[                   %[/R       *X@X $TBY BX;X=X6[.]   /Y  GY    HX        7X +Z7Z 0Z 3\\  0[ (Z  L[ DZ4"
"Z 9[ 3Z2[ &Z      >i   i   2W<Z?]HZ.Y'Z!Z/\\ L\\&S'Z,] JZ  MZ *\\(Z'Z(Z :Z \"Z 4Z7] AZ 2Y JY(Y3e$\\,\\ KZ )\\-"
"\\ Z.Z \"[ 7Y 7[/[ =ZNZ DZNX4XNY![6[ 4Z 7[  AX  AX  MY        NY4\\ F\\4Z F[ &Z5] H[  @Y 2Z6] GY1Y 5Y  NX 0X?[ +"
"Y FY3Y2Y+Y1Y HZ4Z G\\4Z JZ5\\ ;Y  6Y 8Y -Y5\\ ;YKY =XNX=WNY E[B[ 3YNY 4[  BY  X  Y      N_=_ LZ:_ CZ2Y FX;Y >Z4"
"Z EY #Y1Y 9XNZ 7Y6Z GZ4[$Z=]=['ZDYDZ FY9Y HZBXBZ K]5Z J[5[ 2Y 2Z7Y L[(Z H[ #Z '\\5[ F~ LZ(Z :Z :\\-\\ KW  :X  :"
"V >r >V/V @s   #Z 2[CU -Z +[MeL[ 5Z  X  G\\   :W!V   3W@W     7V!W              AZ4[ 1WEW          LW@W 1W7s,X-"
"Y JX8t$\\ 7Z'Z%Z'Z$Z'Y%Z'Z$Z'Y%Z'Z4Z1Z 6\\&S NZ !Z  Z !Z  >Z !Z !Z \"Z :Z,]\"Y3ZNY$\\,\\#\\,\\$\\,\\$\\-\\$\\,"
"\\ N\\4[ ]-\\![/Z LZ/[ N[/[ N[/[ 7Z 2Z #Y-Y NY4\\ HY5] IY4\\ GY4\\ HY4\\ HY4\\.Z5` 2Z $Z !Z !Z !Z  =Y  Y  NX  Y "
"3Z4Z GX0X H[5[ GZ4Z GZ4Z H[5[ GZ4[ 6\\ 5_9[ HZ5[ GZ5[ FY5[ FY5\\ :YNZ :\\4Z ;YNY     )YAXAZ\"Z+Z!Z*Y Y*Z\"Z+Z 8"
"X $YMY     %[  F^   '\\FSF\\ LcGRGc >f ,c :X.Y FZ7Y BY8Y 7e >[                   %[1S   -Y   'X@X ;Q:TCZ CX:X=X"
"5[.]   /Y  HY    HX  NZ    GZ 'X +[8Z 0Z 4\\  0[ 'Z  M\\ CZ6[ 9Z 2[3[ '[ 0Y  Y  ?f   f  BX DW=\\C_J[.Z&Z\"Z0\\ "
"J\\(T'Z._ JZ  MZ *])Z'Z(Z :Z \"Z 4Z6] BZ 2Y JY(Y3e#\\.\\ JZ )]/\\ NZ.[ NQ'[ 6Y 6[0[ =ZNZ CYNX4XNY!Z4[ 5Z 8[  @X"
"  AX  MY        NY5] F]6Z DZ &Z5] G[  AY 2[8^ GY1Y 5Y  NX 0X>[ ,Y FY3Y2Y+Y1Y H[6[ G]6Z IZ5\\ ;Y  6Y 8Y -Z6\\ ;Z"
"MZ =b=b EZ@Z 3d 5[  AY  X  Y      L[:\\ IZ;` D[4Z FX<Z >Z5[ EY #Y1Y 9c 7Z5Y GZ5\\$[>^>['[EYE[ FY9Y HZBXCZ J]5Z "
"IZ5Z 1Y 1Y8Z LZ&Z J[ \"Z &\\8] E| KZ(Z :Z :]/] JU  9X  9T <p <T-T >q   \"Z 1ZCU -Z ,[JaI[ 6Z  X  F\\   :W#V   1"
"V?V     7W#W              @[5[ 1WEW          LV?V 1X7s,W-Y JX7t%\\ 6Z&Z&Z'Z%Z&Z&Z'Z%Z&Z&Z&Y4Y0Z 5\\(T NZ !Z  Z "
"!Z  >Z !Z !Z \"Z :Z.^!Y3e#\\.\\!\\.\\#].\\#]/]#\\.\\ N\\2[ ]/]![0[ L[0[ M[0[ N\\1[ 6Z 2Z #Y-Y NY5] HY5] IZ6] GY"
"5] HY5] HY5]-Y5a 3[ %[ \"[ \"[ \"[  >Y  Y  NX  Y 3Z5[ GX0X GZ5Z F[6[ G[6[ GZ5Z F[5Z 5\\ 4^9Z FY6\\ FY6\\ FY6\\ "
"FY6] 9c 9]6Z :d     )[CXBZ Z-Z NZ-[ [-Z Z-Z 7X $YNZ     %Z  D]   $VCSDW G`FSG` ;d +c :X.Y F[9Z CZ8Y 6d =\\     "
"              '\\3T   -Z   (W?X ;S<TDZ BW8W=W4\\1`   0Y  HY    HX  NZ    GZ 'X *Z9Z /Z 5\\  0\\ 'Z  N\\ B[8[ 8Z"
" 2\\5[ '[ /Z \"[  >d   c  @Z EW<_Ks-Z&Z\"Z1] J^,V'Z/_ IZ  MZ )]*Z'Z(Z :Z \"Z 4Z5] CZ 2Y JY(Y2d#]0\\ IZ (]1] NZ-"
"Z NS*\\ 6Y 6[1[ <e Bc4c\"[3Z 5Z 9\\  @X  AX  MY        NZ6] F^8[ D[ &Z7^ G[  AY 1[:_ GY1Y 5Y  NX 0X=[ -Y FY3Y2Y"
"+Y1Y G[7Z F]7[ HZ7] ;Y  6Y 7Y .Z7] :YMY <a<a EZ>Z 4c 5[  @Y  X  Y      HS3V FZ<a D\\5Z FX<Y =[7[ DZ $Y1Y 9c 7Y4"
"Z H[6\\#Z?WNV>Z%ZEYF[ EY9Y GZCXD[ J^7Z H[7[ 1Y 1Z:Z KZ&Z K[ !Z %];] Bx IZ(Z :Z 9]1] HS  8X  8R :n :R+R <o   !Z "
"1[DU -Z -[F\\F[ 7Z  X  E\\   :W&W   /U>U     6W%W              ?[6\\ 1WEW          LU>U 0W6s-X.X HW6t&\\ 5Z&Z'Z"
"%Z&Z&Z'Z%Z&Z&Z&Z&Z6Z0Z 4],V NZ !Z  Z !Z  >Z !Z !Z \"Z :Z0`!Y2d\"\\0]!]0\\!]0\\!]1]!]1] \\0[ ]1] N[2\\ L\\2[ L\\"
"2[ L[1[ 6Z 2Z #Y.Y MZ7^ HY6^ HY6] GZ6] HZ7^ HZ7^-Y6c 3[ %[ \"[ \"[ \"[  ?Y  Y  NX  Y 3[7[ FX0X G[7[ E[7[ FZ7[ F"
"[7[ E[7[ 5\\ 4]9[ FZ8] FZ8] FZ8] FZ7] 9c 9]7[ 9b     '[DXD[ N[/Z LZ/[ M[0[ N[/Z 6X $d     %Z  C\\    ?S 2\\ETD"
"\\ 9b )a 9X.Y E[<[ BY7Z 7c ;\\                   '\\5U   -Z   (W?W :U>TE[ CX8X?X3\\3b   1Y  IY    GX  NZ    GZ ("
"X )[;[ /Z 5[ %Q-\\ &Z BQ/] AZ9\\ 9Z 0[6\\ (\\ /Z \"[  ;a   `  =Z EX<nNd,Z$Y\"Z2] H^.W'Z2a HZ  MZ (^,Z'Z(Z :Z \""
"Z 4Z4] DZ 2Y JY(Y2d\"]3^ IZ ']3] MZ-[ U-] 6Y 5\\4\\ ;d Bb2b#[2[ 6Z :\\  ?X  @X  NY        MZ8^ F^8Z B[ '[9_ F[,"
"P 7Y 1\\<` GY1Y 5Y  NX 0X<[ .Y FY3Y2Y+Y1Y G[8[ F^9[ G[9^ ;Y *Q/Z 7Y -Z9^ :YMY <a;` F[>[ 4b 6[  ?Y  X  Y        "
"FZ=b E]7Z EX=Z <[9\\ D[ %Y1Y 8a 6Y3Y H\\8]#[@WNW@[%[FYG\\ EY9Y G[DXD[ J_9[ G[9[ /Y 1Z;Z LZ%Z L\\ !Z $]=\\ >t GZ"
"(Z :Z 8]3] FQ  7X  7P 8l 8P)P :m    Z 0[EU -Z .[?P?[ 8Z  X  D[   9W(W   -T<S     5X)X              >\\8] 1WEW  "
"        LS<T 0W5s-W.X HX6t'\\ 5Z$Y'Z%Z'[%Z(Z%Z&Z%Z(Z%Z6Z0Z 4^.W NZ !Z  Z !Z  >Z !Z !Z \"Z :Z2a Y2d\"^3] N]3^ ]3"
"] N]3] N]3] \\.[!^3] M\\4\\ J\\4\\ K\\4\\ L\\4\\ 5Z 2Z #Y.Y MZ8_ HZ8_ HZ8^ FZ8^ HZ8_ HZ8_-Z8e-Q)\\ &\\-Q G\\-Q "
"G\\-Q G\\-Q 5Y  Y  NX  Y 2[9\\ FX0X F[9[ D\\9[ E[8[ E[9[ D\\9[ 4\\ 3[9[ EZ9^ FZ9^ FZ9^ F[9^ 9b 8^9[ 8b     &[2["
" L\\3\\ K[2[ K[2[ L\\3\\ 6X #c     &Z  B\\    ?S /UATAT 4a '_ 8X.Y E\\>\\ BY6Y 7c :]                   (\\7V   "
"-Z   )X@X :W@TF[ BW7X?X3]6e   1X  IY    GX  NZ    GZ (X ([=[ .Z 6[ $S1^ &Z BS3^ @\\<\\ 8Z 0]9] FR6] .Z \"[  8^ "
"  ^  ;Z DW;lMc+Z$Z#Z4_ G_2Y'Z5c GZ  MZ '^/\\'Z(Z :Z \"Z 4Z3] EZ 2Y JY(Y1c!^6^ HZ '^6^ LZ,Z X1] 5Y 5]6\\ :c Ab2a"
"\"Z0[ 7Z ;\\  >X  @X  NY        MZ:` F_:[ B\\3P D[;` E\\1S 7Y 0\\>a GY1Y 5Y  NX 0X;\\ 0Y FY3Y2Y+Y1Y F[:[ E_;\\ "
"F[;_ ;Y *S1Y 6Z .[;_ :e ;`;` G[<[ 5a 6[  >Y  X  Y        F[?YNY F_:[ DX?Z :[;\\ B[ &Y1Y 8a 7Z3Y H]:^#\\BXNWA[#["
"GYH\\ DY9Y F\\FXF\\ I`;[ F\\;\\ /Z 2[=Z KZ$Z N\\  Z #^A] :n DZ(Z :Z 7]5]   +X    Mj   (k    NZ 0\\FUBP ;Z /[,[ "
"9Z  X  CZ   8X+W   *R;R     4X+X              =]:^ 1WEW          LR;R /X5s.W.X GW5t(\\ 4Z$Z(Z%Z'Z$Z(Z$Y'Z$Z(Z$Z"
"8Z/Z 3_2Y NZ !Z  Z !Z  >Z !Z !Z \"Z :Z5c NY1c!^6^ L^6^ M^6^ M]5] M^6^ \\,[#a7^ K\\6] I\\6\\ J]6\\ J\\6] 5Z 2Z #"
"Y/Z LZ:` H[:` H[:_ FZ:` GZ:` GZ:`-[:YN\\0S(\\4Q C\\0S F\\0S F\\0S F\\0S 5Y  Y  NX  Y 1[:[ EX0X F\\;\\ C\\;[ C[:"
"[ D\\;\\ C\\;\\ 4\\ 3[:\\ DZ;_ EZ;_ EZ;_ EZ;` 8a 8_;\\ 7a     %\\6\\ J\\5\\ I\\6\\ I\\6\\ J\\5\\ 5X #c     'Z  "
"@[    @T  JT  _ %] 7X.Y D^D^ BZ6Y 6b 9_                   *];X   -Z   )X@X :ZCTH] CX7YAX1^:h   2Y  JY    GX  NZ"
"    GZ (X (\\?\\ .Z 7\\ $W7_ %Z BV8` ?\\>] 9[ /];] ET9] -Z \"[  5[   [  8Z DX;jLb*Z$Z#Z7a E`7\\'Z9f FZ  MZ &`4^"
"'Z(Z :Z \"Z 4Z2] FZ 2Y JY(Y1c _:_ GZ &_9^ KZ,[![6^ 4Y 4]9] 8b @a2a#[/Z 7Z ;[  =X  @X  NY        M[<a Fa>\\ @]7R"
" D\\=a E]4U 7Y /]Bc GY1Y 5Y  NX 0X:\\ 1Y FY3Y2Y+Y1Y E\\>] E`=\\ E\\=` ;Y *U5[ 6[ /\\>a 9c :_:` GZ:Z 4` 6[  >Y  "
"X  Y        E[AYMZ G`<[ CX@Z 9\\=\\ A\\3Q EY1Y 7` 7Y2Z I^<_\"[BWMXC\\#]IYI\\ CY9Y F]GXG] Ia=\\ E\\=\\ .[ 2[?Z J"
"Z$Z N[  NZ \"^C^ 7g @Z(Z :Z 7_9_   +X    Lh   &i    MZ /]HUDR ;Z .Y*Y 8Z  X  BZ   8Y/X   (Q:Q     2X/Y         "
"     <^<` 2WEW          LQ:Q .W MV(X/X GX NW\"\\ 3Z$Z)Z#Z(Z$Z)Z#Z(Z$Z)Z#Z8Z/Z 2`7\\ NZ !Z  Z !Z  >Z !Z !Z \"Z :"
"Z9f MY0b _:_ J_:_ K_:_ L_9_ L_9^ N[*[$c:^ J^:^ H^:^ I^:] H]9] 4Z 2Z #YIP7[ L[<a G[<a G[=a F[<a G[<a G[<a,[=ZL\\"
"4V'\\7S B\\4V E]5V E]5V E]5V 5Y  Y  NX  Y 1\\=\\ DX0X E\\=\\ A\\=\\ C]>] C\\=\\ A\\=\\ 3\\ 2\\=\\ C[=` E[=` E[="
"` E[=a 8a 8`=\\ 6`     #]:] H]9] G]:] G]:] H]9] 4W !a     'Z  ?Z    ?U  KT  N] $] 7X.Y Cv AZ6Z 7a 7a           "
"        -_?Z   -Z   )W?X :^GTK_ CX5XAX0_>k   3Y  JX    FX  NZ    GZ )Y ']C] ?} I~S IZ=b %Z BZ>a =]B^ 8Z ._?^ DX"
"@_ ,Z \"[  3Y   X  5Z CW:gJ`)Z\"Z$~T Cb=_'~W E~S FZ %b:a'Z(Z :Z \"Z 4Z1] G~Q)Y JY(Y0b N`>` FZ %a?` JZ+Z!^<a 4Y "
"3_>_ 8b @a2a$[.[ 8Z <~` AX  ?X  Y        L\\@c Fb@] ?^<U C]Ac D^9X 7Y /aI[NY GY1Y 5Y  NX 0X9\\ 2Y FY3Y2Y+Y1Y E]"
"@] Db@\\ C]Ab ;Y *X9\\ 5] 1\\Ac 9c :_:_ GZ9[ 5` 7[  =Y  X  Y        E]DZM[ Hb@] BXB[ 8]A^ @]8T EY1Y 7_ 7Z1Y I`@"
"b#]EXLXE\\!]JYK^ CY9Y E_JXJ_ HcA] C]A] ,] 4[B\\ K~c!~T FZ 3oDo A[ :Z(Z :Z 6a?a   *X    Kf   $g    LZ .^JUGU H~U"
" JW(W 7Z  X  AY   7Z3Y   &P9P     1Y3Y     <~d       3`@b 2WEW          LP9P .X MV(W/X GX MW#\\ 3Z\"Z*Z#Z)Z\"Z*"
"Z#Z)[#Z*Z#Z9Z.~T+b=_ N~T J~T I~S I~S 7Z !Z !Z \"Z :~V KY0b N`>` H`>` I`>` Ja?a Ja?` LY(Y$f?` H_>_ F_>_ G_>_ H_>"
"_ 3Z 2Z #YIS;[ K\\?c G\\?c G\\?b E\\@c F\\@c G\\?c,\\?[L^9Y'^<V B_:Y E_:Y E_:Y D^:Y 5Y  Y  NX  Y 0]@] DX0X D]A]"
" @]@] A]@] A]A^ A]@] 2\\ 2]@] B]Ab E]Ab D\\Ab D\\Ac 7_ 7b@\\ 5`     \"_@_ F_?_ E_@_ E_@_ F_?_ 3W !a     'Z  ?Z "
"   ?U  KT  M\\ #[ 6X.Y Bu AY5Z 7a 6f                   2aE]   -Z   )W?W 9~ BW4YCY/bFp   3X  KY    FX  NZ    GZ "
")X %^G^ >} I~S I~ $Z B| ;^F_ 7Z -aEa Dv +Z \"[  0V   U  2Z CX9dI^'Z\"Z$~S AfGd'~U C~S FZ $gGg&Z(Z :Z \"Z 4Z0] H"
"~Q)Y JY(Y0b McGd EZ $dGc IZ+[\"cEd 3Y 3cGc 7a ?`1a$Z,[ 9Z =~a AX  ?X  Y        L^DZNY FYNZF_ =`CY B^EZNY CaB] 7"
"Y .qMY GY1Y 5Y  NX 0X8\\ 3Y FY3Y2Y+Y1Y D_F_ CYNYE_ B^EZNX ;Y *]A^ 4k >^G[NY 8a 9_9^ H[8[ 5^ 6~P 2Y  X  Y       "
" D^H[La NfH` AYD[ 6^E_ ?`?X EY1Y 7_ 7Y0Y IcFk(]HZLZI^ `Nk BY9Z E~Q GYNZE^ B_E_ ,e ;]G] J~c!~T FZ 3oDo @Z :Z(Z :"
"Z 5dGd   )X    Jd   \"e    KZ -`MUKY H~U IU&U 6Z  X  AY   5Z7Z          LZ7Z     ;~d       3cFk 8WEW           "
" BW LV)X0X FW LW$\\ 2Z\"Z+[#Z)Z\"Z*Z\"Z*Z\"Z*Z\"Z:Z.~T*fGd N~T J~T I~S I~S 7Z !Z !Z \"Z :~U JY/a MdGc FcGd GcGd"
" HdGd HdGc JW&W$kGc FbFb DbFb FcFb FcGc 3Z 2Z #YIWB] I^DZNY F]D[NY F]D[NX E^DZNY F^DZNY F^E[NY+]D]J`@]&`BY AaA]"
" DaA] DaA] DaA] 5Y  Y  NX  Y /_F_ CX0X D_E_ ?_F_ ?_F_ @_E_ ?_F_   7aF_ @^FZMX D^FZMX D_GZMX D_G[NY 7_ 7YNYE_ 4^"
"      dLd CdMd BdLd CdLd DeMd 2X !`     %X  =Y    ?U  LV  MZ !Y 5X.Y As AZ4Y 6` 5~]                  )x   -Z   "
"*X@X 9} BX3YFZ-{L]   4Y  LY    FX  NZ    GZ )X $t >} I~S I} #Z B{ :v 7[ ,{ Cu *Z \"[  -S   S  0Z BW8aG[%[\"Z$~R"
" ?~S'~T B~S FZ #~V%Z(Z :Z \"Z 4Z/] I~Q)Y JY(Y/a L~ DZ #~ HZ*Z\"~R 2Y 2} 5` ?`0_$[+Z 9Z =~a AX  ?X  Y        KsN"
"Y FYNr ;u AqMY B{ 7Y -oLY GY1Y 5Y  NX 0X7\\ 4Y FY3Y2Y+Y1Y Cv BYNr ArMX ;Y *y 2j >qMY 8a 8^9^ I[6Z 5^ 6~P 2Y  X "
" Y        CpK` N} ?YF[ 5w =x EY1Y 6] 7Z0Z J~Y(nJm M{ AY9\\ F~ FYMq @w *d ;r J~d!~T FZ 3oDo @Z :Z(Z :Z 4~   'X  "
"  Ib    c    JZ ,u H~U HS$S 5Z  X  AY   4\\>\\          I]>\\     :~d       3~Y 8WEW            CW KV)W0X FX LW"
"$[ 2[\"Z+Z!Z*Z\"Z+Z!Z*Z!Z,Z!Z:Z.~T)~S N~T J~T I~S I~S 7Z !Z !Z \"Z :~T IY/a L~ D~ E~ F~ E~ HU$U$~X D| B| D} D} "
"2Z 2Z #YIr HrMY FsMY FsMX DsNY ErMY FsMY+uH|%v @| C| C| C| 5Y  Y  NX  Y .v BX0X Cw =w >v >w =w   8{ ?qMX CqMX C"
"qMX CqMY 6] 6YNr 3^      My Ay @y @z Ay 1X  _     $V  <X    ?V  LV  LX  NW 4X.Y @p ?Z4Z 7_ 2~[                 "
" (v   ,Z   *X@X 9| AW1[K[+yJ]   5Y  LX    EX  NZ    GZ )X #r =} I~S I| \"Z Bz 8t 6Z *y Bt )Z \"[  *P   P  -Z BX"
"6[DX\"Z Z%~Q <~P&~R @~S FZ \"~T$Z(Z :Z \"Z 4Z.] J~Q)Y JY(Y/a K| CZ !{ GZ*[#~Q 1Y 1{ 4_ =_0_%[*[ :Z =~a AX  >X !"
"Y        JqMY FYMp 9t ApLY Az 7Y ,mKY GY1Y 5Y  NX 0X6\\ 5Y FY3Y2Y+Y1Y Bt AYMp ?pLX ;Y *x 1j =oLY 8a 8]8^ IZ4Z 6"
"] 5~P 2Y  X  Y        CoI_ N} ?[K] 3u ;w EY1Y 6] 7Y.Y JvM_'mJm Ly @Y9b K| EYLp ?u (c :p I~e\"~T FZ 3oDo @Z :Z(Z"
" :Z 2{   &X    H`    Ma    IZ +t H~U GQ\"Q 4Z  X  AY   2aLb          FaKa     8~d       3YNlN_ 8WEW            "
"DX KV*W0o-W KW%[ 1Z Z,Z!Z+Z Z,Z!Z+Z Z,Z!Z;Z-~T'~P M~T J~T I~S I~S 7Z !Z !Z \"Z :~R GY.` K| B| C{ B{ B{ FS\"S$YM"
"{ Bz @z B{ B{ 1Z 2Z #YIq GqLY EqLY EqLX CqMY ErMY EqLY*sF{$u ?{ B{ B{ B{ 5Y  Y  NX  Y -t AX0X Bu ;u <t <u ;u   "
"8{ >pLX CpLX CpLX BoLY 6] 6YMp 1]      Lv >w =v =v >w 0X  _     #T  ;X    ?W  MV  LW  LV 4X.Y ?n >Y3Z 7_ 1~Z   "
"               't   +Z   *W?X 8y @X1j)vG]   5X  MY    EX  NZ    GZ *X !p <} I~S Iz  Z By 6r 5Z )w As (Z \"[    "
"    5Z AX  HZ Z%~ 9|$~P >~S FZ  ~P\"Z(Z :Z \"Z 4Z-] K~Q)Y JY(Y.` Jy AZ  x EZ)Z#~P 0Y /x 3_ =_0_%Z([ ;Z =~a AX  "
">X !Y        JpLY FYLn 7s @nKY @y 7Y +kJY GY1Y 5Y  NX 0X5\\ 6Y FY3Y2Y+Y1Y Ar @YLn =nKX ;Y *w /i <mKY 7_ 7]8] IZ"
"3[ 6\\ 5~P 2Y  X  Y        BmH_ N{ <k 0r 9v EY1Y 6] 8Z.Z KYNkM_&kHk Jw ?Y8a Jy CYKn =s &b 9n H~e\"~T FZ 3oDo @Z"
" :Z(Z :Z 1y   %X    G^    K_    HZ *s H~U   *Z  X  AY   1t          Bs     6~d       3YNkM_ 8WEW            DW "
"JV+X0o.X KW%Z 0Z Z-Z NZ,Z Z-[ Z,Z Z-[ Z<Z-~T&| K~T J~T I~S I~S 7Z !Z !Z \"Z :~P EY.` Iy @y @y @y @y DQ Q$YKy @x"
" >x ?x @y 0Z 2Z #YIp EoKY DoKY DoKX BoLY DpLY DoKY)qCy#t =y @y @y @y 5Y  Y  NX  Y ,r @X0X As 9s :r :s 9s   7z <"
"nKX BnKX BnKX BnKY 6] 6YLn 0\\      Jt ;s :t ;t ;s .X  N]     !R  9V    >W  NX  LU  KU 3X.Y >l =Y2Y 7_ /~X     "
"             %p   )Z   *W?W 4u @X/i(tE]   6Y  NX    DX  NZ    GZ *X  m :} I~S Iy  NZ Bw 2o 5Z 'u @r 'Z \"Z     "
"   4Z AY  J[ Z%} 6x\"} <~S FZ  N| Z(Z :Z \"Z 4Z,] L~Q)Y JY(Y.` Hv @Z  Mu DZ)[$~ /Y .u 0^ =^/_&['Z ;Z =~a AX  >X"
" !Y        InKY FYKl 5r ?lJY >w 7Y )hIY GY1Y 5Y  NX 0X4\\ 7Y FY3Y2Y+Y1Y @p ?YKl ;lJX ;Y *v -h ;kJY 7_ 7]7\\ J[2"
"[ 7\\ 5~P 2Y  X  Y        AkE] Nz :i .p 7u EY1Y 5[ 7Y,Y KYMiL_%iGj Hu >Y8a Hv BYJl :p $a 7k H~f\"~T FZ 3oDo @Z "
":Z(Z :Z /u   #X    F\\    I]    GZ )r H~U   *Z  X  AY   /p          >o     4~d       3YMiK^ 8WEW            EX "
"JV+W/o/X JW&Z 0[ Z-Z NZ-[ [.Z NZ,Z NZ.Z NZ=Z,~T$x I~T J~T I~S I~S 7Z !Z !Z \"Z :| BY-_ Hv <v =v =u =v   BXHu =v"
" <v =u <u .Z 2Z #YIo CmJY CmJY CmJX BnKY CmJY CmJY(oAx!r <x ?x ?x ?x 5Y  Y  NX  Y +p ?X0X ?p 7p 7p 7p 7p   6WNp"
" 9lJX AlJX AlJX AlJY 5[ 5YKl /\\      Hp 8q 7p 7p 8q -X  N]      NP  9V    ?Y  X  KS  IS 2X.Y <h <Z2Y 6^ -~V   "
"               $n   (Z   +X@X 1o =W-f$pB]   6X  NX    DX  Z    FZ *X  Nk 9} I~S Iw  LZ Bv 0m 4Z %q >p %Z \"Z   "
"     4Z @X  JZ MZ&{ 3u z 9~S FZ  Lx MZ(Z :Z \"Z 4Z+] M~Q)Y JY(Y-_ Fr >Z  Lr BZ(Z!y -Y -s /] <^.]&[&[ <Z =~a AX "
" =X \"Y        GjIY FYJj 2p =iIY =u 6Y 'dGY GY1Y 5Y  NX 0X3\\ 8Y FY3Y2Y+Y1Y >m >YJj 8iIX ;Y *u *f :iIY 7_ 6\\7"
"\\ K[0Z 6Z 4~P 2Y  X  Y        ?hC\\ NYMm 8f +m 3s EY1Y 5[ 8Z,Y KYLgJ^$gEh Fs =Y8a Fr @YIi 7m !` 6i G~g#~T FZ 3o"
"Do @Z :Z(Z :Z .s   \"X    EZ    G[    FZ 'p H~U   *Z  X  AY   ,k          :k     2~d       3YLgJ^ 8WEW         "
"   EW IV,X/o/W IW&Z 0Z MZ/[ NZ-Z MZ.Z N[.Z MZ.Z MZ>Z,~T\"t G~T J~T I~S I~S 7Z !Z !Z \"Z :y ?Y-_ Fr 8r 9r :s :r "
"  AXEr :r 8r :s :s -Z 2Z #YIn AkIY BkIY BkIX @jIY BkIY BkIY'l=t Mq :t ;t ;t ;t 3Y  Y  NX  Y *m =X0X >m 3m 5n 5m"
" 3m   6XLm 7iHX @iHX @jIX @jIY 5[ 5YJj -Z      El 3k 2l 3l 4l *X  N\\        5U    ?Y  Y  KR  HQ 1X.Y 9b 9Y1Z 7"
"] )~S                  \"j   &Z   +X@X -h ;X+c!l?\\   6X  Y    DX  Z    FZ +X  Kh 8} I~S Fr  JZ As ,i 3[ $n ;m "
"#Z \"Y        3Z ?X  KZ MZ&x -p Mu 4~S FZ  Js JZ(Z :Z \"Z 4Z*] N~Q)Y JY(Y-_ Dn <Z  Jn @Z([ Nt +Y +o ,\\ ;].]&Z$"
"[ =Z =~a AX  =X \"Y        FhHY FYHf .m ;gHY ;p 3Y %`EY GY1Y 5Y  NX 0X2\\ 9Y FY3Y2Y+Y1Y =j <YHf 5gHX ;Y (q &d 9"
"fGY 6] 5[6\\ KZ.Z 7Z 4~P 2Y  X  Y        >gB[ NYLj 5d (j 0q EY1Y 5Z 7Y+Z LYKdG]\"dBd Bo ;Y7` Dn >YHg 4i  L^ 4e "
"E~g#~T FZ 3oDo @Z :Z(Z :Z ,n    NX    DX    EY    EZ %m G~U   *Z  X  BZ   )e          4e     /~d       3YKeH] 8"
"WEW            FW HV,W.o0X IW'Z /Z MZ/Z LZ.Z MZ/[ MZ.Z MZ/[ MZ>Y+~T p E~T J~T I~S I~S 7Z !Z !Z \"Z :u ;Y,^ Dn 4"
"n 5n 6o 6n   @XBm 5n 4n 6o 6o +Z 2Z #YIl =gGY AhGY AhGX ?hHY @hHY @gGY%i:o Hm 7p 6o 6p 7p 1Y  Y  NX  Y (i ;X0X "
"<i 0j 1j 1j 1j   5XIi 3fGX >fGX >fGX >fGY 4Y 4YHf +Z      Bg /g .g -g /g (X  M[        5T    ?Z !Z  JP   'X.Y 5"
"[ 6Y0Y 7] &~P                   Ne   $Z   +W?X '] 6W)a Mh<\\   7Y !X    CX  Y    EZ +X  Id 6} I~S Cm  HZ =l 'e "
"1Z  i 6h !Z #Z        3Z ?Y  M[ M['s &k Jo .~S FZ  Gm GZ(Z :Z \"Z 4Z)] ~Q)Y JY(Y,^ Bi 9Z  Gl AZ'Z Jm (Y (i )\\ "
";].]'[#Z =Z =~a AX  =X \"Y        DdFY FYFb *h 6cFY 8j 0Y \"YAY GY1Y 5Y  NX 0X1\\ :Y FY3Y2Y+Y1Y ;f :YFb 1cFX ;Y"
" $k  ` 7cFY 6] 5[5Z KZ-[ 8Y 3~P 2Y  X  Y        ;b=X NYJe 0` $e +l BY1Y 4Y 7Y*Y LYIaE[ b@a >k 9Y6_ Ah ;YFc 0e  "
"FZ 2a D~i$~T FZ 3oDo @Z :Z(Z :Z )i    LX    CV    CW    DZ #h D~U   *Z  X -R9Z   #[          *[     *~d       3"
"YIaE\\ 8WEW            GX HV-W-o0W HW'Z 0Z L[0Z LZ/[ LZ0Z LZ/[ LZ0Z LZ?Z+~T Lj B~T J~T I~S I~S 7Z !Z !Z \"Z :o "
"5Y,^ Ai /h 0i 0i 0i   >W?i 1j 0j 1j 1i (Z 2Z #YGh 9cEY ?dEY ?dEX =dFY >dFY >cEY#d5j Ch 1j 1j 1j 1j -Y  Y  NX  Y"
" &e 9X0X :e ,f -f -e ,f   4XFe 0cEX <bEX <bEX <bEY 4Y 4YFb )Z      ?` (a '` '` (a %X          'T               "
"       L{                   K_          0T 4X&[ Ga    AX \"Y      :Y      EX  G_      Ie   #e !_    c /a    EY "
"         EY       Hc        ?e      FZ          +b    Ni   )d    Nc            (X  =Y #Y        A^  J^ %a /]  N"
"c    ;Y      NX          *` 7YD^ ,]CX   1c    ^        /Y    DY  X  Y        8] 1YF] *\\  N` %c  DY 4Y   *YG\\A"
"X J\\;] 9e  A^ =` 7YC] *_    G[                 >a             NU    CZ  N`        9X -T<[                     "
"         LYG]BX 5WEW   %U        HW  NX  MX  GZ                 (d                       +b (b )b )a )b   9V;a "
")c *c *c *c      =a 4_ &^ %^ $^ &_ &_ :_/c <b +c *c *c *c          3_    K_ &` '` '_ &`   1WB_ *] $] $^ %^  NZ "
"4YD^ 'Y      6Q  HQ  GQ  FQ  HQ  LX          &S                                          DQ          )T 4W Q :Q"
"    9Y #X      :Y      EX  ?Q      8R    ?R  @Q    @R  MQ    =Y          DY       @R        -Q      <Z         "
" #R    >RM]   !R    <R             X  <X #Y        ;Q  <Q  GR !Q  @Q    2Y      MX          #R 0Y=Q  Q=X   'Q  "
"  @Q        *Z    DY  X  Y          ;Y  <P  AQ  CQ  ;Y 4Y   *YAQ8P @Q0Q -Y  8X 7Y 3Y=Q  LQ                     "
" JQ                 4Z  IU        3X -W@[                              KYAQ8P 1WEW   $U        IV  MW  LW  FZ  "
"                V                        KQ  GR  HQ  GQ  GQ   0T2Q  HR  GR  HR  HQ      ,Q %Q  GP  GQ  FQ  GQ  "
"GP *P NQ ,V  MQ  GR  HR  HR          #Q    =Q  FQ  HR  HQ  FQ   *V:Q  LQ  GQ  GQ  GQ  GY 3Y=Q !Y               "
"  9X                                                                MT        +X #X      :Y      EX            "
"              5X          BZ                      7Y               7]                     8X  <X #Y            "
"          HY      MX            0Y  'X                 MY    CY  X  Y          ;Y         8Y 4Y   *Y    1Y    E"
"X 3Y                                          CZ  IU        3X -\\I_                              KY  8WEW   $V"
"              %Z                  NU                                    0R                                 #V  "
"                                  )T           <Z 3Y  =Y                 8X                                    "
"                            MT        +X $X      9X      DX                          6Y          AZ NR         "
"            =Z               6\\                     8X  <X #Y                      HY      MX            0Y  '"
"X                 NZ    CY  X  X          :Y         8Y 4Y   *Y    1Y    EX 3Y                                 "
"         CZ  IU        3X -q                              JY  8WEW   #V              &Z                  NV    "
"                                                                  0V                                    (R     "
"      <Y 2Y  =Y                 8X                                                                MT        *X "
"%X      9X      EY                          6X          @[!T                     >Z               5\\          "
"           9X  ;X $Y                      HY      NY            0Y  'X                 NY    BY  X !Y          "
":Y         8Y 4Y   *Y    1Y    EX 3Y                                          CZ  IU        3X -p              "
"                IY  8WEW   #V              &Z                  MV                                              "
"                        0U                                    'P           ;Y 2Y  >Z                 8X        "
"                                                        MT        *X &X      9X      DX                        "
"  5X          ?\\%W                     ?Z               4\\                     :X  ;X $Y                     "
" IZ      NY            0Y  'X                 NY    BZ !X !Y          :Y         8Y 4Y   *Y    1Y    EX 3Y     "
"                                     CZ  IU        3X -o                              HY  8WEW   \"V           "
"   'Z                  LU                                                                      0V              "
"                                  CZ 2Y  >Y                 7X                                                 "
"               MT        )X 'X      9X      DX                          5W          <\\(X                     ?"
"Z               3\\                     ;Y  <X $Y                      IY      MY            0Y  'X            "
"     Z    AY !X !Y          :Y         8Y 4Y   *Y    1Y    EX 3Y                                          CZ  I"
"U        3X -n                              GY  8WEW   \"V              '[3Q                 <V                "
"                                                      0V                                                DY 1Y  "
"?Z                 7X                                                                MT        )X (X      8W   "
"   CX                          6X          ;],[                     AZ               1\\                     <e"
"  GX 2f                      JZ      MY            0Y  'X                 Y    @Z \"X \"Z          :Y         8"
"Y 4Y   *Y    1Y    EX 3Y                                          CZ  IU        3X ,k                          "
"    EY  8WEW   !V              'Z4R                 <V                                                         "
"             0V                                                EZ 1Y  ?Y                 ARGX                  "
"                                              MT        (X )X      8W      DX                          5W      "
"    9^1^                     AZ               0\\                     =e  GX 2f                      KZ      LY"
"            0Y  'X                !Z    @[ #X #Z          9Y         8Y 4Y   *Y    1Y    EX 3Y                 "
"                         CZ  IU        3X )f                              CY  8WEW   !V              '[7T      "
"           ;V                                                                      1V                          "
"                      EY 0Y  ?Y                 FWGW                                                           "
"     LT        'W *X      8W      CX                          5W          8`7`                     A[          "
"     /\\                     >e  GX 2f                      KZ      LY            0Y  'X                !Y    >"
"\\ %X &]          9Y         8Y 4Y   *Y    1Y    EX 3Y                                          CZ  IU        3"
"X $^                              @Y  8WEW   !V              '\\:V                 ;V                          "
"                                            1W                                                GZ 0Y  @Z        "
"         FWHX                                                                LT        'X +W      7W           "
"                      V          5b?c                     A[               -\\                     ?e   !f     "
"                <P2\\      MY            /Y  'X                \"Z    >f /X 0g          9Y         8Y 4Y   *Y  "
"  1Y    EX 3Y                                          CZ  IU        3X                                5Y      "
" NV              &\\=X                 ;V                                                                      "
"1W                                                GY /Y  AZ                 EWHX                               "
"                                 LT        &W ,X      7V                                 V          3~T        "
"             A]               ,\\                     @e   !f                     <R5\\      LY            /Y  "
"'X                #Z    =f /X 0f          8Y         8Y 4Y   *Y    1Y    EX 3Y                                 "
"         CZ  IU        3X                                5Y       NW              '^B[                 <W      "
"                                                                1W                                             "
"   HZ /Y  AZ                 DWIX                                                                LT        &X -"
"W      6U                                 NV          1~P                     B_               *\\             "
"        Ae   !f                     <U:]      LZ            /Y  'X                #Z    <e /X 0e          7Y   "
"      8Y 4Y   *Y    1Y    EX 3Y                                          CZ  IU        3X                      "
"          5Y       X              &aJ_                 <W                                                      "
"                2X                                                IZ .Y  BZ                 CWJY               "
"                                                 LT        %X /X                                               "
"   7|                     Hf               )\\                     Be   !f                     <X?_      N[    "
"        .Y  'X                %[    :d /X 0e          7Y         8Y 4Y   *Y    1Y    EX 3Y                     "
"                     CZ  IU        3X                                5Y      -PDX              %v              "
"   JQDX                                                                      ?QEY                              "
"                  J[ .Y  D\\                 CXLY                                                              "
"  KT                                                             7x                     Fe                     "
"                                          -_Me     %b            .Y  'X                /e    9c /X 0c          "
"5Y         8Y 4Y   *Y    1Y    EX 3Y                                          CZ  IU        3X                 "
"               5Y      -d              $u                 Je                                                   "
"                   ?d                                               $d -Y  Ne                 Ad               "
"                                                 KT                                                            "
" 5s                     Cd                                                               ,v     %b            -"
"Y  'X                0e    6a /X 0b          4Y         8Y 4Y   *Y    1Y    EX 3Y                              "
"            CZ  IU        3X                                5Y      -d              #t                 Jd      "
"                                                                >d                                             "
"  %e -Y  Nd                 @c                                                                                 "
"                                            (m                     @c                                          "
"                     +u     $b            -Y  'X                0d    2^ /X 0_          1Y         8Y 4Y   *Y  "
"  1Y    EX 3Y                                          CZ  IT        2X                                5Y      "
"-c              !q                 Hd                                                                      >c  "
"                                             $d ,Y  Nd                 ?b                                      "
"                                                                                       %g                     ="
"b                                                               *t     #a            ,Y  'X                0d  "
"  ,X /X 0Y          +Y         8Y 4Y   *Y    1Y    EX 3Y                                          CZ          '"
"X                                5Y      -c               Nm                 Fc                                "
"                                      =c                                               $c +Y  Nc               "
"  >a                                                                                                           "
"                   M\\                     8a                                             \"~Y                1"
"r     !`            +Y  'X                0c      1X            1Y         8Y 4Y   *Y    1Y    EX 3Y           "
"                               CZ          &W                                5Y      -b               Lj       "
"          Db                                                                      <b                           "
"                    #b *Y  Nb                 <_                                                               "
"                                                                                    (_                         "
"                     ~Y                1q      _            *Y  'X                0b      0X            1Y     "
"    8Y 4Y   *Y    1Y    EX 3Y                                          CZ                                      "
"     3Y      -`               He                 A`                                                            "
"          :`                                               !a )Y  Na                 :]                        "
"                                                                                                               "
"            ']                                              M~Y                .l      M]            (Y  'X    "
"            0`      .X            1Y         8Y 4Y   *Y    1Y    EX 3Y                                         "
"                                             KY      *Z               B^                 9Z                    "
"                                                  5Z                                                M` (Y  N`  "
"               8Z                                                                                              "
"                                                     %X                                              H~Y       "
"         *d      I[            &Y  'X                0^      ,X            1Y         8Y 4Y   *Y    1Y    EX 3Y"
"                                                                                      KY                       "
"                                                                                                               "
"                         H^ &Y  N]                 3V                                                          "
"                                                                                                               "
"                         B~Y                #X      CU            !X  &X                /Y      (X            1"
"Y         7X 4X   )X    0Y    EX 2X                                                                            "
"          KY                                                                                                   "
"                                                            HZ \"X  MY                                         "
"                                                                                                               "
"                                                            J~Y                                                "
"               9X                                                                                              "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                          3~Y                                  "
"                             9X                                                                                "
"                                                                                                               "
"                                                                                                               "
"                                                                                                               "
"                                                                                        3~Y                    "
"                                           9X                                                                  "
"                                                                                                               "
"                                                                                                               "
"  '" };

// Define a 40x38 'danger' color logo (used by cimg::dialog()).
static const unsigned char logo40x38[4576] = {
177,200,200,200,3,123,123,0,36,200,200,200,1,123,123,0,2,255,255,0,1,189,189,189,1,0,0,0,34,200,200,200,
1,123,123,0,4,255,255,0,1,189,189,189,1,0,0,0,1,123,123,123,32,200,200,200,1,123,123,0,5,255,255,0,1,0,0,
0,2,123,123,123,30,200,200,200,1,123,123,0,6,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,29,200,200,200,
1,123,123,0,7,255,255,0,1,0,0,0,2,123,123,123,28,200,200,200,1,123,123,0,8,255,255,0,1,189,189,189,1,0,0,0,
2,123,123,123,27,200,200,200,1,123,123,0,9,255,255,0,1,0,0,0,2,123,123,123,26,200,200,200,1,123,123,0,10,255,
255,0,1,189,189,189,1,0,0,0,2,123,123,123,25,200,200,200,1,123,123,0,3,255,255,0,1,189,189,189,3,0,0,0,1,189,
189,189,3,255,255,0,1,0,0,0,2,123,123,123,24,200,200,200,1,123,123,0,4,255,255,0,5,0,0,0,3,255,255,0,1,189,
189,189,1,0,0,0,2,123,123,123,23,200,200,200,1,123,123,0,4,255,255,0,5,0,0,0,4,255,255,0,1,0,0,0,2,123,123,123,
22,200,200,200,1,123,123,0,5,255,255,0,5,0,0,0,4,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,21,200,200,200,
1,123,123,0,5,255,255,0,5,0,0,0,5,255,255,0,1,0,0,0,2,123,123,123,20,200,200,200,1,123,123,0,6,255,255,0,5,0,0,
0,5,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,19,200,200,200,1,123,123,0,6,255,255,0,1,123,123,0,3,0,0,0,1,
123,123,0,6,255,255,0,1,0,0,0,2,123,123,123,18,200,200,200,1,123,123,0,7,255,255,0,1,189,189,189,3,0,0,0,1,189,
189,189,6,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,17,200,200,200,1,123,123,0,8,255,255,0,3,0,0,0,8,255,255,
0,1,0,0,0,2,123,123,123,16,200,200,200,1,123,123,0,9,255,255,0,1,123,123,0,1,0,0,0,1,123,123,0,8,255,255,0,1,189,
189,189,1,0,0,0,2,123,123,123,15,200,200,200,1,123,123,0,9,255,255,0,1,189,189,189,1,0,0,0,1,189,189,189,9,255,
255,0,1,0,0,0,2,123,123,123,14,200,200,200,1,123,123,0,11,255,255,0,1,0,0,0,10,255,255,0,1,189,189,189,1,0,0,0,2,
123,123,123,13,200,200,200,1,123,123,0,23,255,255,0,1,0,0,0,2,123,123,123,12,200,200,200,1,123,123,0,11,255,255,0,
1,189,189,189,2,0,0,0,1,189,189,189,9,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,11,200,200,200,1,123,123,0,11,
255,255,0,4,0,0,0,10,255,255,0,1,0,0,0,2,123,123,123,10,200,200,200,1,123,123,0,12,255,255,0,4,0,0,0,10,255,255,0,
1,189,189,189,1,0,0,0,2,123,123,123,9,200,200,200,1,123,123,0,12,255,255,0,1,189,189,189,2,0,0,0,1,189,189,189,11,
255,255,0,1,0,0,0,2,123,123,123,9,200,200,200,1,123,123,0,27,255,255,0,1,0,0,0,3,123,123,123,8,200,200,200,1,123,
123,0,26,255,255,0,1,189,189,189,1,0,0,0,3,123,123,123,9,200,200,200,1,123,123,0,24,255,255,0,1,189,189,189,1,0,0,
0,4,123,123,123,10,200,200,200,1,123,123,0,24,0,0,0,5,123,123,123,12,200,200,200,27,123,123,123,14,200,200,200,25,
123,123,123,86,200,200,200,91,49,124,118,124,71,32,124,95,49,56,114,52,82,121,0 };

//! Get/set default output stream for the \CImg library messages.
/**
       \param file Desired output stream. Set to \c 0 to get the currently used output stream only.
       \return Currently used output stream.
    **/
inline std::FILE* output(std::FILE *file) {
cimg::mutex(1);
static std::FILE *res = cimg::_stderr();
if (file) res = file;
cimg::mutex(1,0);
return res;
}

// Return number of available CPU cores.
inline unsigned int nb_cpus() {
unsigned int res = 1;
#if cimg_OS==2
SYSTEM_INFO sysinfo;
GetSystemInfo(&sysinfo);
res = (unsigned int)sysinfo.dwNumberOfProcessors;
#elif cimg_OS == 1
res = (unsigned int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
return res?res:1U;
}

// Lock/unlock mutex for CImg multi-thread programming.
inline int mutex(const unsigned int n, const int lock_mode) {
switch (lock_mode) {
case 0 : cimg::Mutex_attr().unlock(n); return 0;
case 1 : cimg::Mutex_attr().lock(n); return 0;
default : return cimg::Mutex_attr().trylock(n);
}
}

//! Display a warning message on the default output stream.
/**
       \param format C-string containing the format of the message, as with <tt>std::printf()</tt>.
       \note If configuration macro \c cimg_strict_warnings is set, this function throws a
       \c CImgWarningException instead.
       \warning As the first argument is a format string, it is highly recommended to write
       \code
       cimg::warn("%s",warning_message);
       \endcode
       instead of
       \code
       cimg::warn(warning_message);
       \endcode
       if \c warning_message can be arbitrary, to prevent nasty memory access.
    **/
inline void warn(const char *const format, ...) {
if (cimg::exception_mode()>=1) {
char *const message = new char[16384];
std::va_list ap;
va_start(ap,format);
cimg_vsnprintf(message,16384,format,ap);
va_end(ap);
#ifdef cimg_strict_warnings
throw CImgWarningException(message);
#else
std::fprintf(cimg::output(),"\n%s[CImg] *** Warning ***%s%s\n",cimg::t_red,cimg::t_normal,message);
#endif
delete[] message;
}
}

// Execute an external system command.
/**
       \param command C-string containing the command line to execute.
       \param module_name Module name.
       \return Status value of the executed command, whose meaning is OS-dependent.
       \note This function is similar to <tt>std::system()</tt>
       but it does not open an extra console windows
       on Windows-based systems.
    **/
inline int system(const char *const command, const char *const module_name=0, const bool is_verbose=false) {
cimg::unused(module_name);
#ifdef cimg_no_system_calls
return -1;
#else
if (is_verbose) return std::system(command);
#if cimg_OS==1
const unsigned int l = (unsigned int)std::strlen(command);
if (l) {
char *const ncommand = new char[l + 24];
std::memcpy(ncommand,command,l);
std::strcpy(ncommand + l," >/dev/null 2>&1"); // Make command silent
const int out_val = std::system(ncommand);
delete[] ncommand;
return out_val;
} else return -1;
#elif cimg_OS==2
PROCESS_INFORMATION pi;
STARTUPINFO si;
std::memset(&pi,0,sizeof(PROCESS_INFORMATION));
std::memset(&si,0,sizeof(STARTUPINFO));
GetStartupInfo(&si);
si.cb = sizeof(si);
si.wShowWindow = SW_HIDE;
si.dwFlags |= SW_HIDE | STARTF_USESHOWWINDOW;
const BOOL res = CreateProcess((LPCTSTR)module_name,(LPTSTR)command,0,0,FALSE,0,0,0,&si,&pi);
if (res) {
WaitForSingleObject(pi.hProcess,INFINITE);
CloseHandle(pi.hThread);
CloseHandle(pi.hProcess);
return 0;
} else return std::system(command);
#else
return std::system(command);
#endif
#endif
}

//! Return a reference to a temporary variable of type T.
template<typename T>
inline T& temporary(const T&) {
static T temp;
return temp;
}

//! Exchange values of variables \c a and \c b.
template<typename T>
inline void swap(T& a, T& b) { T t = a; a = b; b = t; }

//! Exchange values of variables (\c a1,\c a2) and (\c b1,\c b2).
template<typename T1, typename T2>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2) {
cimg::swap(a1,b1); cimg::swap(a2,b2);
}

//! Exchange values of variables (\c a1,\c a2,\c a3) and (\c b1,\c b2,\c b3).
template<typename T1, typename T2, typename T3>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3) {
cimg::swap(a1,b1,a2,b2); cimg::swap(a3,b3);
}

//! Exchange values of variables (\c a1,\c a2,...,\c a4) and (\c b1,\c b2,...,\c b4).
template<typename T1, typename T2, typename T3, typename T4>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4) {
cimg::swap(a1,b1,a2,b2,a3,b3); cimg::swap(a4,b4);
}

//! Exchange values of variables (\c a1,\c a2,...,\c a5) and (\c b1,\c b2,...,\c b5).
template<typename T1, typename T2, typename T3, typename T4, typename T5>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5) {
cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4); cimg::swap(a5,b5);
}

//! Exchange values of variables (\c a1,\c a2,...,\c a6) and (\c b1,\c b2,...,\c b6).
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6) {
cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5); cimg::swap(a6,b6);
}

//! Exchange values of variables (\c a1,\c a2,...,\c a7) and (\c b1,\c b2,...,\c b7).
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6,
T7& a7, T7& b7) {
cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6); cimg::swap(a7,b7);
}

//! Exchange values of variables (\c a1,\c a2,...,\c a8) and (\c b1,\c b2,...,\c b8).
template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6,
T7& a7, T7& b7, T8& a8, T8& b8) {
cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7); cimg::swap(a8,b8);
}

//! Return the endianness of the current architecture.
/**
       \return \c false for <i>Little Endian</i> or \c true for <i>Big Endian</i>.
    **/
inline bool endianness() {
const int x = 1;
return ((unsigned char*)&x)[0]?false:true;
}

//! Reverse endianness of all elements in a memory buffer.
/**
       \param[in,out] buffer Memory buffer whose endianness must be reversed.
       \param size Number of buffer elements to reverse.
    **/
template<typename T>
inline void invert_endianness(T* const buffer, const cimg_ulong size) {
if (size) switch (sizeof(T)) {
case 1 : break;
case 2 : {
for (unsigned short *ptr = (unsigned short*)buffer + size; ptr>(unsigned short*)buffer; ) {
const unsigned short val = *(--ptr);
*ptr = (unsigned short)((val>>8) | ((val<<8)));
}
} break;
case 4 : {
for (unsigned int *ptr = (unsigned int*)buffer + size; ptr>(unsigned int*)buffer; ) {
const unsigned int val = *(--ptr);
*ptr = (val>>24) | ((val>>8)&0xff00) | ((val<<8)&0xff0000) | (val<<24);
}
} break;
case 8 : {
const cimg_uint64
m0 = (cimg_uint64)0xff, m1 = m0<<8, m2 = m0<<16, m3 = m0<<24,
m4 = m0<<32, m5 = m0<<40, m6 = m0<<48, m7 = m0<<56;
for (cimg_uint64 *ptr = (cimg_uint64*)buffer + size; ptr>(cimg_uint64*)buffer; ) {
const cimg_uint64 val = *(--ptr);
*ptr =  (((val&m7)>>56) | ((val&m6)>>40) | ((val&m5)>>24) | ((val&m4)>>8) |
((val&m3)<<8) |((val&m2)<<24) | ((val&m1)<<40) | ((val&m0)<<56));
}
} break;
default : {
for (T* ptr = buffer + size; ptr>buffer; ) {
unsigned char *pb = (unsigned char*)(--ptr), *pe = pb + sizeof(T);
for (int i = 0; i<(int)sizeof(T)/2; ++i) swap(*(pb++),*(--pe));
}
}
}
}

//! Reverse endianness of a single variable.
/**
       \param[in,out] a Variable to reverse.
       \return Reference to reversed variable.
    **/
template<typename T>
inline T& invert_endianness(T& a) {
invert_endianness(&a,1);
return a;
}

// Conversion functions to get more precision when trying to store unsigned ints values as floats.
inline unsigned int float2uint(const float f) {
int tmp = 0;
std::memcpy(&tmp,&f,sizeof(float));
if (tmp>=0) return (unsigned int)f;
unsigned int u;
// use memcpy instead of assignment to avoid undesired optimizations by C++-compiler.
std::memcpy(&u,&f,sizeof(float));
return ((u)<<1)>>1; // set sign bit to 0
}

inline float uint2float(const unsigned int u) {
if (u<(1U<<19)) return (float)u;  // Consider safe storage of unsigned int as floats until 19bits (i.e 524287)
float f;
const unsigned int v = u|(1U<<(8*sizeof(unsigned int)-1)); // set sign bit to 1
// use memcpy instead of simple assignment to avoid undesired optimizations by C++-compiler.
std::memcpy(&f,&v,sizeof(float));
return f;
}

//! Return the value of a system timer, with a millisecond precision.
/**
       \note The timer does not necessarily starts from \c 0.
    **/
inline cimg_ulong time() {
#if cimg_OS==1
struct timeval st_time;
gettimeofday(&st_time,0);
return (cimg_ulong)(st_time.tv_usec/1000 + st_time.tv_sec*1000);
#elif cimg_OS==2
SYSTEMTIME st_time;
GetLocalTime(&st_time);
return (cimg_ulong)(st_time.wMilliseconds + 1000*(st_time.wSecond + 60*(st_time.wMinute + 60*st_time.wHour)));
#else
return 0;
#endif
}

// Implement a tic/toc mechanism to display elapsed time of algorithms.
inline cimg_ulong tictoc(const bool is_tic);

//! Start tic/toc timer for time measurement between code instructions.
/**
       \return Current value of the timer (same value as time()).
    **/
inline cimg_ulong tic() {
return cimg::tictoc(true);
}

//! End tic/toc timer and displays elapsed time from last call to tic().
/**
       \return Time elapsed (in ms) since last call to tic().
    **/
inline cimg_ulong toc() {
return cimg::tictoc(false);
}

//! Sleep for a given numbers of milliseconds.
/**
       \param milliseconds Number of milliseconds to wait for.
       \note This function frees the CPU ressources during the sleeping time.
       It can be used to temporize your program properly, without wasting CPU time.
    **/
inline void sleep(const unsigned int milliseconds) {
#if cimg_OS==1
struct timespec tv;
tv.tv_sec = milliseconds/1000;
tv.tv_nsec = (milliseconds%1000)*1000000;
nanosleep(&tv,0);
#elif cimg_OS==2
Sleep(milliseconds);
#else
cimg::unused(milliseconds);
#endif
}

inline unsigned int wait(const unsigned int milliseconds, cimg_ulong *const p_timer) {
if (!*p_timer) *p_timer = cimg::time();
const cimg_ulong current_time = cimg::time();
if (current_time>=*p_timer + milliseconds) { *p_timer = current_time; return 0; }
const unsigned int time_diff = (unsigned int)(*p_timer + milliseconds - current_time);
*p_timer = current_time + time_diff;
cimg::sleep(time_diff);
return time_diff;
}

//! Wait for a given number of milliseconds since the last call to wait().
/**
       \param milliseconds Number of milliseconds to wait for.
       \return Number of milliseconds elapsed since the last call to wait().
       \note Same as sleep() with a waiting time computed with regard to the last call
       of wait(). It may be used to temporize your program properly, without wasting CPU time.
    **/
inline cimg_long wait(const unsigned int milliseconds) {
cimg::mutex(3);
static cimg_ulong timer = cimg::time();
cimg::mutex(3,0);
return cimg::wait(milliseconds,&timer);
}

// Custom random number generator (allow re-entrance).
inline cimg_ulong& rng() { // Used as a shared global number for rng
static cimg_ulong rng = 0xB16B00B5U;
return rng;
}

inline unsigned int _rand(cimg_ulong *const p_rng) {
*p_rng = *p_rng*1103515245 + 12345U;
return (unsigned int)*p_rng;
}

inline unsigned int _rand() {
cimg::mutex(4);
const unsigned int res = cimg::_rand(&cimg::rng());
cimg::mutex(4,0);
return res;
}

inline void srand(cimg_ulong *const p_rng) {
#if cimg_OS==1
*p_rng = cimg::time() + (cimg_ulong)getpid();
#elif cimg_OS==2
*p_rng = cimg::time() + (cimg_ulong)_getpid();
#endif
}

inline void srand() {
cimg::mutex(4);
cimg::srand(&cimg::rng());
cimg::mutex(4,0);
}

inline void srand(const cimg_ulong seed) {
cimg::mutex(4);
cimg::rng() = seed;
cimg::mutex(4,0);
}

inline double rand(const double val_min, const double val_max, cimg_ulong *const p_rng) {
const double val = cimg::_rand(p_rng)/(double)~0U;
return val_min + (val_max - val_min)*val;
}

inline double rand(const double val_min, const double val_max) {
cimg::mutex(4);
const double res = cimg::rand(val_min,val_max,&cimg::rng());
cimg::mutex(4,0);
return res;
}

inline double rand(const double val_max, cimg_ulong *const p_rng) {
const double val = cimg::_rand(p_rng)/(double)~0U;
return val_max*val;
}

inline double rand(const double val_max=1) {
cimg::mutex(4);
const double res = cimg::rand(val_max,&cimg::rng());
cimg::mutex(4,0);
return res;
}

inline double grand(cimg_ulong *const p_rng) {
double x1, w;
do {
const double x2 = cimg::rand(-1,1,p_rng);
x1 = cimg::rand(-1,1,p_rng);
w = x1*x1 + x2*x2;
} while (w<=0 || w>=1.);
return x1*std::sqrt((-2*std::log(w))/w);
}

inline double grand() {
cimg::mutex(4);
const double res = cimg::grand(&cimg::rng());
cimg::mutex(4,0);
return res;
}

inline unsigned int prand(const double z, cimg_ulong *const p_rng) {
if (z<=1.e-10) return 0;
if (z>100) return (unsigned int)((std::sqrt(z) * cimg::grand(p_rng)) + z);
unsigned int k = 0;
const double y = std::exp(-z);
for (double s = 1.; s>=y; ++k) s*=cimg::rand(1,p_rng);
return k - 1;
}

inline unsigned int prand(const double z) {
cimg::mutex(4);
const unsigned int res = cimg::prand(z,&cimg::rng());
cimg::mutex(4,0);
return res;
}

//! Cut (i.e. clamp) value in specified interval.
template<typename T, typename t>
inline T cut(const T& val, const t& val_min, const t& val_max) {
return val<val_min?(T)val_min:val>val_max?(T)val_max:val;
}

//! Bitwise-rotate value on the left.
template<typename T>
inline T rol(const T& a, const unsigned int n=1) {
return n?(T)((a<<n)|(a>>((sizeof(T)<<3) - n))):a;
}

inline float rol(const float a, const unsigned int n=1) {
return (float)rol((int)a,n);
}

inline double rol(const double a, const unsigned int n=1) {
return (double)rol((cimg_long)a,n);
}

inline double rol(const long double a, const unsigned int n=1) {
return (double)rol((cimg_long)a,n);
}

#ifdef cimg_use_half
inline half rol(const half a, const unsigned int n=1) {
return (half)rol((int)a,n);
}
#endif

//! Bitwise-rotate value on the right.
template<typename T>
inline T ror(const T& a, const unsigned int n=1) {
return n?(T)((a>>n)|(a<<((sizeof(T)<<3) - n))):a;
}

inline float ror(const float a, const unsigned int n=1) {
return (float)ror((int)a,n);
}

inline double ror(const double a, const unsigned int n=1) {
return (double)ror((cimg_long)a,n);
}

inline double ror(const long double a, const unsigned int n=1) {
return (double)ror((cimg_long)a,n);
}

#ifdef cimg_use_half
inline half ror(const half a, const unsigned int n=1) {
return (half)ror((int)a,n);
}
#endif

//! Return absolute value of a value.
template<typename T>
inline T abs(const T& a) {
return a>=0?a:-a;
}
inline bool abs(const bool a) {
return a;
}
inline int abs(const unsigned char a) {
return (int)a;
}
inline int abs(const unsigned short a) {
return (int)a;
}
inline int abs(const unsigned int a) {
return (int)a;
}
inline int abs(const int a) {
return std::abs(a);
}
inline cimg_int64 abs(const cimg_uint64 a) {
return (cimg_int64)a;
}
inline double abs(const double a) {
return std::fabs(a);
}
inline float abs(const float a) {
return (float)std::fabs((double)a);
}

//! Return hyperbolic arcosine of a value.
inline double acosh(const double x) {
#if cimg_use_cpp11==1 && !defined(_MSC_VER)
return std::acosh(x);
#else
return std::log(x + std::sqrt(x*x - 1));
#endif
}

//! Return hyperbolic arcsine of a value.
inline double asinh(const double x) {
#if cimg_use_cpp11==1 && !defined(_MSC_VER)
return std::asinh(x);
#else
return std::log(x + std::sqrt(x*x + 1));
#endif
}

//! Return hyperbolic arctangent of a value.
inline double atanh(const double x) {
#if cimg_use_cpp11==1 && !defined(_MSC_VER)
return std::atanh(x);
#else
return 0.5*std::log((1. + x)/(1. - x));
#endif
}

//! Return the sinc of a given value.
inline double sinc(const double x) {
return x?std::sin(x)/x:1;
}

//! Return base-2 logarithm of a value.
inline double log2(const double x) {
#if cimg_use_cpp11==1 && !defined(_MSC_VER)
return std::log2(x);
#else
const double base2 = std::log(2.);
return std::log(x)/base2;
#endif
}

//! Return square of a value.
template<typename T>
inline T sqr(const T& val) {
return val*val;
}

//! Return cubic root of a value.
template<typename T>
inline double cbrt(const T& x) {
#if cimg_use_cpp11==1
return std::cbrt(x);
#else
return x>=0?std::pow((double)x,1./3):-std::pow(-(double)x,1./3);
#endif
}

template<typename T>
inline T pow3(const T& val) {
return val*val*val;
}
template<typename T>
inline T pow4(const T& val) {
return val*val*val*val;
}

//! Return the minimum between three values.
template<typename t>
inline t min(const t& a, const t& b, const t& c) {
return std::min(std::min(a,b),c);
}

//! Return the minimum between four values.
template<typename t>
inline t min(const t& a, const t& b, const t& c, const t& d) {
return std::min(std::min(a,b),std::min(c,d));
}

//! Return the maximum between three values.
template<typename t>
inline t max(const t& a, const t& b, const t& c) {
return std::max(std::max(a,b),c);
}

//! Return the maximum between four values.
template<typename t>
inline t max(const t& a, const t& b, const t& c, const t& d) {
return std::max(std::max(a,b),std::max(c,d));
}

//! Return the sign of a value.
template<typename T>
inline T sign(const T& x) {
return (T)(cimg::type<T>::is_nan(x)?0:x<0?-1:x>0);
}

//! Return the nearest power of 2 higher than given value.
template<typename T>
inline cimg_ulong nearest_pow2(const T& x) {
cimg_ulong i = 1;
while (x>i) i<<=1;
return i;
}

//! Return the modulo of a value.
/**
       \param x Input value.
       \param m Modulo value.
       \note This modulo function accepts negative and floating-points modulo numbers, as well as variables of any type.
    **/
template<typename T>
inline T mod(const T& x, const T& m) {
const double dx = (double)x, dm = (double)m;
return (T)(dx - dm * std::floor(dx / dm));
}
inline int mod(const bool x, const bool m) {
return m?(x?1:0):0;
}
inline int mod(const unsigned char x, const unsigned char m) {
return x%m;
}
inline int mod(const char x, const char m) {
#if defined(CHAR_MAX) && CHAR_MAX==255
return x%m;
#else
return x>=0?x%m:(x%m?m + x%m:0);
#endif
}
inline int mod(const unsigned short x, const unsigned short m) {
return x%m;
}
inline int mod(const short x, const short m) {
return x>=0?x%m:(x%m?m + x%m:0);
}
inline int mod(const unsigned int x, const unsigned int m) {
return (int)(x%m);
}
inline int mod(const int x, const int m) {
return x>=0?x%m:(x%m?m + x%m:0);
}
inline cimg_int64 mod(const cimg_uint64 x, const cimg_uint64 m) {
return x%m;
}
inline cimg_int64 mod(const cimg_int64 x, const cimg_int64 m) {
return x>=0?x%m:(x%m?m + x%m:0);
}

//! Return the min-mod of two values.
/**
       \note <i>minmod(\p a,\p b)</i> is defined to be:
       - <i>minmod(\p a,\p b) = min(\p a,\p b)</i>, if \p a and \p b have the same sign.
       - <i>minmod(\p a,\p b) = 0</i>, if \p a and \p b have different signs.
    **/
template<typename T>
inline T minmod(const T& a, const T& b) {
return a*b<=0?0:(a>0?(a<b?a:b):(a<b?b:a));
}

template<typename T>
inline T round(const T& x) {
return (T)std::floor((_cimg_Tfloat)x + 0.5f);
}

//! Return rounded value.
/**
       \param x Value to be rounded.
       \param y Rounding precision.
       \param rounding_type Type of rounding operation (\c 0 = nearest, \c -1 = backward, \c 1 = forward).
       \return Rounded value, having the same type as input value \c x.
    **/
template<typename T>
inline T round(const T& x, const double y, const int rounding_type=0) {
if (y<=0) return x;
if (y==1) switch (rounding_type) {
case 0 : return cimg::round(x);
case 1 : return (T)std::ceil((_cimg_Tfloat)x);
default : return (T)std::floor((_cimg_Tfloat)x);
}
const double sx = (double)x/y, floor = std::floor(sx), delta =  sx - floor;
return (T)(y*(rounding_type<0?floor:rounding_type>0?std::ceil(sx):delta<0.5?floor:std::ceil(sx)));
}

// Code to compute fast median from 2,3,5,7,9,13,25 and 49 values.
// (contribution by RawTherapee: http://rawtherapee.com/).
template<typename T>
inline T median(T val0, T val1) {
return (val0 + val1)/2;
}

template<typename T>
inline T median(T val0, T val1, T val2) {
return std::max(std::min(val0,val1),std::min(val2,std::max(val0,val1)));
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4) {
T tmp = std::min(val0,val1);
val1 = std::max(val0,val1); val0 = tmp; tmp = std::min(val3,val4); val4 = std::max(val3,val4);
val3 = std::max(val0,tmp);  val1 = std::min(val1,val4); tmp = std::min(val1,val2); val2 = std::max(val1,val2);
val1 = tmp; tmp = std::min(val2,val3);
return std::max(val1,tmp);
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4, T val5, T val6) {
T tmp = std::min(val0,val5);
val5 = std::max(val0,val5); val0 = tmp; tmp = std::min(val0,val3); val3 = std::max(val0,val3); val0 = tmp;
tmp = std::min(val1,val6); val6 = std::max(val1,val6); val1 = tmp; tmp = std::min(val2,val4);
val4 = std::max(val2,val4); val2 = tmp; val1 = std::max(val0,val1); tmp = std::min(val3,val5);
val5 = std::max(val3,val5); val3 = tmp; tmp = std::min(val2,val6); val6 = std::max(val2,val6);
val3 = std::max(tmp,val3); val3 = std::min(val3,val6); tmp = std::min(val4,val5); val4 = std::max(val1,tmp);
tmp = std::min(val1,tmp); val3 = std::max(tmp,val3);
return std::min(val3,val4);
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4, T val5, T val6, T val7, T val8) {
T tmp = std::min(val1,val2);
val2 = std::max(val1,val2); val1 = tmp; tmp = std::min(val4,val5);
val5 = std::max(val4,val5); val4 = tmp; tmp = std::min(val7,val8);
val8 = std::max(val7,val8); val7 = tmp; tmp = std::min(val0,val1);
val1 = std::max(val0,val1); val0 = tmp; tmp = std::min(val3,val4);
val4 = std::max(val3,val4); val3 = tmp; tmp = std::min(val6,val7);
val7 = std::max(val6,val7); val6 = tmp; tmp = std::min(val1,val2);
val2 = std::max(val1,val2); val1 = tmp; tmp = std::min(val4,val5);
val5 = std::max(val4,val5); val4 = tmp; tmp = std::min(val7,val8);
val8 = std::max(val7,val8); val3 = std::max(val0,val3); val5 = std::min(val5,val8);
val7 = std::max(val4,tmp); tmp = std::min(val4,tmp); val6 = std::max(val3,val6);
val4 = std::max(val1,tmp); val2 = std::min(val2,val5); val4 = std::min(val4,val7);
tmp = std::min(val4,val2); val2 = std::max(val4,val2); val4 = std::max(val6,tmp);
return std::min(val4,val2);
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4, T val5, T val6, T val7, T val8, T val9, T val10, T val11,
T val12) {
T tmp = std::min(val1,val7);
val7 = std::max(val1,val7); val1 = tmp; tmp = std::min(val9,val11); val11 = std::max(val9,val11); val9 = tmp;
tmp = std::min(val3,val4);  val4 = std::max(val3,val4); val3 = tmp; tmp = std::min(val5,val8);
val8 = std::max(val5,val8); val5 = tmp; tmp = std::min(val0,val12); val12 = std::max(val0,val12);
val0 = tmp; tmp = std::min(val2,val6); val6 = std::max(val2,val6); val2 = tmp; tmp = std::min(val0,val1);
val1 = std::max(val0,val1); val0 = tmp; tmp = std::min(val2,val3); val3 = std::max(val2,val3); val2 = tmp;
tmp = std::min(val4,val6);  val6 = std::max(val4,val6); val4 = tmp; tmp = std::min(val8,val11);
val11 = std::max(val8,val11); val8 = tmp; tmp = std::min(val7,val12); val12 = std::max(val7,val12); val7 = tmp;
tmp = std::min(val5,val9); val9 = std::max(val5,val9); val5 = tmp; tmp = std::min(val0,val2);
val2 = std::max(val0,val2); val0 = tmp; tmp = std::min(val3,val7); val7 = std::max(val3,val7); val3 = tmp;
tmp = std::min(val10,val11); val11 = std::max(val10,val11); val10 = tmp; tmp = std::min(val1,val4);
val4 = std::max(val1,val4); val1 = tmp; tmp = std::min(val6,val12); val12 = std::max(val6,val12); val6 = tmp;
tmp = std::min(val7,val8); val8 = std::max(val7,val8); val7 = tmp; val11 = std::min(val11,val12);
tmp = std::min(val4,val9); val9 = std::max(val4,val9); val4 = tmp; tmp = std::min(val6,val10);
val10 = std::max(val6,val10); val6 = tmp; tmp = std::min(val3,val4); val4 = std::max(val3,val4); val3 = tmp;
tmp = std::min(val5,val6); val6 = std::max(val5,val6); val5 = tmp; val8 = std::min(val8,val9);
val10 = std::min(val10,val11); tmp = std::min(val1,val7); val7 = std::max(val1,val7); val1 = tmp;
tmp = std::min(val2,val6); val6 = std::max(val2,val6); val2 = tmp; val3 = std::max(val1,val3);
tmp = std::min(val4,val7); val7 = std::max(val4,val7); val4 = tmp; val8 = std::min(val8,val10);
val5 = std::max(val0,val5); val5 = std::max(val2,val5); tmp = std::min(val6,val8); val8 = std::max(val6,val8);
val5 = std::max(val3,val5); val7 = std::min(val7,val8); val6 = std::max(val4,tmp); tmp = std::min(val4,tmp);
val5 = std::max(tmp,val5); val6 = std::min(val6,val7);
return std::max(val5,val6);
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4,
T val5, T val6, T val7, T val8, T val9,
T val10, T val11, T val12, T val13, T val14,
T val15, T val16, T val17, T val18, T val19,
T val20, T val21, T val22, T val23, T val24) {
T tmp = std::min(val0,val1);
val1 = std::max(val0,val1); val0 = tmp; tmp = std::min(val3,val4); val4 = std::max(val3,val4);
val3 = tmp; tmp = std::min(val2,val4); val4 = std::max(val2,val4); val2 = std::min(tmp,val3);
val3 = std::max(tmp,val3); tmp = std::min(val6,val7); val7 = std::max(val6,val7); val6 = tmp;
tmp = std::min(val5,val7); val7 = std::max(val5,val7); val5 = std::min(tmp,val6); val6 = std::max(tmp,val6);
tmp = std::min(val9,val10); val10 = std::max(val9,val10); val9 = tmp; tmp = std::min(val8,val10);
val10 = std::max(val8,val10); val8 = std::min(tmp,val9); val9 = std::max(tmp,val9);
tmp = std::min(val12,val13); val13 = std::max(val12,val13); val12 = tmp; tmp = std::min(val11,val13);
val13 = std::max(val11,val13); val11 = std::min(tmp,val12); val12 = std::max(tmp,val12);
tmp = std::min(val15,val16); val16 = std::max(val15,val16); val15 = tmp; tmp = std::min(val14,val16);
val16 = std::max(val14,val16); val14 = std::min(tmp,val15); val15 = std::max(tmp,val15);
tmp = std::min(val18,val19); val19 = std::max(val18,val19); val18 = tmp; tmp = std::min(val17,val19);
val19 = std::max(val17,val19); val17 = std::min(tmp,val18); val18 = std::max(tmp,val18);
tmp = std::min(val21,val22); val22 = std::max(val21,val22); val21 = tmp; tmp = std::min(val20,val22);
val22 = std::max(val20,val22); val20 = std::min(tmp,val21); val21 = std::max(tmp,val21);
tmp = std::min(val23,val24); val24 = std::max(val23,val24); val23 = tmp; tmp = std::min(val2,val5);
val5 = std::max(val2,val5); val2 = tmp; tmp = std::min(val3,val6); val6 = std::max(val3,val6); val3 = tmp;
tmp = std::min(val0,val6); val6 = std::max(val0,val6); val0 = std::min(tmp,val3); val3 = std::max(tmp,val3);
tmp = std::min(val4,val7); val7 = std::max(val4,val7); val4 = tmp; tmp = std::min(val1,val7);
val7 = std::max(val1,val7); val1 = std::min(tmp,val4); val4 = std::max(tmp,val4); tmp = std::min(val11,val14);
val14 = std::max(val11,val14); val11 = tmp; tmp = std::min(val8,val14); val14 = std::max(val8,val14);
val8 = std::min(tmp,val11); val11 = std::max(tmp,val11); tmp = std::min(val12,val15);
val15 = std::max(val12,val15); val12 = tmp; tmp = std::min(val9,val15); val15 = std::max(val9,val15);
val9 = std::min(tmp,val12); val12 = std::max(tmp,val12); tmp = std::min(val13,val16);
val16 = std::max(val13,val16); val13 = tmp; tmp = std::min(val10,val16); val16 = std::max(val10,val16);
val10 = std::min(tmp,val13); val13 = std::max(tmp,val13); tmp = std::min(val20,val23);
val23 = std::max(val20,val23); val20 = tmp; tmp = std::min(val17,val23); val23 = std::max(val17,val23);
val17 = std::min(tmp,val20); val20 = std::max(tmp,val20); tmp = std::min(val21,val24);
val24 = std::max(val21,val24); val21 = tmp; tmp = std::min(val18,val24); val24 = std::max(val18,val24);
val18 = std::min(tmp,val21); val21 = std::max(tmp,val21); tmp = std::min(val19,val22);
val22 = std::max(val19,val22); val19 = tmp; val17 = std::max(val8,val17); tmp = std::min(val9,val18);
val18 = std::max(val9,val18); val9 = tmp; tmp = std::min(val0,val18); val18 = std::max(val0,val18);
val9 = std::max(tmp,val9); tmp = std::min(val10,val19); val19 = std::max(val10,val19); val10 = tmp;
tmp = std::min(val1,val19); val19 = std::max(val1,val19); val1 = std::min(tmp,val10);
val10 = std::max(tmp,val10); tmp = std::min(val11,val20); val20 = std::max(val11,val20); val11 = tmp;
tmp = std::min(val2,val20); val20 = std::max(val2,val20); val11 = std::max(tmp,val11);
tmp = std::min(val12,val21); val21 = std::max(val12,val21); val12 = tmp; tmp = std::min(val3,val21);
val21 = std::max(val3,val21); val3 = std::min(tmp,val12); val12 = std::max(tmp,val12);
tmp = std::min(val13,val22); val22 = std::max(val13,val22); val4 = std::min(val4,val22);
val13 = std::max(val4,tmp); tmp = std::min(val4,tmp); val4 = tmp; tmp = std::min(val14,val23);
val23 = std::max(val14,val23); val14 = tmp; tmp = std::min(val5,val23); val23 = std::max(val5,val23);
val5 = std::min(tmp,val14); val14 = std::max(tmp,val14); tmp = std::min(val15,val24);
val24 = std::max(val15,val24); val15 = tmp; val6 = std::min(val6,val24); tmp = std::min(val6,val15);
val15 = std::max(val6,val15); val6 = tmp; tmp = std::min(val7,val16); val7 = std::min(tmp,val19);
tmp = std::min(val13,val21); val15 = std::min(val15,val23); tmp = std::min(val7,tmp);
val7 = std::min(tmp,val15); val9 = std::max(val1,val9); val11 = std::max(val3,val11);
val17 = std::max(val5,val17); val17 = std::max(val11,val17); val17 = std::max(val9,val17);
tmp = std::min(val4,val10); val10 = std::max(val4,val10); val4 = tmp; tmp = std::min(val6,val12);
val12 = std::max(val6,val12); val6 = tmp; tmp = std::min(val7,val14); val14 = std::max(val7,val14);
val7 = tmp; tmp = std::min(val4,val6); val6 = std::max(val4,val6); val7 = std::max(tmp,val7);
tmp = std::min(val12,val14); val14 = std::max(val12,val14); val12 = tmp; val10 = std::min(val10,val14);
tmp = std::min(val6,val7); val7 = std::max(val6,val7); val6 = tmp; tmp = std::min(val10,val12);
val12 = std::max(val10,val12); val10 = std::max(val6,tmp); tmp = std::min(val6,tmp);
val17 = std::max(tmp,val17); tmp = std::min(val12,val17); val17 = std::max(val12,val17); val12 = tmp;
val7 = std::min(val7,val17); tmp = std::min(val7,val10); val10 = std::max(val7,val10); val7 = tmp;
tmp = std::min(val12,val18); val18 = std::max(val12,val18); val12 = std::max(val7,tmp);
val10 = std::min(val10,val18); tmp = std::min(val12,val20); val20 = std::max(val12,val20); val12 = tmp;
tmp = std::min(val10,val20);
return std::max(tmp,val12);
}

template<typename T>
inline T median(T val0, T val1, T val2, T val3, T val4, T val5, T val6,
T val7, T val8, T val9, T val10, T val11, T val12, T val13,
T val14, T val15, T val16, T val17, T val18, T val19, T val20,
T val21, T val22, T val23, T val24, T val25, T val26, T val27,
T val28, T val29, T val30, T val31, T val32, T val33, T val34,
T val35, T val36, T val37, T val38, T val39, T val40, T val41,
T val42, T val43, T val44, T val45, T val46, T val47, T val48) {
T tmp = std::min(val0,val32);
val32 = std::max(val0,val32); val0 = tmp; tmp = std::min(val1,val33); val33 = std::max(val1,val33); val1 = tmp;
tmp = std::min(val2,val34); val34 = std::max(val2,val34); val2 = tmp; tmp = std::min(val3,val35);
val35 = std::max(val3,val35); val3 = tmp; tmp = std::min(val4,val36); val36 = std::max(val4,val36); val4 = tmp;
tmp = std::min(val5,val37); val37 = std::max(val5,val37); val5 = tmp; tmp = std::min(val6,val38);
val38 = std::max(val6,val38); val6 = tmp; tmp = std::min(val7,val39); val39 = std::max(val7,val39); val7 = tmp;
tmp = std::min(val8,val40); val40 = std::max(val8,val40); val8 = tmp; tmp = std::min(val9,val41);
val41 = std::max(val9,val41); val9 = tmp; tmp = std::min(val10,val42); val42 = std::max(val10,val42);
val10 = tmp; tmp = std::min(val11,val43); val43 = std::max(val11,val43); val11 = tmp;
tmp = std::min(val12,val44); val44 = std::max(val12,val44); val12 = tmp; tmp = std::min(val13,val45);
val45 = std::max(val13,val45); val13 = tmp; tmp = std::min(val14,val46); val46 = std::max(val14,val46);
val14 = tmp; tmp = std::min(val15,val47); val47 = std::max(val15,val47); val15 = tmp;
tmp = std::min(val16,val48); val48 = std::max(val16,val48); val16 = tmp; tmp = std::min(val0,val16);
val16 = std::max(val0,val16); val0 = tmp; tmp = std::min(val1,val17); val17 = std::max(val1,val17);
val1 = tmp; tmp = std::min(val2,val18); val18 = std::max(val2,val18); val2 = tmp; tmp = std::min(val3,val19);
val19 = std::max(val3,val19); val3 = tmp; tmp = std::min(val4,val20); val20 = std::max(val4,val20); val4 = tmp;
tmp = std::min(val5,val21); val21 = std::max(val5,val21); val5 = tmp; tmp = std::min(val6,val22);
val22 = std::max(val6,val22); val6 = tmp; tmp = std::min(val7,val23); val23 = std::max(val7,val23); val7 = tmp;
tmp = std::min(val8,val24); val24 = std::max(val8,val24); val8 = tmp; tmp = std::min(val9,val25);
val25 = std::max(val9,val25); val9 = tmp; tmp = std::min(val10,val26); val26 = std::max(val10,val26);
val10 = tmp; tmp = std::min(val11,val27); val27 = std::max(val11,val27); val11 = tmp;
tmp = std::min(val12,val28); val28 = std::max(val12,val28); val12 = tmp; tmp = std::min(val13,val29);
val29 = std::max(val13,val29); val13 = tmp; tmp = std::min(val14,val30); val30 = std::max(val14,val30);
val14 = tmp; tmp = std::min(val15,val31); val31 = std::max(val15,val31); val15 = tmp;
tmp = std::min(val32,val48); val48 = std::max(val32,val48); val32 = tmp; tmp = std::min(val16,val32);
val32 = std::max(val16,val32); val16 = tmp; tmp = std::min(val17,val33); val33 = std::max(val17,val33);
val17 = tmp; tmp = std::min(val18,val34); val34 = std::max(val18,val34); val18 = tmp;
tmp = std::min(val19,val35); val35 = std::max(val19,val35); val19 = tmp; tmp = std::min(val20,val36);
val36 = std::max(val20,val36); val20 = tmp; tmp = std::min(val21,val37); val37 = std::max(val21,val37);
val21 = tmp; tmp = std::min(val22,val38); val38 = std::max(val22,val38); val22 = tmp;
tmp = std::min(val23,val39); val39 = std::max(val23,val39); val23 = tmp; tmp = std::min(val24,val40);
val40 = std::max(val24,val40); val24 = tmp; tmp = std::min(val25,val41); val41 = std::max(val25,val41);
val25 = tmp; tmp = std::min(val26,val42); val42 = std::max(val26,val42); val26 = tmp;
tmp = std::min(val27,val43); val43 = std::max(val27,val43); val27 = tmp; tmp = std::min(val28,val44);
val44 = std::max(val28,val44); val28 = tmp; tmp = std::min(val29,val45); val45 = std::max(val29,val45);
val29 = tmp; tmp = std::min(val30,val46); val46 = std::max(val30,val46); val30 = tmp;
tmp = std::min(val31,val47); val47 = std::max(val31,val47); val31 = tmp; tmp = std::min(val0,val8);
val8 = std::max(val0,val8); val0 = tmp; tmp = std::min(val1,val9); val9 = std::max(val1,val9); val1 = tmp;
tmp = std::min(val2,val10); val10 = std::max(val2,val10); val2 = tmp; tmp = std::min(val3,val11);
val11 = std::max(val3,val11); val3 = tmp; tmp = std::min(val4,val12); val12 = std::max(val4,val12); val4 = tmp;
tmp = std::min(val5,val13); val13 = std::max(val5,val13); val5 = tmp; tmp = std::min(val6,val14);
val14 = std::max(val6,val14); val6 = tmp; tmp = std::min(val7,val15); val15 = std::max(val7,val15); val7 = tmp;
tmp = std::min(val16,val24); val24 = std::max(val16,val24); val16 = tmp; tmp = std::min(val17,val25);
val25 = std::max(val17,val25); val17 = tmp; tmp = std::min(val18,val26); val26 = std::max(val18,val26);
val18 = tmp; tmp = std::min(val19,val27); val27 = std::max(val19,val27); val19 = tmp;
tmp = std::min(val20,val28); val28 = std::max(val20,val28); val20 = tmp; tmp = std::min(val21,val29);
val29 = std::max(val21,val29); val21 = tmp; tmp = std::min(val22,val30); val30 = std::max(val22,val30);
val22 = tmp; tmp = std::min(val23,val31); val31 = std::max(val23,val31); val23 = tmp;
tmp = std::min(val32,val40); val40 = std::max(val32,val40); val32 = tmp; tmp = std::min(val33,val41);
val41 = std::max(val33,val41); val33 = tmp; tmp = std::min(val34,val42); val42 = std::max(val34,val42);
val34 = tmp; tmp = std::min(val35,val43); val43 = std::max(val35,val43); val35 = tmp;
tmp = std::min(val36,val44); val44 = std::max(val36,val44); val36 = tmp; tmp = std::min(val37,val45);
val45 = std::max(val37,val45); val37 = tmp; tmp = std::min(val38,val46); val46 = std::max(val38,val46);
val38 = tmp; tmp = std::min(val39,val47); val47 = std::max(val39,val47); val39 = tmp;
tmp = std::min(val8,val32); val32 = std::max(val8,val32); val8 = tmp; tmp = std::min(val9,val33);
val33 = std::max(val9,val33); val9 = tmp; tmp = std::min(val10,val34); val34 = std::max(val10,val34);
val10 = tmp; tmp = std::min(val11,val35); val35 = std::max(val11,val35); val11 = tmp;
tmp = std::min(val12,val36); val36 = std::max(val12,val36); val12 = tmp; tmp = std::min(val13,val37);
val37 = std::max(val13,val37); val13 = tmp; tmp = std::min(val14,val38); val38 = std::max(val14,val38);
val14 = tmp; tmp = std::min(val15,val39); val39 = std::max(val15,val39); val15 = tmp;
tmp = std::min(val24,val48); val48 = std::max(val24,val48); val24 = tmp; tmp = std::min(val8,val16);
val16 = std::max(val8,val16); val8 = tmp; tmp = std::min(val9,val17); val17 = std::max(val9,val17);
val9 = tmp; tmp = std::min(val10,val18); val18 = std::max(val10,val18); val10 = tmp;
tmp = std::min(val11,val19); val19 = std::max(val11,val19); val11 = tmp; tmp = std::min(val12,val20);
val20 = std::max(val12,val20); val12 = tmp; tmp = std::min(val13,val21); val21 = std::max(val13,val21);
val13 = tmp; tmp = std::min(val14,val22); val22 = std::max(val14,val22); val14 = tmp;
tmp = std::min(val15,val23); val23 = std::max(val15,val23); val15 = tmp; tmp = std::min(val24,val32);
val32 = std::max(val24,val32); val24 = tmp; tmp = std::min(val25,val33); val33 = std::max(val25,val33);
val25 = tmp; tmp = std::min(val26,val34); val34 = std::max(val26,val34); val26 = tmp;
tmp = std::min(val27,val35); val35 = std::max(val27,val35); val27 = tmp; tmp = std::min(val28,val36);
val36 = std::max(val28,val36); val28 = tmp; tmp = std::min(val29,val37); val37 = std::max(val29,val37);
val29 = tmp; tmp = std::min(val30,val38); val38 = std::max(val30,val38); val30 = tmp;
tmp = std::min(val31,val39); val39 = std::max(val31,val39); val31 = tmp; tmp = std::min(val40,val48);
val48 = std::max(val40,val48); val40 = tmp; tmp = std::min(val0,val4); val4 = std::max(val0,val4);
val0 = tmp; tmp = std::min(val1,val5); val5 = std::max(val1,val5); val1 = tmp; tmp = std::min(val2,val6);
val6 = std::max(val2,val6); val2 = tmp; tmp = std::min(val3,val7); val7 = std::max(val3,val7); val3 = tmp;
tmp = std::min(val8,val12); val12 = std::max(val8,val12); val8 = tmp; tmp = std::min(val9,val13);
val13 = std::max(val9,val13); val9 = tmp; tmp = std::min(val10,val14); val14 = std::max(val10,val14);
val10 = tmp; tmp = std::min(val11,val15); val15 = std::max(val11,val15); val11 = tmp;
tmp = std::min(val16,val20); val20 = std::max(val16,val20); val16 = tmp; tmp = std::min(val17,val21);
val21 = std::max(val17,val21); val17 = tmp; tmp = std::min(val18,val22); val22 = std::max(val18,val22);
val18 = tmp; tmp = std::min(val19,val23); val23 = std::max(val19,val23); val19 = tmp;
tmp = std::min(val24,val28); val28 = std::max(val24,val28); val24 = tmp; tmp = std::min(val25,val29);
val29 = std::max(val25,val29); val25 = tmp; tmp = std::min(val26,val30); val30 = std::max(val26,val30);
val26 = tmp; tmp = std::min(val27,val31); val31 = std::max(val27,val31); val27 = tmp;
tmp = std::min(val32,val36); val36 = std::max(val32,val36); val32 = tmp; tmp = std::min(val33,val37);
val37 = std::max(val33,val37); val33 = tmp; tmp = std::min(val34,val38); val38 = std::max(val34,val38);
val34 = tmp; tmp = std::min(val35,val39); val39 = std::max(val35,val39); val35 = tmp;
tmp = std::min(val40,val44); val44 = std::max(val40,val44); val40 = tmp; tmp = std::min(val41,val45);
val45 = std::max(val41,val45); val41 = tmp; tmp = std::min(val42,val46); val46 = std::max(val42,val46);
val42 = tmp; tmp = std::min(val43,val47); val47 = std::max(val43,val47); val43 = tmp;
tmp = std::min(val4,val32); val32 = std::max(val4,val32); val4 = tmp; tmp = std::min(val5,val33);
val33 = std::max(val5,val33); val5 = tmp; tmp = std::min(val6,val34); val34 = std::max(val6,val34);
val6 = tmp; tmp = std::min(val7,val35); val35 = std::max(val7,val35); val7 = tmp;
tmp = std::min(val12,val40); val40 = std::max(val12,val40); val12 = tmp; tmp = std::min(val13,val41);
val41 = std::max(val13,val41); val13 = tmp; tmp = std::min(val14,val42); val42 = std::max(val14,val42);
val14 = tmp; tmp = std::min(val15,val43); val43 = std::max(val15,val43); val15 = tmp;
tmp = std::min(val20,val48); val48 = std::max(val20,val48); val20 = tmp; tmp = std::min(val4,val16);
val16 = std::max(val4,val16); val4 = tmp; tmp = std::min(val5,val17); val17 = std::max(val5,val17);
val5 = tmp; tmp = std::min(val6,val18); val18 = std::max(val6,val18); val6 = tmp;
tmp = std::min(val7,val19); val19 = std::max(val7,val19); val7 = tmp; tmp = std::min(val12,val24);
val24 = std::max(val12,val24); val12 = tmp; tmp = std::min(val13,val25); val25 = std::max(val13,val25);
val13 = tmp; tmp = std::min(val14,val26); val26 = std::max(val14,val26); val14 = tmp;
tmp = std::min(val15,val27); val27 = std::max(val15,val27); val15 = tmp; tmp = std::min(val20,val32);
val32 = std::max(val20,val32); val20 = tmp; tmp = std::min(val21,val33); val33 = std::max(val21,val33);
val21 = tmp; tmp = std::min(val22,val34); val34 = std::max(val22,val34); val22 = tmp;
tmp = std::min(val23,val35); val35 = std::max(val23,val35); val23 = tmp; tmp = std::min(val28,val40);
val40 = std::max(val28,val40); val28 = tmp; tmp = std::min(val29,val41); val41 = std::max(val29,val41);
val29 = tmp; tmp = std::min(val30,val42); val42 = std::max(val30,val42); val30 = tmp;
tmp = std::min(val31,val43); val43 = std::max(val31,val43); val31 = tmp; tmp = std::min(val36,val48);
val48 = std::max(val36,val48); val36 = tmp; tmp = std::min(val4,val8); val8 = std::max(val4,val8);
val4 = tmp; tmp = std::min(val5,val9); val9 = std::max(val5,val9); val5 = tmp; tmp = std::min(val6,val10);
val10 = std::max(val6,val10); val6 = tmp; tmp = std::min(val7,val11); val11 = std::max(val7,val11); val7 = tmp;
tmp = std::min(val12,val16); val16 = std::max(val12,val16); val12 = tmp; tmp = std::min(val13,val17);
val17 = std::max(val13,val17); val13 = tmp; tmp = std::min(val14,val18); val18 = std::max(val14,val18);
val14 = tmp; tmp = std::min(val15,val19); val19 = std::max(val15,val19); val15 = tmp;
tmp = std::min(val20,val24); val24 = std::max(val20,val24); val20 = tmp; tmp = std::min(val21,val25);
val25 = std::max(val21,val25); val21 = tmp; tmp = std::min(val22,val26); val26 = std::max(val22,val26);
val22 = tmp; tmp = std::min(val23,val27); val27 = std::max(val23,val27); val23 = tmp;
tmp = std::min(val28,val32); val32 = std::max(val28,val32); val28 = tmp; tmp = std::min(val29,val33);
val33 = std::max(val29,val33); val29 = tmp; tmp = std::min(val30,val34); val34 = std::max(val30,val34);
val30 = tmp; tmp = std::min(val31,val35); val35 = std::max(val31,val35); val31 = tmp;
tmp = std::min(val36,val40); val40 = std::max(val36,val40); val36 = tmp; tmp = std::min(val37,val41);
val41 = std::max(val37,val41); val37 = tmp; tmp = std::min(val38,val42); val42 = std::max(val38,val42);
val38 = tmp; tmp = std::min(val39,val43); val43 = std::max(val39,val43); val39 = tmp;
tmp = std::min(val44,val48); val48 = std::max(val44,val48); val44 = tmp; tmp = std::min(val0,val2);
val2 = std::max(val0,val2); val0 = tmp; tmp = std::min(val1,val3); val3 = std::max(val1,val3); val1 = tmp;
tmp = std::min(val4,val6); val6 = std::max(val4,val6); val4 = tmp; tmp = std::min(val5,val7);
val7 = std::max(val5,val7); val5 = tmp; tmp = std::min(val8,val10); val10 = std::max(val8,val10); val8 = tmp;
tmp = std::min(val9,val11); val11 = std::max(val9,val11); val9 = tmp; tmp = std::min(val12,val14);
val14 = std::max(val12,val14); val12 = tmp; tmp = std::min(val13,val15); val15 = std::max(val13,val15);
val13 = tmp; tmp = std::min(val16,val18); val18 = std::max(val16,val18); val16 = tmp;
tmp = std::min(val17,val19); val19 = std::max(val17,val19); val17 = tmp; tmp = std::min(val20,val22);
val22 = std::max(val20,val22); val20 = tmp; tmp = std::min(val21,val23); val23 = std::max(val21,val23);
val21 = tmp; tmp = std::min(val24,val26); val26 = std::max(val24,val26); val24 = tmp;
tmp = std::min(val25,val27); val27 = std::max(val25,val27); val25 = tmp; tmp = std::min(val28,val30);
val30 = std::max(val28,val30); val28 = tmp; tmp = std::min(val29,val31); val31 = std::max(val29,val31);
val29 = tmp; tmp = std::min(val32,val34); val34 = std::max(val32,val34); val32 = tmp;
tmp = std::min(val33,val35); val35 = std::max(val33,val35); val33 = tmp; tmp = std::min(val36,val38);
val38 = std::max(val36,val38); val36 = tmp; tmp = std::min(val37,val39); val39 = std::max(val37,val39);
val37 = tmp; tmp = std::min(val40,val42); val42 = std::max(val40,val42); val40 = tmp;
tmp = std::min(val41,val43); val43 = std::max(val41,val43); val41 = tmp; tmp = std::min(val44,val46);
val46 = std::max(val44,val46); val44 = tmp; tmp = std::min(val45,val47); val47 = std::max(val45,val47);
val45 = tmp; tmp = std::min(val2,val32); val32 = std::max(val2,val32); val2 = tmp; tmp = std::min(val3,val33);
val33 = std::max(val3,val33); val3 = tmp; tmp = std::min(val6,val36); val36 = std::max(val6,val36); val6 = tmp;
tmp = std::min(val7,val37); val37 = std::max(val7,val37); val7 = tmp; tmp = std::min(val10,val40);
val40 = std::max(val10,val40); val10 = tmp; tmp = std::min(val11,val41); val41 = std::max(val11,val41);
val11 = tmp; tmp = std::min(val14,val44); val44 = std::max(val14,val44); val14 = tmp;
tmp = std::min(val15,val45); val45 = std::max(val15,val45); val15 = tmp; tmp = std::min(val18,val48);
val48 = std::max(val18,val48); val18 = tmp; tmp = std::min(val2,val16); val16 = std::max(val2,val16);
val2 = tmp; tmp = std::min(val3,val17); val17 = std::max(val3,val17); val3 = tmp;
tmp = std::min(val6,val20); val20 = std::max(val6,val20); val6 = tmp; tmp = std::min(val7,val21);
val21 = std::max(val7,val21); val7 = tmp; tmp = std::min(val10,val24); val24 = std::max(val10,val24);
val10 = tmp; tmp = std::min(val11,val25); val25 = std::max(val11,val25); val11 = tmp;
tmp = std::min(val14,val28); val28 = std::max(val14,val28); val14 = tmp; tmp = std::min(val15,val29);
val29 = std::max(val15,val29); val15 = tmp; tmp = std::min(val18,val32); val32 = std::max(val18,val32);
val18 = tmp; tmp = std::min(val19,val33); val33 = std::max(val19,val33); val19 = tmp;
tmp = std::min(val22,val36); val36 = std::max(val22,val36); val22 = tmp; tmp = std::min(val23,val37);
val37 = std::max(val23,val37); val23 = tmp; tmp = std::min(val26,val40); val40 = std::max(val26,val40);
val26 = tmp; tmp = std::min(val27,val41); val41 = std::max(val27,val41); val27 = tmp;
tmp = std::min(val30,val44); val44 = std::max(val30,val44); val30 = tmp; tmp = std::min(val31,val45);
val45 = std::max(val31,val45); val31 = tmp; tmp = std::min(val34,val48); val48 = std::max(val34,val48);
val34 = tmp; tmp = std::min(val2,val8); val8 = std::max(val2,val8); val2 = tmp; tmp = std::min(val3,val9);
val9 = std::max(val3,val9); val3 = tmp; tmp = std::min(val6,val12); val12 = std::max(val6,val12); val6 = tmp;
tmp = std::min(val7,val13); val13 = std::max(val7,val13); val7 = tmp; tmp = std::min(val10,val16);
val16 = std::max(val10,val16); val10 = tmp; tmp = std::min(val11,val17); val17 = std::max(val11,val17);
val11 = tmp; tmp = std::min(val14,val20); val20 = std::max(val14,val20); val14 = tmp;
tmp = std::min(val15,val21); val21 = std::max(val15,val21); val15 = tmp; tmp = std::min(val18,val24);
val24 = std::max(val18,val24); val18 = tmp; tmp = std::min(val19,val25); val25 = std::max(val19,val25);
val19 = tmp; tmp = std::min(val22,val28); val28 = std::max(val22,val28); val22 = tmp;
tmp = std::min(val23,val29); val29 = std::max(val23,val29); val23 = tmp; tmp = std::min(val26,val32);
val32 = std::max(val26,val32); val26 = tmp; tmp = std::min(val27,val33); val33 = std::max(val27,val33);
val27 = tmp; tmp = std::min(val30,val36); val36 = std::max(val30,val36); val30 = tmp;
tmp = std::min(val31,val37); val37 = std::max(val31,val37); val31 = tmp; tmp = std::min(val34,val40);
val40 = std::max(val34,val40); val34 = tmp; tmp = std::min(val35,val41); val41 = std::max(val35,val41);
val35 = tmp; tmp = std::min(val38,val44); val44 = std::max(val38,val44); val38 = tmp;
tmp = std::min(val39,val45); val45 = std::max(val39,val45); val39 = tmp; tmp = std::min(val42,val48);
val48 = std::max(val42,val48); val42 = tmp; tmp = std::min(val2,val4); val4 = std::max(val2,val4);
val2 = tmp; tmp = std::min(val3,val5); val5 = std::max(val3,val5); val3 = tmp; tmp = std::min(val6,val8);
val8 = std::max(val6,val8); val6 = tmp; tmp = std::min(val7,val9); val9 = std::max(val7,val9); val7 = tmp;
tmp = std::min(val10,val12); val12 = std::max(val10,val12); val10 = tmp; tmp = std::min(val11,val13);
val13 = std::max(val11,val13); val11 = tmp; tmp = std::min(val14,val16); val16 = std::max(val14,val16);
val14 = tmp; tmp = std::min(val15,val17); val17 = std::max(val15,val17); val15 = tmp;
tmp = std::min(val18,val20); val20 = std::max(val18,val20); val18 = tmp; tmp = std::min(val19,val21);
val21 = std::max(val19,val21); val19 = tmp; tmp = std::min(val22,val24); val24 = std::max(val22,val24);
val22 = tmp; tmp = std::min(val23,val25); val25 = std::max(val23,val25); val23 = tmp;
tmp = std::min(val26,val28); val28 = std::max(val26,val28); val26 = tmp; tmp = std::min(val27,val29);
val29 = std::max(val27,val29); val27 = tmp; tmp = std::min(val30,val32); val32 = std::max(val30,val32);
val30 = tmp; tmp = std::min(val31,val33); val33 = std::max(val31,val33); val31 = tmp;
tmp = std::min(val34,val36); val36 = std::max(val34,val36); val34 = tmp; tmp = std::min(val35,val37);
val37 = std::max(val35,val37); val35 = tmp; tmp = std::min(val38,val40); val40 = std::max(val38,val40);
val38 = tmp; tmp = std::min(val39,val41); val41 = std::max(val39,val41); val39 = tmp;
tmp = std::min(val42,val44); val44 = std::max(val42,val44); val42 = tmp; tmp = std::min(val43,val45);
val45 = std::max(val43,val45); val43 = tmp; tmp = std::min(val46,val48); val48 = std::max(val46,val48);
val46 = tmp; val1 = std::max(val0,val1); val3 = std::max(val2,val3); val5 = std::max(val4,val5);
val7 = std::max(val6,val7); val9 = std::max(val8,val9); val11 = std::max(val10,val11);
val13 = std::max(val12,val13); val15 = std::max(val14,val15); val17 = std::max(val16,val17);
val19 = std::max(val18,val19); val21 = std::max(val20,val21); val23 = std::max(val22,val23);
val24 = std::min(val24,val25); val26 = std::min(val26,val27); val28 = std::min(val28,val29);
val30 = std::min(val30,val31); val32 = std::min(val32,val33); val34 = std::min(val34,val35);
val36 = std::min(val36,val37); val38 = std::min(val38,val39); val40 = std::min(val40,val41);
val42 = std::min(val42,val43); val44 = std::min(val44,val45); val46 = std::min(val46,val47);
val32 = std::max(val1,val32); val34 = std::max(val3,val34); val36 = std::max(val5,val36);
val38 = std::max(val7,val38); val9 = std::min(val9,val40); val11 = std::min(val11,val42);
val13 = std::min(val13,val44); val15 = std::min(val15,val46); val17 = std::min(val17,val48);
val24 = std::max(val9,val24); val26 = std::max(val11,val26); val28 = std::max(val13,val28);
val30 = std::max(val15,val30); val17 = std::min(val17,val32); val19 = std::min(val19,val34);
val21 = std::min(val21,val36); val23 = std::min(val23,val38); val24 = std::max(val17,val24);
val26 = std::max(val19,val26); val21 = std::min(val21,val28); val23 = std::min(val23,val30);
val24 = std::max(val21,val24); val23 = std::min(val23,val26);
return std::max(val23,val24);
}

//! Return sqrt(x^2 + y^2).
template<typename T>
inline T hypot(const T x, const T y) {
return std::sqrt(x*x + y*y);
}

template<typename T>
inline T hypot(const T x, const T y, const T z) {
return std::sqrt(x*x + y*y + z*z);
}

template<typename T>
inline T _hypot(const T x, const T y) { // Slower but more precise version
T nx = cimg::abs(x), ny = cimg::abs(y), t;
if (nx<ny) { t = nx; nx = ny; } else t = ny;
if (nx>0) { t/=nx; return nx*std::sqrt(1 + t*t); }
return 0;
}

//! Return the factorial of n
inline double factorial(const int n) {
if (n<0) return cimg::type<double>::nan();
if (n<2) return 1;
double res = 2;
for (int i = 3; i<=n; ++i) res*=i;
return res;
}

//! Return the number of permutations of k objects in a set of n objects.
inline double permutations(const int k, const int n, const bool with_order) {
if (n<0 || k<0) return cimg::type<double>::nan();
if (k>n) return 0;
double res = 1;
for (int i = n; i>=n - k + 1; --i) res*=i;
return with_order?res:res/cimg::factorial(k);
}

inline double _fibonacci(int exp) {
double
base = (1 + std::sqrt(5.))/2,
result = 1/std::sqrt(5.);
while (exp) {
if (exp&1) result*=base;
exp>>=1;
base*=base;
}
return result;
}

//! Calculate fibonacci number.
// (Precise up to n = 78, less precise for n>78).
inline double fibonacci(const int n) {
if (n<0) return cimg::type<double>::nan();
if (n<3) return 1;
if (n<11) {
cimg_uint64 fn1 = 1, fn2 = 1, fn = 0;
for (int i = 3; i<=n; ++i) { fn = fn1 + fn2; fn2 = fn1; fn1 = fn; }
return (double)fn;
}
if (n<75) // precise up to n = 74, faster than the integer calculation above for n>10
return (double)((cimg_uint64)(_fibonacci(n) + 0.5));

if (n<94) { // precise up to n = 78, less precise for n>78 up to n = 93, overflows for n>93
cimg_uint64
fn1 = (cimg_uint64)1304969544928657ULL,
fn2 = (cimg_uint64)806515533049393ULL,
fn = 0;
for (int i = 75; i<=n; ++i) { fn = fn1 + fn2; fn2 = fn1; fn1 = fn; }
return (double)fn;
}
return _fibonacci(n); // Not precise, but better than the wrong overflowing calculation
}

//! Calculate greatest common divisor.
inline long gcd(long a, long b) {
while (a) { const long c = a; a = b%a; b = c; }
return b;
}

//! Convert Ascii character to lower case.
inline char lowercase(const char x) {
return (char)((x<'A'||x>'Z')?x:x - 'A' + 'a');
}
inline double lowercase(const double x) {
return (double)((x<'A'||x>'Z')?x:x - 'A' + 'a');
}

//! Convert C-string to lower case.
inline void lowercase(char *const str) {
if (str) for (char *ptr = str; *ptr; ++ptr) *ptr = lowercase(*ptr);
}

//! Convert Ascii character to upper case.
inline char uppercase(const char x) {
return (char)((x<'a'||x>'z')?x:x - 'a' + 'A');
}

inline double uppercase(const double x) {
return (double)((x<'a'||x>'z')?x:x - 'a' + 'A');
}

//! Convert C-string to upper case.
inline void uppercase(char *const str) {
if (str) for (char *ptr = str; *ptr; ++ptr) *ptr = uppercase(*ptr);
}

//! Return \c true if input character is blank (space, tab, or non-printable character).
inline bool is_blank(const char c) {
return c>=0 && c<=' ';
}

//! Read value in a C-string.
/**
       \param str C-string containing the float value to read.
       \return Read value.
       \note Same as <tt>std::atof()</tt> extended to manage the retrieval of fractions from C-strings,
       as in <em>"1/2"</em>.
    **/
inline double atof(const char *const str) {
double x = 0, y = 1;
return str && cimg_sscanf(str,"%lf/%lf",&x,&y)>0?x/y:0;
}

//! Compare the first \p l characters of two C-strings, ignoring the case.
/**
       \param str1 C-string.
       \param str2 C-string.
       \param l Number of characters to compare.
       \return \c 0 if the two strings are equal, something else otherwise.
       \note This function has to be defined since it is not provided by all C++-compilers (not ANSI).
    **/
inline int strncasecmp(const char *const str1, const char *const str2, const int l) {
if (!l) return 0;
if (!str1) return str2?-1:0;
const char *nstr1 = str1, *nstr2 = str2;
int k, diff = 0; for (k = 0; k<l && !(diff = lowercase(*nstr1) - lowercase(*nstr2)); ++k) { ++nstr1; ++nstr2; }
return k!=l?diff:0;
}

//! Compare two C-strings, ignoring the case.
/**
       \param str1 C-string.
       \param str2 C-string.
       \return \c 0 if the two strings are equal, something else otherwise.
       \note This function has to be defined since it is not provided by all C++-compilers (not ANSI).
    **/
inline int strcasecmp(const char *const str1, const char *const str2) {
if (!str1) return str2?-1:0;
const int
l1 = (int)std::strlen(str1),
l2 = (int)std::strlen(str2);
return cimg::strncasecmp(str1,str2,1 + (l1<l2?l1:l2));
}

//! Ellipsize a string.
/**
       \param str C-string.
       \param l Max number of characters.
       \param is_ending Tell if the dots are placed at the end or at the center of the ellipsized string.
    **/
inline char *strellipsize(char *const str, const unsigned int l=64,
const bool is_ending=true) {
if (!str) return str;
const unsigned int nl = l<5?5:l, ls = (unsigned int)std::strlen(str);
if (ls<=nl) return str;
if (is_ending) std::strcpy(str + nl - 5,"(...)");
else {
const unsigned int ll = (nl - 5)/2 + 1 - (nl%2), lr = nl - ll - 5;
std::strcpy(str + ll,"(...)");
std::memmove(str + ll + 5,str + ls - lr,lr);
}
str[nl] = 0;
return str;
}

//! Ellipsize a string.
/**
       \param str C-string.
       \param res output C-string.
       \param l Max number of characters.
       \param is_ending Tell if the dots are placed at the end or at the center of the ellipsized string.
    **/
inline char *strellipsize(const char *const str, char *const res, const unsigned int l=64,
const bool is_ending=true) {
const unsigned int nl = l<5?5:l, ls = (unsigned int)std::strlen(str);
if (ls<=nl) { std::strcpy(res,str); return res; }
if (is_ending) {
std::strncpy(res,str,nl - 5);
std::strcpy(res + nl -5,"(...)");
} else {
const unsigned int ll = (nl - 5)/2 + 1 - (nl%2), lr = nl - ll - 5;
std::strncpy(res,str,ll);
std::strcpy(res + ll,"(...)");
std::strncpy(res + ll + 5,str + ls - lr,lr);
}
res[nl] = 0;
return res;
}

//! Remove delimiters on the start and/or end of a C-string.
/**
       \param[in,out] str C-string to work with (modified at output).
       \param delimiter Delimiter character code to remove.
       \param is_symmetric Tells if the removal is done only if delimiters are symmetric
       (both at the beginning and the end of \c s).
       \param is_iterative Tells if the removal is done if several iterations are possible.
       \return \c true if delimiters have been removed, \c false otherwise.
   **/
inline bool strpare(char *const str, const char delimiter,
const bool is_symmetric, const bool is_iterative) {
if (!str) return false;
const int l = (int)std::strlen(str);
int p, q;
if (is_symmetric) for (p = 0, q = l - 1; p<q && str[p]==delimiter && str[q]==delimiter; ) {
--q; ++p; if (!is_iterative) break;
} else {
for (p = 0; p<l && str[p]==delimiter; ) { ++p; if (!is_iterative) break; }
for (q = l - 1; q>p && str[q]==delimiter; ) { --q; if (!is_iterative) break; }
}
const int n = q - p + 1;
if (n!=l) { std::memmove(str,str + p,(unsigned int)n); str[n] = 0; return true; }
return false;
}

//! Remove white spaces on the start and/or end of a C-string.
inline bool strpare(char *const str, const bool is_symmetric, const bool is_iterative) {
if (!str) return false;
const int l = (int)std::strlen(str);
int p, q;
if (is_symmetric) for (p = 0, q = l - 1; p<q && is_blank(str[p]) && is_blank(str[q]); ) {
--q; ++p; if (!is_iterative) break;
} else {
for (p = 0; p<l && is_blank(str[p]); ) { ++p; if (!is_iterative) break; }
for (q = l - 1; q>p && is_blank(str[q]); ) { --q; if (!is_iterative) break; }
}
const int n = q - p + 1;
if (n!=l) { std::memmove(str,str + p,(unsigned int)n); str[n] = 0; return true; }
return false;
}

//! Replace reserved characters (for Windows filename) by another character.
/**
       \param[in,out] str C-string to work with (modified at output).
       \param[in] c Replacement character.
    **/
inline void strwindows_reserved(char *const str, const char c='_') {
for (char *s = str; *s; ++s) {
const char i = *s;
if (i=='<' || i=='>' || i==':' || i=='\"' || i=='/' || i=='\\' || i=='|' || i=='?' || i=='*') *s = c;
}
}

//! Replace escape sequences in C-strings by their binary Ascii values.
/**
       \param[in,out] str C-string to work with (modified at output).
    **/
inline void strunescape(char *const str) {
#define cimg_strunescape(ci,co) case ci : *nd = co; ++ns; break;
unsigned int val = 0;
for (char *ns = str, *nd = str; *ns || (bool)(*nd=0); ++nd) if (*ns=='\\') switch (*(++ns)) {
cimg_strunescape('a','\a');
cimg_strunescape('b','\b');
cimg_strunescape('e',0x1B);
cimg_strunescape('f','\f');
cimg_strunescape('n','\n');
cimg_strunescape('r','\r');
cimg_strunescape('t','\t');
cimg_strunescape('v','\v');
cimg_strunescape('\\','\\');
cimg_strunescape('\'','\'');
cimg_strunescape('\"','\"');
cimg_strunescape('\?','\?');
case 0 : *nd = 0; break;
case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' :
cimg_sscanf(ns,"%o",&val); while (*ns>='0' && *ns<='7') ++ns;
*nd = (char)val; break;
case 'x' :
cimg_sscanf(++ns,"%x",&val);
while ((*ns>='0' && *ns<='9') || (*ns>='a' && *ns<='f') || (*ns>='A' && *ns<='F')) ++ns;
*nd = (char)val; break;
default : *nd = *(ns++);
} else *nd = *(ns++);
}

// Return a temporary string describing the size of a memory buffer.
inline const char *strbuffersize(const cimg_ulong size);

// Return string that identifies the running OS.
inline const char *stros() {
#if defined(linux) || defined(__linux) || defined(__linux__)
static const char *const str = "Linux";
#elif defined(sun) || defined(__sun)
static const char *const str = "Sun OS";
#elif defined(BSD) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined (__DragonFly__)
static const char *const str = "BSD";
#elif defined(sgi) || defined(__sgi)
static const char *const str = "Irix";
#elif defined(__MACOSX__) || defined(__APPLE__)
static const char *const str = "Mac OS";
#elif defined(unix) || defined(__unix) || defined(__unix__)
static const char *const str = "Generic Unix";
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) || \
  defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
static const char *const str = "Windows";
#else
const char
*const _str1 = std::getenv("OSTYPE"),
*const _str2 = _str1?_str1:std::getenv("OS"),
*const str = _str2?_str2:"Unknown OS";
#endif
return str;
}

//! Return the basename of a filename.
inline const char* basename(const char *const s, const char separator=cimg_file_separator)  {
const char *p = 0, *np = s;
while (np>=s && (p=np)) np = std::strchr(np,separator) + 1;
return p;
}

// Return a random filename.
inline const char* filenamerand() {
cimg::mutex(6);
static char randomid[9];
for (unsigned int k = 0; k<8; ++k) {
const int v = (int)cimg::rand(65535)%3;
randomid[k] = (char)(v==0?('0' + ((int)cimg::rand(65535)%10)):
(v==1?('a' + ((int)cimg::rand(65535)%26)):
('A' + ((int)cimg::rand(65535)%26))));
}
cimg::mutex(6,0);
return randomid;
}

// Convert filename as a Windows-style filename (short path name).
inline void winformat_string(char *const str) {
if (str && *str) {
#if cimg_OS==2
char *const nstr = new char[MAX_PATH];
if (GetShortPathNameA(str,nstr,MAX_PATH)) std::strcpy(str,nstr);
delete[] nstr;
#endif
}
}

// Open a file (similar to std:: fopen(), but with wide character support on Windows).
inline std::FILE *std_fopen(const char *const path, const char *const mode);


//! Open a file.
/**
       \param path Path of the filename to open.
       \param mode C-string describing the opening mode.
       \return Opened file.
       \note Same as <tt>std::fopen()</tt> but throw a \c CImgIOException when
       the specified file cannot be opened, instead of returning \c 0.
    **/
inline std::FILE *fopen(const char *const path, const char *const mode) {
if (!path)
throw CImgArgumentException("cimg::fopen(): Specified file path is (null).");
if (!mode)
throw CImgArgumentException("cimg::fopen(): File '%s', specified mode is (null).",
path);
std::FILE *res = 0;
if (*path=='-' && (!path[1] || path[1]=='.')) {
res = (*mode=='r')?cimg::_stdin():cimg::_stdout();
#if cimg_OS==2
if (*mode && mode[1]=='b') { // Force stdin/stdout to be in binary mode
#ifdef __BORLANDC__
if (setmode(_fileno(res),0x8000)==-1) res = 0;
#else
if (_setmode(_fileno(res),0x8000)==-1) res = 0;
#endif
}
#endif
} else res = cimg::std_fopen(path,mode);
if (!res) throw CImgIOException("cimg::fopen(): Failed to open file '%s' with mode '%s'.",
path,mode);
return res;
}

//! Close a file.
/**
       \param file File to close.
       \return \c 0 if file has been closed properly, something else otherwise.
       \note Same as <tt>std::fclose()</tt> but display a warning message if
       the file has not been closed properly.
    **/
inline int fclose(std::FILE *file) {
if (!file) { warn("cimg::fclose(): Specified file is (null)."); return 0; }
if (file==cimg::_stdin(false) || file==cimg::_stdout(false)) return 0;
const int errn = std::fclose(file);
if (errn!=0) warn("cimg::fclose(): Error code %d returned during file closing.",
errn);
return errn;
}

//! Version of 'fseek()' that supports >=64bits offsets everywhere (for Windows).
inline int fseek(FILE *stream, cimg_long offset, int origin) {
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
return _fseeki64(stream,(__int64)offset,origin);
#else
return std::fseek(stream,offset,origin);
#endif
}

//! Version of 'ftell()' that supports >=64bits offsets everywhere (for Windows).
inline cimg_long ftell(FILE *stream) {
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
return (cimg_long)_ftelli64(stream);
#else
return (cimg_long)std::ftell(stream);
#endif
}

//! Check if a path is a directory.
/**
       \param path Specified path to test.
    **/
inline bool is_directory(const char *const path) {
if (!path || !*path) return false;
#if cimg_OS==1
struct stat st_buf;
return (!stat(path,&st_buf) && S_ISDIR(st_buf.st_mode));
#elif cimg_OS==2
const unsigned int res = (unsigned int)GetFileAttributesA(path);
return res==INVALID_FILE_ATTRIBUTES?false:(res&16);
#else
return false;
#endif
}

//! Check if a path is a file.
/**
       \param path Specified path to test.
    **/
inline bool is_file(const char *const path) {
if (!path || !*path) return false;
std::FILE *const file = cimg::std_fopen(path,"rb");
if (!file) return false;
cimg::fclose(file);
return !is_directory(path);
}

//! Get file size.
/**
       \param filename Specified filename to get size from.
       \return File size or '-1' if file does not exist.
    **/
inline cimg_int64 fsize(const char *const filename) {
std::FILE *const file = cimg::std_fopen(filename,"rb");
if (!file) return (cimg_int64)-1;
std::fseek(file,0,SEEK_END);
const cimg_int64 siz = (cimg_int64)std::ftell(file);
cimg::fclose(file);
return siz;
}

//! Get last write time of a given file or directory (multiple-attributes version).
/**
       \param path Specified path to get attributes from.
       \param[in,out] attr Type of requested time attributes.
                      Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
                      Replaced by read attributes after return (or -1 if an error occured).
       \param nb_attr Number of attributes to read/write.
       \return Latest read attribute.
    **/
template<typename T>
inline int fdate(const char *const path, T *attr, const unsigned int nb_attr) {
#define _cimg_fdate_err() for (unsigned int i = 0; i<nb_attr; ++i) attr[i] = (T)-1
int res = -1;
if (!path || !*path) { _cimg_fdate_err(); return -1; }
cimg::mutex(6);
#if cimg_OS==2
HANDLE file = CreateFileA(path,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
if (file!=INVALID_HANDLE_VALUE) {
FILETIME _ft;
SYSTEMTIME ft;
if (GetFileTime(file,0,0,&_ft) && FileTimeToSystemTime(&_ft,&ft)) {
for (unsigned int i = 0; i<nb_attr; ++i) {
res = (int)(attr[i]==0?ft.wYear:attr[i]==1?ft.wMonth:attr[i]==2?ft.wDay:
attr[i]==3?ft.wDayOfWeek:attr[i]==4?ft.wHour:attr[i]==5?ft.wMinute:
attr[i]==6?ft.wSecond:-1);
attr[i] = (T)res;
}
} else _cimg_fdate_err();
CloseHandle(file);
} else _cimg_fdate_err();
#elif cimg_OS==1
struct stat st_buf;
if (!stat(path,&st_buf)) {
const time_t _ft = st_buf.st_mtime;
const struct tm& ft = *std::localtime(&_ft);
for (unsigned int i = 0; i<nb_attr; ++i) {
res = (int)(attr[i]==0?ft.tm_year + 1900:attr[i]==1?ft.tm_mon + 1:attr[i]==2?ft.tm_mday:
attr[i]==3?ft.tm_wday:attr[i]==4?ft.tm_hour:attr[i]==5?ft.tm_min:
attr[i]==6?ft.tm_sec:-1);
attr[i] = (T)res;
}
} else _cimg_fdate_err();
#endif
cimg::mutex(6,0);
return res;
}

//! Get last write time of a given file or directory (single-attribute version).
/**
       \param path Specified path to get attributes from.
       \param attr Type of requested time attributes.
                   Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
       \return Specified attribute or -1 if an error occured.
    **/
inline int fdate(const char *const path, unsigned int attr) {
int out = (int)attr;
return fdate(path,&out,1);
}

//! Get current local time (multiple-attributes version).
/**
       \param[in,out] attr Type of requested time attributes.
                           Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
                           Replaced by read attributes after return (or -1 if an error occured).
       \param nb_attr Number of attributes to read/write.
       \return Latest read attribute.
    **/
template<typename T>
inline int date(T *attr, const unsigned int nb_attr) {
int res = -1;
cimg::mutex(6);
#if cimg_OS==2
SYSTEMTIME st;
GetLocalTime(&st);
for (unsigned int i = 0; i<nb_attr; ++i) {
res = (int)(attr[i]==0?st.wYear:attr[i]==1?st.wMonth:attr[i]==2?st.wDay:
attr[i]==3?st.wDayOfWeek:attr[i]==4?st.wHour:attr[i]==5?st.wMinute:
attr[i]==6?st.wSecond:-1);
attr[i] = (T)res;
}
#else
time_t _st;
std::time(&_st);
struct tm *st = std::localtime(&_st);
for (unsigned int i = 0; i<nb_attr; ++i) {
res = (int)(attr[i]==0?st->tm_year + 1900:attr[i]==1?st->tm_mon + 1:attr[i]==2?st->tm_mday:
attr[i]==3?st->tm_wday:attr[i]==4?st->tm_hour:attr[i]==5?st->tm_min:
attr[i]==6?st->tm_sec:-1);
attr[i] = (T)res;
}
#endif
cimg::mutex(6,0);
return res;
}

//! Get current local time (single-attribute version).
/**
       \param attr Type of requested time attribute.
                   Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
       \return Specified attribute or -1 if an error occured.
    **/
inline int date(unsigned int attr) {
int out = (int)attr;
return date(&out,1);
}

// Get/set path to store temporary files.
inline const char* temporary_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the <i>Program Files/</i> directory (Windows only).
#if cimg_OS==2
inline const char* programfiles_path(const char *const user_path=0, const bool reinit_path=false);
#endif

// Get/set path to the ImageMagick's \c convert binary.
inline const char* imagemagick_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the GraphicsMagick's \c gm binary.
inline const char* graphicsmagick_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the XMedcon's \c medcon binary.
inline const char* medcon_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the FFMPEG's \c ffmpeg binary.
inline const char *ffmpeg_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the \c gzip binary.
inline const char *gzip_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the \c gunzip binary.
inline const char *gunzip_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the \c dcraw binary.
inline const char *dcraw_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the \c wget binary.
inline const char *wget_path(const char *const user_path=0, const bool reinit_path=false);

// Get/set path to the \c curl binary.
inline const char *curl_path(const char *const user_path=0, const bool reinit_path=false);

//! Split filename into two C-strings \c body and \c extension.
/**
       filename and body must not overlap!
    **/
inline const char *split_filename(const char *const filename, char *const body=0) {
if (!filename) { if (body) *body = 0; return 0; }
const char *p = 0; for (const char *np = filename; np>=filename && (p=np); np = std::strchr(np,'.') + 1) {}
if (p==filename) {
if (body) std::strcpy(body,filename);
return filename + std::strlen(filename);
}
const unsigned int l = (unsigned int)(p - filename - 1);
if (body) { if (l) std::memcpy(body,filename,l); body[l] = 0; }
return p;
}

//! Generate a numbered version of a filename.
inline char* number_filename(const char *const filename, const int number,
const unsigned int digits, char *const str) {
if (!filename) { if (str) *str = 0; return 0; }
char *const format = new char[1024], *const body = new char[1024];
const char *const ext = cimg::split_filename(filename,body);
if (*ext) cimg_snprintf(format,1024,"%%s_%%.%ud.%%s",digits);
else cimg_snprintf(format,1024,"%%s_%%.%ud",digits);
cimg_sprintf(str,format,body,number,ext);
delete[] format; delete[] body;
return str;
}

//! Read data from file.
/**
       \param[out] ptr Pointer to memory buffer that will contain the binary data read from file.
       \param nmemb Number of elements to read.
       \param stream File to read data from.
       \return Number of read elements.
       \note Same as <tt>std::fread()</tt> but may display warning message if all elements could not be read.
    **/
template<typename T>
inline size_t fread(T *const ptr, const size_t nmemb, std::FILE *stream) {
if (!ptr || !stream)
throw CImgArgumentException("cimg::fread(): Invalid reading request of %u %s%s from file %p to buffer %p.",
nmemb,cimg::type<T>::string(),nmemb>1?"s":"",stream,ptr);
if (!nmemb) return 0;
const size_t wlimitT = 63*1024*1024, wlimit = wlimitT/sizeof(T);
size_t to_read = nmemb, al_read = 0, l_to_read = 0, l_al_read = 0;
do {
l_to_read = (to_read*sizeof(T))<wlimitT?to_read:wlimit;
l_al_read = std::fread((void*)(ptr + al_read),sizeof(T),l_to_read,stream);
al_read+=l_al_read;
to_read-=l_al_read;
} while (l_to_read==l_al_read && to_read>0);
if (to_read>0)
warn("cimg::fread(): Only %lu/%lu elements could be read from file.",
(unsigned long)al_read,(unsigned long)nmemb);
return al_read;
}

//! Write data to file.
/**
       \param ptr Pointer to memory buffer containing the binary data to write on file.
       \param nmemb Number of elements to write.
       \param[out] stream File to write data on.
       \return Number of written elements.
       \note Similar to <tt>std::fwrite</tt> but may display warning messages if all elements could not be written.
    **/
template<typename T>
inline size_t fwrite(const T *ptr, const size_t nmemb, std::FILE *stream) {
if (!ptr || !stream)
throw CImgArgumentException("cimg::fwrite(): Invalid writing request of %u %s%s from buffer %p to file %p.",
nmemb,cimg::type<T>::string(),nmemb>1?"s":"",ptr,stream);
if (!nmemb) return 0;
const size_t wlimitT = 63*1024*1024, wlimit = wlimitT/sizeof(T);
size_t to_write = nmemb, al_write = 0, l_to_write = 0, l_al_write = 0;
do {
l_to_write = (to_write*sizeof(T))<wlimitT?to_write:wlimit;
l_al_write = std::fwrite((void*)(ptr + al_write),sizeof(T),l_to_write,stream);
al_write+=l_al_write;
to_write-=l_al_write;
} while (l_to_write==l_al_write && to_write>0);
if (to_write>0)
warn("cimg::fwrite(): Only %lu/%lu elements could be written in file.",
(unsigned long)al_write,(unsigned long)nmemb);
return al_write;
}

//! Create an empty file.
/**
       \param file Input file (can be \c 0 if \c filename is set).
       \param filename Filename, as a C-string (can be \c 0 if \c file is set).
    **/
inline void fempty(std::FILE *const file, const char *const filename) {
if (!file && !filename)
throw CImgArgumentException("cimg::fempty(): Specified filename is (null).");
std::FILE *const nfile = file?file:cimg::fopen(filename,"wb");
if (!file) cimg::fclose(nfile);
}

// Try to guess format from an image file.
inline const char *ftype(std::FILE *const file, const char *const filename);

// Load file from network as a local temporary file.
inline char *load_network(const char *const url, char *const filename_local,
const unsigned int timeout=0, const bool try_fallback=false,
const char *const referer=0);

//! Return options specified on the command line.
inline const char* option(const char *const name, const int argc, const char *const *const argv,
const char *const defaut, const char *const usage, const bool reset_static) {
static bool first = true, visu = false;
if (reset_static) { first = true; return 0; }
const char *res = 0;
if (first) {
first = false;
visu = cimg::option("-h",argc,argv,(char*)0,(char*)0,false)!=0;
visu |= cimg::option("-help",argc,argv,(char*)0,(char*)0,false)!=0;
visu |= cimg::option("--help",argc,argv,(char*)0,(char*)0,false)!=0;
}
if (!name && visu) {
if (usage) {
std::fprintf(cimg::output(),"\n %s%s%s",cimg::t_red,cimg::basename(argv[0]),cimg::t_normal);
std::fprintf(cimg::output(),": %s",usage);
std::fprintf(cimg::output()," (%s, %s)\n\n",cimg_date,cimg_time);
}
if (defaut) std::fprintf(cimg::output(),"%s\n",defaut);
}
if (name) {
if (argc>0) {
int k = 0;
while (k<argc && std::strcmp(argv[k],name)) ++k;
res = (k++==argc?defaut:(k==argc?argv[--k]:argv[k]));
} else res = defaut;
if (visu && usage) std::fprintf(cimg::output(),"    %s%-16s%s %-24s %s%s%s\n",
cimg::t_bold,name,cimg::t_normal,res?res:"0",
cimg::t_green,usage,cimg::t_normal);
}
return res;
}

inline const char* option(const char *const name, const int argc, const char *const *const argv,
const char *const defaut, const char *const usage=0) {
return option(name,argc,argv,defaut,usage,false);
}

inline bool option(const char *const name, const int argc, const char *const *const argv,
const bool defaut, const char *const usage=0) {
const char *const s = cimg::option(name,argc,argv,(char*)0);
const bool res = s?(cimg::strcasecmp(s,"false") && cimg::strcasecmp(s,"off") && cimg::strcasecmp(s,"0")):defaut;
cimg::option(name,0,0,res?"true":"false",usage);
return res;
}

inline int option(const char *const name, const int argc, const char *const *const argv,
const int defaut, const char *const usage=0) {
const char *const s = cimg::option(name,argc,argv,(char*)0);
const int res = s?std::atoi(s):defaut;
char *const tmp = new char[256];
cimg_snprintf(tmp,256,"%d",res);
cimg::option(name,0,0,tmp,usage);
delete[] tmp;
return res;
}

inline char option(const char *const name, const int argc, const char *const *const argv,
const char defaut, const char *const usage=0) {
const char *const s = cimg::option(name,argc,argv,(char*)0);
const char res = s?*s:defaut;
char tmp[8];
*tmp = res; tmp[1] = 0;
cimg::option(name,0,0,tmp,usage);
return res;
}

inline float option(const char *const name, const int argc, const char *const *const argv,
const float defaut, const char *const usage=0) {
const char *const s = cimg::option(name,argc,argv,(char*)0);
const float res = s?(float)cimg::atof(s):defaut;
char *const tmp = new char[256];
cimg_snprintf(tmp,256,"%g",res);
cimg::option(name,0,0,tmp,usage);
delete[] tmp;
return res;
}

inline double option(const char *const name, const int argc, const char *const *const argv,
const double defaut, const char *const usage=0) {
const char *const s = cimg::option(name,argc,argv,(char*)0);
const double res = s?cimg::atof(s):defaut;
char *const tmp = new char[256];
cimg_snprintf(tmp,256,"%g",res);
cimg::option(name,0,0,tmp,usage);
delete[] tmp;
return res;
}

//! Print information about \CImg environement variables.
/**
       \note Output is done on the default output stream.
    **/
inline void info() {
std::fprintf(cimg::output(),"\n %s%sCImg Library %u.%u.%u%s, compiled %s ( %s ) with the following flags:\n\n",
cimg::t_red,cimg::t_bold,cimg_version/100,(cimg_version/10)%10,cimg_version%10,
cimg::t_normal,cimg_date,cimg_time);

std::fprintf(cimg::output(),"  > Operating System:       %s%-13s%s %s('cimg_OS'=%d)%s\n",
cimg::t_bold,
cimg_OS==1?"Unix":(cimg_OS==2?"Windows":"Unknow"),
cimg::t_normal,cimg::t_green,
cimg_OS,
cimg::t_normal);

std::fprintf(cimg::output(),"  > CPU endianness:         %s%s Endian%s\n",
cimg::t_bold,
cimg::endianness()?"Big":"Little",
cimg::t_normal);

std::fprintf(cimg::output(),"  > Verbosity mode:         %s%-13s%s %s('cimg_verbosity'=%d)%s\n",
cimg::t_bold,
cimg_verbosity==0?"Quiet":
cimg_verbosity==1?"Console":
cimg_verbosity==2?"Dialog":
cimg_verbosity==3?"Console+Warnings":"Dialog+Warnings",
cimg::t_normal,cimg::t_green,
cimg_verbosity,
cimg::t_normal);

std::fprintf(cimg::output(),"  > Stricts warnings:       %s%-13s%s %s('cimg_strict_warnings' %s)%s\n",
cimg::t_bold,
#ifdef cimg_strict_warnings
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Support for C++11:      %s%-13s%s %s('cimg_use_cpp11'=%d)%s\n",
cimg::t_bold,
cimg_use_cpp11?"Yes":"No",
cimg::t_normal,cimg::t_green,
(int)cimg_use_cpp11,
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using VT100 messages:   %s%-13s%s %s('cimg_use_vt100' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_vt100
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Display type:           %s%-13s%s %s('cimg_display'=%d)%s\n",
cimg::t_bold,
cimg_display==0?"No display":cimg_display==1?"X11":cimg_display==2?"Windows GDI":"Unknown",
cimg::t_normal,cimg::t_green,
(int)cimg_display,
cimg::t_normal);

#if cimg_display==1
std::fprintf(cimg::output(),"  > Using XShm for X11:     %s%-13s%s %s('cimg_use_xshm' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_xshm
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using XRand for X11:    %s%-13s%s %s('cimg_use_xrandr' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_xrandr
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);
#endif
std::fprintf(cimg::output(),"  > Using OpenMP:           %s%-13s%s %s('cimg_use_openmp' %s)%s\n",
cimg::t_bold,
#if cimg_use_openmp!=0
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);
std::fprintf(cimg::output(),"  > Using PNG library:      %s%-13s%s %s('cimg_use_png' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_png
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);
std::fprintf(cimg::output(),"  > Using JPEG library:     %s%-13s%s %s('cimg_use_jpeg' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_jpeg
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using TIFF library:     %s%-13s%s %s('cimg_use_tiff' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_tiff
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using Magick++ library: %s%-13s%s %s('cimg_use_magick' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_magick
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using FFTW3 library:    %s%-13s%s %s('cimg_use_fftw3' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_fftw3
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

std::fprintf(cimg::output(),"  > Using LAPACK library:   %s%-13s%s %s('cimg_use_lapack' %s)%s\n",
cimg::t_bold,
#ifdef cimg_use_lapack
"Yes",cimg::t_normal,cimg::t_green,"defined",
#else
"No",cimg::t_normal,cimg::t_green,"undefined",
#endif
cimg::t_normal);

char *const tmp = new char[1024];
cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::imagemagick_path());
std::fprintf(cimg::output(),"  > Path of ImageMagick:    %s%-13s%s\n",
cimg::t_bold,
tmp,
cimg::t_normal);

cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::graphicsmagick_path());
std::fprintf(cimg::output(),"  > Path of GraphicsMagick: %s%-13s%s\n",
cimg::t_bold,
tmp,
cimg::t_normal);

cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::medcon_path());
std::fprintf(cimg::output(),"  > Path of 'medcon':       %s%-13s%s\n",
cimg::t_bold,
tmp,
cimg::t_normal);

cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::temporary_path());
std::fprintf(cimg::output(),"  > Temporary path:         %s%-13s%s\n",
cimg::t_bold,
tmp,
cimg::t_normal);

std::fprintf(cimg::output(),"\n");
delete[] tmp;
}

// Declare LAPACK function signatures if LAPACK support is enabled.
#ifdef cimg_use_lapack
template<typename T>
inline void getrf(int &N, T *lapA, int *IPIV, int &INFO) {
dgetrf_(&N,&N,lapA,&N,IPIV,&INFO);
}

inline void getrf(int &N, float *lapA, int *IPIV, int &INFO) {
sgetrf_(&N,&N,lapA,&N,IPIV,&INFO);
}

template<typename T>
inline void getri(int &N, T *lapA, int *IPIV, T* WORK, int &LWORK, int &INFO) {
dgetri_(&N,lapA,&N,IPIV,WORK,&LWORK,&INFO);
}

inline void getri(int &N, float *lapA, int *IPIV, float* WORK, int &LWORK, int &INFO) {
sgetri_(&N,lapA,&N,IPIV,WORK,&LWORK,&INFO);
}

template<typename T>
inline void gesvd(char &JOB, int &M, int &N, T *lapA, int &MN,
T *lapS, T *lapU, T *lapV, T *WORK, int &LWORK, int &INFO) {
dgesvd_(&JOB,&JOB,&M,&N,lapA,&MN,lapS,lapU,&M,lapV,&N,WORK,&LWORK,&INFO);
}

inline void gesvd(char &JOB, int &M, int &N, float *lapA, int &MN,
float *lapS, float *lapU, float *lapV, float *WORK, int &LWORK, int &INFO) {
sgesvd_(&JOB,&JOB,&M,&N,lapA,&MN,lapS,lapU,&M,lapV,&N,WORK,&LWORK,&INFO);
}

template<typename T>
inline void getrs(char &TRANS, int &N, T *lapA, int *IPIV, T *lapB, int &INFO) {
int one = 1;
dgetrs_(&TRANS,&N,&one,lapA,&N,IPIV,lapB,&N,&INFO);
}

inline void getrs(char &TRANS, int &N, float *lapA, int *IPIV, float *lapB, int &INFO) {
int one = 1;
sgetrs_(&TRANS,&N,&one,lapA,&N,IPIV,lapB,&N,&INFO);
}

template<typename T>
inline void syev(char &JOB, char &UPLO, int &N, T *lapA, T *lapW, T *WORK, int &LWORK, int &INFO) {
dsyev_(&JOB,&UPLO,&N,lapA,&N,lapW,WORK,&LWORK,&INFO);
}

inline void syev(char &JOB, char &UPLO, int &N, float *lapA, float *lapW, float *WORK, int &LWORK, int &INFO) {
ssyev_(&JOB,&UPLO,&N,lapA,&N,lapW,WORK,&LWORK,&INFO);
}

template<typename T>
inline void sgels(char & TRANS, int &M, int &N, int &NRHS, T* lapA, int &LDA,
T* lapB, int &LDB, T* WORK, int &LWORK, int &INFO){
dgels_(&TRANS, &M, &N, &NRHS, lapA, &LDA, lapB, &LDB, WORK, &LWORK, &INFO);
}

inline void sgels(char & TRANS, int &M, int &N, int &NRHS, float* lapA, int &LDA,
float* lapB, int &LDB, float* WORK, int &LWORK, int &INFO){
sgels_(&TRANS, &M, &N, &NRHS, lapA, &LDA, lapB, &LDB, WORK, &LWORK, &INFO);
}

#endif

// End of the 'cimg' namespace
}

/*------------------------------------------------
   #
   #
   #   Definition of mathematical operators and
   #   external functions.
   #
   #
   -------------------------------------------------*/

#define _cimg_create_ext_operators(typ) \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator+(const typ val, const CImg<T>& img) { \
    return img + val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator-(const typ val, const CImg<T>& img) { \
    typedef typename cimg::superset<T,typ>::type Tt; \
    return CImg<Tt>(img._width,img._height,img._depth,img._spectrum,val)-=img; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator*(const typ val, const CImg<T>& img) { \
    return img*val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator/(const typ val, const CImg<T>& img) { \
    return val*img.get_invert(); \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator&(const typ val, const CImg<T>& img) { \
    return img & val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator|(const typ val, const CImg<T>& img) { \
    return img | val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator^(const typ val, const CImg<T>& img) { \
    return img ^ val; \
  } \
  template<typename T> \
  inline bool operator==(const typ val, const CImg<T>& img) {   \
    return img == val; \
  } \
  template<typename T> \
  inline bool operator!=(const typ val, const CImg<T>& img) { \
    return img != val; \
  }

_cimg_create_ext_operators(bool)
_cimg_create_ext_operators(unsigned char)
_cimg_create_ext_operators(char)
_cimg_create_ext_operators(signed char)
_cimg_create_ext_operators(unsigned short)
_cimg_create_ext_operators(short)
_cimg_create_ext_operators(unsigned int)
_cimg_create_ext_operators(int)
_cimg_create_ext_operators(cimg_uint64)
_cimg_create_ext_operators(cimg_int64)
_cimg_create_ext_operators(float)
_cimg_create_ext_operators(double)
_cimg_create_ext_operators(long double)

template<typename T>
inline CImg<_cimg_Tfloat> operator+(const char *const expression, const CImg<T>& img) {
return img + expression;
}

template<typename T>
inline CImg<_cimg_Tfloat> operator-(const char *const expression, const CImg<T>& img) {
return CImg<_cimg_Tfloat>(img,false).fill(expression,true)-=img;
}

template<typename T>
inline CImg<_cimg_Tfloat> operator*(const char *const expression, const CImg<T>& img) {
return img*expression;
}

template<typename T>
inline CImg<_cimg_Tfloat> operator/(const char *const expression, const CImg<T>& img) {
return expression*img.get_invert();
}

template<typename T>
inline CImg<T> operator&(const char *const expression, const CImg<T>& img) {
return img & expression;
}

template<typename T>
inline CImg<T> operator|(const char *const expression, const CImg<T>& img) {
return img | expression;
}

template<typename T>
inline CImg<T> operator^(const char *const expression, const CImg<T>& img) {
return img ^ expression;
}

template<typename T>
inline bool operator==(const char *const expression, const CImg<T>& img) {
return img==expression;
}

template<typename T>
inline bool operator!=(const char *const expression, const CImg<T>& img) {
return img!=expression;
}

template<typename T>
inline CImg<T> transpose(const CImg<T>& instance) {
return instance.get_transpose();
}

template<typename T>
inline CImg<_cimg_Tfloat> invert(const CImg<T>& instance) {
return instance.get_invert();
}

template<typename T>
inline CImg<_cimg_Tfloat> pseudoinvert(const CImg<T>& instance) {
return instance.get_pseudoinvert();
}

#define _cimg_create_ext_pointwise_function(name) \
  template<typename T> \
  inline CImg<_cimg_Tfloat> name(const CImg<T>& instance) { \
    return instance.get_##name(); \
  }

_cimg_create_ext_pointwise_function(sqr)
_cimg_create_ext_pointwise_function(sqrt)
_cimg_create_ext_pointwise_function(exp)
_cimg_create_ext_pointwise_function(log)
_cimg_create_ext_pointwise_function(log2)
_cimg_create_ext_pointwise_function(log10)
_cimg_create_ext_pointwise_function(abs)
_cimg_create_ext_pointwise_function(sign)
_cimg_create_ext_pointwise_function(cos)
_cimg_create_ext_pointwise_function(sin)
_cimg_create_ext_pointwise_function(sinc)
_cimg_create_ext_pointwise_function(tan)
_cimg_create_ext_pointwise_function(acos)
_cimg_create_ext_pointwise_function(asin)
_cimg_create_ext_pointwise_function(atan)
_cimg_create_ext_pointwise_function(cosh)
_cimg_create_ext_pointwise_function(sinh)
_cimg_create_ext_pointwise_function(tanh)
_cimg_create_ext_pointwise_function(acosh)
_cimg_create_ext_pointwise_function(asinh)
_cimg_create_ext_pointwise_function(atanh)

/*-----------------------------------
   #
   # Define the CImgDisplay structure
   #
   ----------------------------------*/
//! Allow the creation of windows, display images on them and manage user events (keyboard, mouse and windows events).
/**
     CImgDisplay methods rely on a low-level graphic library to perform: it can be either \b X-Window
     (X11, for Unix-based systems) or \b GDI32 (for Windows-based systems).
     If both libraries are missing, CImgDisplay will not be able to display images on screen, and will enter
     a minimal mode where warning messages will be outputed each time the program is trying to call one of the
     CImgDisplay method.

     The configuration variable \c cimg_display tells about the graphic library used.
     It is set automatically by \CImg when one of these graphic libraries has been detected.
     But, you can override its value if necessary. Valid choices are:
     - 0: Disable display capabilities.
     - 1: Use \b X-Window (X11) library.
     - 2: Use \b GDI32 library.

     Remember to link your program against \b X11 or \b GDI32 libraries if you use CImgDisplay.
  **/
struct CImgDisplay {
cimg_ulong _timer, _fps_frames, _fps_timer;
unsigned int _width, _height, _normalization;
float _fps_fps, _min, _max;
bool _is_fullscreen;
char *_title;
unsigned int _window_width, _window_height, _button, *_keys, *_released_keys;
int _window_x, _window_y, _mouse_x, _mouse_y, _wheel;
bool _is_closed, _is_resized, _is_moved, _is_event,
_is_keyESC, _is_keyF1, _is_keyF2, _is_keyF3, _is_keyF4, _is_keyF5, _is_keyF6, _is_keyF7,
_is_keyF8, _is_keyF9, _is_keyF10, _is_keyF11, _is_keyF12, _is_keyPAUSE, _is_key1, _is_key2,
_is_key3, _is_key4, _is_key5, _is_key6, _is_key7, _is_key8, _is_key9, _is_key0,
_is_keyBACKSPACE, _is_keyINSERT, _is_keyHOME, _is_keyPAGEUP, _is_keyTAB, _is_keyQ, _is_keyW, _is_keyE,
_is_keyR, _is_keyT, _is_keyY, _is_keyU, _is_keyI, _is_keyO, _is_keyP, _is_keyDELETE,
_is_keyEND, _is_keyPAGEDOWN, _is_keyCAPSLOCK, _is_keyA, _is_keyS, _is_keyD, _is_keyF, _is_keyG,
_is_keyH, _is_keyJ, _is_keyK, _is_keyL, _is_keyENTER, _is_keySHIFTLEFT, _is_keyZ, _is_keyX,
_is_keyC, _is_keyV, _is_keyB, _is_keyN, _is_keyM, _is_keySHIFTRIGHT, _is_keyARROWUP, _is_keyCTRLLEFT,
_is_keyAPPLEFT, _is_keyALT, _is_keySPACE, _is_keyALTGR, _is_keyAPPRIGHT, _is_keyMENU, _is_keyCTRLRIGHT,
_is_keyARROWLEFT, _is_keyARROWDOWN, _is_keyARROWRIGHT, _is_keyPAD0, _is_keyPAD1, _is_keyPAD2, _is_keyPAD3,
_is_keyPAD4, _is_keyPAD5, _is_keyPAD6, _is_keyPAD7, _is_keyPAD8, _is_keyPAD9, _is_keyPADADD, _is_keyPADSUB,
_is_keyPADMUL, _is_keyPADDIV;

//@}
//---------------------------
//
//! \name Plugins
//@{
//---------------------------

#ifdef cimgdisplay_plugin
#include cimgdisplay_plugin
#endif
#ifdef cimgdisplay_plugin1
#include cimgdisplay_plugin1
#endif
#ifdef cimgdisplay_plugin2
#include cimgdisplay_plugin2
#endif
#ifdef cimgdisplay_plugin3
#include cimgdisplay_plugin3
#endif
#ifdef cimgdisplay_plugin4
#include cimgdisplay_plugin4
#endif
#ifdef cimgdisplay_plugin5
#include cimgdisplay_plugin5
#endif
#ifdef cimgdisplay_plugin6
#include cimgdisplay_plugin6
#endif
#ifdef cimgdisplay_plugin7
#include cimgdisplay_plugin7
#endif
#ifdef cimgdisplay_plugin8
#include cimgdisplay_plugin8
#endif

//@}
//--------------------------------------------------------
//
//! \name Constructors / Destructor / Instance Management
//@{
//--------------------------------------------------------

//! Destructor.
/**
       \note If the associated window is visible on the screen, it is closed by the call to the destructor.
    **/
~CImgDisplay() {
assign();
delete[] _keys;
delete[] _released_keys;
}

//! Construct an empty display.
/**
       \note Constructing an empty CImgDisplay instance does not make a window appearing on the screen, until
       display of valid data is performed.
       \par Example
       \code
       CImgDisplay disp;  // Does actually nothing
       ...
       disp.display(img); // Construct new window and display image in it
       \endcode
    **/
CImgDisplay():
_width(0),_height(0),_normalization(0),
_min(0),_max(0),
_is_fullscreen(false),
_title(0),
_window_width(0),_window_height(0),_button(0),
_keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
_window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
_is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
assign();
}

//! Construct a display with specified dimensions.
/** \param width Window width.
        \param height Window height.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note A black background is initially displayed on the associated window.
    **/
CImgDisplay(const unsigned int width, const unsigned int height,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false):
_width(0),_height(0),_normalization(0),
_min(0),_max(0),
_is_fullscreen(false),
_title(0),
_window_width(0),_window_height(0),_button(0),
_keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
_window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
_is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
assign(width,height,title,normalization,is_fullscreen,is_closed);
}

//! Construct a display from an image.
/** \param img Image used as a model to create the window.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note The pixels of the input image are initially displayed on the associated window.
    **/
template<typename T>
explicit CImgDisplay(const CImg<T>& img,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false):
_width(0),_height(0),_normalization(0),
_min(0),_max(0),
_is_fullscreen(false),
_title(0),
_window_width(0),_window_height(0),_button(0),
_keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
_window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
_is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
assign(img,title,normalization,is_fullscreen,is_closed);
}

//! Construct a display from an image list.
/** \param list The images list to display.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note All images of the list, appended along the X-axis, are initially displayed on the associated window.
    **/
template<typename T>
explicit CImgDisplay(const CImgList<T>& list,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false):
_width(0),_height(0),_normalization(0),
_min(0),_max(0),
_is_fullscreen(false),
_title(0),
_window_width(0),_window_height(0),_button(0),
_keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
_window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
_is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
assign(list,title,normalization,is_fullscreen,is_closed);
}

//! Construct a display as a copy of an existing one.
/**
        \param disp Display instance to copy.
        \note The pixel buffer of the input window is initially displayed on the associated window.
    **/
CImgDisplay(const CImgDisplay& disp):
_width(0),_height(0),_normalization(0),
_min(0),_max(0),
_is_fullscreen(false),
_title(0),
_window_width(0),_window_height(0),_button(0),
_keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
_window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
_is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
assign(disp);
}

//! Take a screenshot.
/**
       \param[out] img Output screenshot. Can be empty on input
    **/
template<typename T>
static void screenshot(CImg<T>& img) {
return screenshot(0,0,cimg::type<int>::max(),cimg::type<int>::max(),img);
}

#if cimg_display==0

static void _no_display_exception() {
throw CImgDisplayException("CImgDisplay(): No display available.");
}

//! Destructor - Empty constructor \inplace.
/**
       \note Replace the current instance by an empty display.
    **/
CImgDisplay& assign() {
return flush();
}

//! Construct a display with specified dimensions \inplace.
/**
    **/
CImgDisplay& assign(const unsigned int width, const unsigned int height,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false) {
cimg::unused(width,height,title,normalization,is_fullscreen,is_closed);
_no_display_exception();
return assign();
}

//! Construct a display from an image \inplace.
/**
    **/
template<typename T>
CImgDisplay& assign(const CImg<T>& img,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false) {
_no_display_exception();
return assign(img._width,img._height,title,normalization,is_fullscreen,is_closed);
}

//! Construct a display from an image list \inplace.
/**
    **/
template<typename T>
CImgDisplay& assign(const CImgList<T>& list,
const char *const title=0, const unsigned int normalization=3,
const bool is_fullscreen=false, const bool is_closed=false) {
_no_display_exception();
return assign(list._width,list._width,title,normalization,is_fullscreen,is_closed);
}

//! Construct a display as a copy of another one \inplace.
/**
    **/
CImgDisplay& assign(const CImgDisplay &disp) {
_no_display_exception();
return assign(disp._width,disp._height);
}

#endif

//! Return a reference to an empty display.
/**
       \note Can be useful for writing function prototypes where one of the argument (of type CImgDisplay&)
       must have a default value.
       \par Example
       \code
       void foo(CImgDisplay& disp=CImgDisplay::empty());
       \endcode
    **/
static CImgDisplay& empty() {
static CImgDisplay _empty;
return _empty.assign();
}

//! Return a reference to an empty display \const.
static const CImgDisplay& const_empty() {
static const CImgDisplay _empty;
return _empty;
}

#define cimg_fitscreen(dx,dy,dz) CImgDisplay::_fitscreen(dx,dy,dz,256,-85,false), \
                                 CImgDisplay::_fitscreen(dx,dy,dz,256,-85,true)
static unsigned int _fitscreen(const unsigned int dx, const unsigned int dy, const unsigned int dz,
const int dmin, const int dmax, const bool return_y) {
const int
u = CImgDisplay::screen_width(),
v = CImgDisplay::screen_height();
const float
mw = dmin<0?cimg::round(u*-dmin/100.f):(float)dmin,
mh = dmin<0?cimg::round(v*-dmin/100.f):(float)dmin,
Mw = dmax<0?cimg::round(u*-dmax/100.f):(float)dmax,
Mh = dmax<0?cimg::round(v*-dmax/100.f):(float)dmax;
float
w = (float)std::max(1U,dx),
h = (float)std::max(1U,dy);
if (dz>1) { w+=dz; h+=dz; }
if (w<mw) { h = h*mw/w; w = mw; }
if (h<mh) { w = w*mh/h; h = mh; }
if (w>Mw) { h = h*Mw/w; w = Mw; }
if (h>Mh) { w = w*Mh/h; h = Mh; }
if (w<mw) w = mw;
if (h<mh) h = mh;
return std::max(1U,(unsigned int)cimg::round(return_y?h:w));
}

//@}
//------------------------------------------
//
//! \name Overloaded Operators
//@{
//------------------------------------------

//! Display image on associated window.
/**
       \note <tt>disp = img</tt> is equivalent to <tt>disp.display(img)</tt>.
    **/
template<typename t>
CImgDisplay& operator=(const CImg<t>& img) {
return display(img);
}

//! Display list of images on associated window.
/**
       \note <tt>disp = list</tt> is equivalent to <tt>disp.display(list)</tt>.
    **/
template<typename t>
CImgDisplay& operator=(const CImgList<t>& list) {
return display(list);
}

//! Construct a display as a copy of another one \inplace.
/**
       \note Equivalent to assign(const CImgDisplay&).
     **/
CImgDisplay& operator=(const CImgDisplay& disp) {
return assign(disp);
}

//! Return \c false if display is empty, \c true otherwise.
/**
       \note <tt>if (disp) { ... }</tt> is equivalent to <tt>if (!disp.is_empty()) { ... }</tt>.
    **/
operator bool() const {
return !is_empty();
}

//@}
//------------------------------------------
//
//! \name Instance Checking
//@{
//------------------------------------------

//! Return \c true if display is empty, \c false otherwise.
/**
    **/
bool is_empty() const {
return !(_width && _height);
}

//! Return \c true if display is closed (i.e. not visible on the screen), \c false otherwise.
/**
       \note
       - When a user physically closes the associated window, the display is set to closed.
       - A closed display is not destroyed. Its associated window can be show again on the screen using show().
    **/
bool is_closed() const {
return _is_closed;
}

//! Return \c true if associated window has been resized on the screen, \c false otherwise.
/**
    **/
bool is_resized() const {
return _is_resized;
}

//! Return \c true if associated window has been moved on the screen, \c false otherwise.
/**
    **/
bool is_moved() const {
return _is_moved;
}

//! Return \c true if any event has occured on the associated window, \c false otherwise.
/**
    **/
bool is_event() const {
return _is_event;
}

//! Return \c true if current display is in fullscreen mode, \c false otherwise.
/**
    **/
bool is_fullscreen() const {
return _is_fullscreen;
}

//! Return \c true if any key is being pressed on the associated window, \c false otherwise.
/**
       \note The methods below do the same only for specific keys.
    **/
bool is_key() const {
return _is_keyESC || _is_keyF1 || _is_keyF2 || _is_keyF3 ||
_is_keyF4 || _is_keyF5 || _is_keyF6 || _is_keyF7 ||
_is_keyF8 || _is_keyF9 || _is_keyF10 || _is_keyF11 ||
_is_keyF12 || _is_keyPAUSE || _is_key1 || _is_key2 ||
_is_key3 || _is_key4 || _is_key5 || _is_key6 ||
_is_key7 || _is_key8 || _is_key9 || _is_key0 ||
_is_keyBACKSPACE || _is_keyINSERT || _is_keyHOME ||
_is_keyPAGEUP || _is_keyTAB || _is_keyQ || _is_keyW ||
_is_keyE || _is_keyR || _is_keyT || _is_keyY ||
_is_keyU || _is_keyI || _is_keyO || _is_keyP ||
_is_keyDELETE || _is_keyEND || _is_keyPAGEDOWN ||
_is_keyCAPSLOCK || _is_keyA || _is_keyS || _is_keyD ||
_is_keyF || _is_keyG || _is_keyH || _is_keyJ ||
_is_keyK || _is_keyL || _is_keyENTER ||
_is_keySHIFTLEFT || _is_keyZ || _is_keyX || _is_keyC ||
_is_keyV || _is_keyB || _is_keyN || _is_keyM ||
_is_keySHIFTRIGHT || _is_keyARROWUP || _is_keyCTRLLEFT ||
_is_keyAPPLEFT || _is_keyALT || _is_keySPACE || _is_keyALTGR ||
_is_keyAPPRIGHT || _is_keyMENU || _is_keyCTRLRIGHT ||
_is_keyARROWLEFT || _is_keyARROWDOWN || _is_keyARROWRIGHT ||
_is_keyPAD0 || _is_keyPAD1 || _is_keyPAD2 ||
_is_keyPAD3 || _is_keyPAD4 || _is_keyPAD5 ||
_is_keyPAD6 || _is_keyPAD7 || _is_keyPAD8 ||
_is_keyPAD9 || _is_keyPADADD || _is_keyPADSUB ||
_is_keyPADMUL || _is_keyPADDIV;
}

//! Return \c true if key specified by given keycode is being pressed on the associated window, \c false otherwise.
/**
       \param keycode Keycode to test.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.key(cimg::keyTAB)) { ... }  // Equivalent to 'if (disp.is_keyTAB())'
         disp.wait();
       }
       \endcode
    **/
bool is_key(const unsigned int keycode) const {
#define _cimg_iskey_test(k) if (keycode==cimg::key##k) return _is_key##k;
_cimg_iskey_test(ESC); _cimg_iskey_test(F1); _cimg_iskey_test(F2); _cimg_iskey_test(F3);
_cimg_iskey_test(F4); _cimg_iskey_test(F5); _cimg_iskey_test(F6); _cimg_iskey_test(F7);
_cimg_iskey_test(F8); _cimg_iskey_test(F9); _cimg_iskey_test(F10); _cimg_iskey_test(F11);
_cimg_iskey_test(F12); _cimg_iskey_test(PAUSE); _cimg_iskey_test(1); _cimg_iskey_test(2);
_cimg_iskey_test(3); _cimg_iskey_test(4); _cimg_iskey_test(5); _cimg_iskey_test(6);
_cimg_iskey_test(7); _cimg_iskey_test(8); _cimg_iskey_test(9); _cimg_iskey_test(0);
_cimg_iskey_test(BACKSPACE); _cimg_iskey_test(INSERT); _cimg_iskey_test(HOME);
_cimg_iskey_test(PAGEUP); _cimg_iskey_test(TAB); _cimg_iskey_test(Q); _cimg_iskey_test(W);
_cimg_iskey_test(E); _cimg_iskey_test(R); _cimg_iskey_test(T); _cimg_iskey_test(Y);
_cimg_iskey_test(U); _cimg_iskey_test(I); _cimg_iskey_test(O); _cimg_iskey_test(P);
_cimg_iskey_test(DELETE); _cimg_iskey_test(END); _cimg_iskey_test(PAGEDOWN);
_cimg_iskey_test(CAPSLOCK); _cimg_iskey_test(A); _cimg_iskey_test(S); _cimg_iskey_test(D);
_cimg_iskey_test(F); _cimg_iskey_test(G); _cimg_iskey_test(H); _cimg_iskey_test(J);
_cimg_iskey_test(K); _cimg_iskey_test(L); _cimg_iskey_test(ENTER);
_cimg_iskey_test(SHIFTLEFT); _cimg_iskey_test(Z); _cimg_iskey_test(X); _cimg_iskey_test(C);
_cimg_iskey_test(V); _cimg_iskey_test(B); _cimg_iskey_test(N); _cimg_iskey_test(M);
_cimg_iskey_test(SHIFTRIGHT); _cimg_iskey_test(ARROWUP); _cimg_iskey_test(CTRLLEFT);
_cimg_iskey_test(APPLEFT); _cimg_iskey_test(ALT); _cimg_iskey_test(SPACE); _cimg_iskey_test(ALTGR);
_cimg_iskey_test(APPRIGHT); _cimg_iskey_test(MENU); _cimg_iskey_test(CTRLRIGHT);
_cimg_iskey_test(ARROWLEFT); _cimg_iskey_test(ARROWDOWN); _cimg_iskey_test(ARROWRIGHT);
_cimg_iskey_test(PAD0); _cimg_iskey_test(PAD1); _cimg_iskey_test(PAD2);
_cimg_iskey_test(PAD3); _cimg_iskey_test(PAD4); _cimg_iskey_test(PAD5);
_cimg_iskey_test(PAD6); _cimg_iskey_test(PAD7); _cimg_iskey_test(PAD8);
_cimg_iskey_test(PAD9); _cimg_iskey_test(PADADD); _cimg_iskey_test(PADSUB);
_cimg_iskey_test(PADMUL); _cimg_iskey_test(PADDIV);
return false;
}

//! Return \c true if key specified by given keycode is being pressed on the associated window, \c false otherwise.
/**
       \param keycode C-string containing the keycode label of the key to test.
       \note Use it when the key you want to test can be dynamically set by the user.
       \par Example
       \code
       CImgDisplay disp(400,400);
       const char *const keycode = "TAB";
       while (!disp.is_closed()) {
         if (disp.is_key(keycode)) { ... }  // Equivalent to 'if (disp.is_keyTAB())'
         disp.wait();
       }
       \endcode
    **/
bool& is_key(const char *const keycode) {
static bool f = false;
f = false;
#define _cimg_iskey_test2(k) if (!cimg::strcasecmp(keycode,#k)) return _is_key##k;
_cimg_iskey_test2(ESC); _cimg_iskey_test2(F1); _cimg_iskey_test2(F2); _cimg_iskey_test2(F3);
_cimg_iskey_test2(F4); _cimg_iskey_test2(F5); _cimg_iskey_test2(F6); _cimg_iskey_test2(F7);
_cimg_iskey_test2(F8); _cimg_iskey_test2(F9); _cimg_iskey_test2(F10); _cimg_iskey_test2(F11);
_cimg_iskey_test2(F12); _cimg_iskey_test2(PAUSE); _cimg_iskey_test2(1); _cimg_iskey_test2(2);
_cimg_iskey_test2(3); _cimg_iskey_test2(4); _cimg_iskey_test2(5); _cimg_iskey_test2(6);
_cimg_iskey_test2(7); _cimg_iskey_test2(8); _cimg_iskey_test2(9); _cimg_iskey_test2(0);
_cimg_iskey_test2(BACKSPACE); _cimg_iskey_test2(INSERT); _cimg_iskey_test2(HOME);
_cimg_iskey_test2(PAGEUP); _cimg_iskey_test2(TAB); _cimg_iskey_test2(Q); _cimg_iskey_test2(W);
_cimg_iskey_test2(E); _cimg_iskey_test2(R); _cimg_iskey_test2(T); _cimg_iskey_test2(Y);
_cimg_iskey_test2(U); _cimg_iskey_test2(I); _cimg_iskey_test2(O); _cimg_iskey_test2(P);
_cimg_iskey_test2(DELETE); _cimg_iskey_test2(END); _cimg_iskey_test2(PAGEDOWN);
_cimg_iskey_test2(CAPSLOCK); _cimg_iskey_test2(A); _cimg_iskey_test2(S); _cimg_iskey_test2(D);
_cimg_iskey_test2(F); _cimg_iskey_test2(G); _cimg_iskey_test2(H); _cimg_iskey_test2(J);
_cimg_iskey_test2(K); _cimg_iskey_test2(L); _cimg_iskey_test2(ENTER);
_cimg_iskey_test2(SHIFTLEFT); _cimg_iskey_test2(Z); _cimg_iskey_test2(X); _cimg_iskey_test2(C);
_cimg_iskey_test2(V); _cimg_iskey_test2(B); _cimg_iskey_test2(N); _cimg_iskey_test2(M);
_cimg_iskey_test2(SHIFTRIGHT); _cimg_iskey_test2(ARROWUP); _cimg_iskey_test2(CTRLLEFT);
_cimg_iskey_test2(APPLEFT); _cimg_iskey_test2(ALT); _cimg_iskey_test2(SPACE); _cimg_iskey_test2(ALTGR);
_cimg_iskey_test2(APPRIGHT); _cimg_iskey_test2(MENU); _cimg_iskey_test2(CTRLRIGHT);
_cimg_iskey_test2(ARROWLEFT); _cimg_iskey_test2(ARROWDOWN); _cimg_iskey_test2(ARROWRIGHT);
_cimg_iskey_test2(PAD0); _cimg_iskey_test2(PAD1); _cimg_iskey_test2(PAD2);
_cimg_iskey_test2(PAD3); _cimg_iskey_test2(PAD4); _cimg_iskey_test2(PAD5);
_cimg_iskey_test2(PAD6); _cimg_iskey_test2(PAD7); _cimg_iskey_test2(PAD8);
_cimg_iskey_test2(PAD9); _cimg_iskey_test2(PADADD); _cimg_iskey_test2(PADSUB);
_cimg_iskey_test2(PADMUL); _cimg_iskey_test2(PADDIV);
return f;
}

//! Return \c true if specified key sequence has been typed on the associated window, \c false otherwise.
/**
       \param keycodes_sequence Buffer of keycodes to test.
       \param length Number of keys in the \c keycodes_sequence buffer.
       \param remove_sequence Tells if the key sequence must be removed from the key history, if found.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       CImgDisplay disp(400,400);
       const unsigned int key_seq[] = { cimg::keyCTRLLEFT, cimg::keyD };
       while (!disp.is_closed()) {
         if (disp.is_key_sequence(key_seq,2)) { ... }  // Test for the 'CTRL+D' keyboard event
         disp.wait();
       }
       \endcode
    **/
bool is_key_sequence(const unsigned int *const keycodes_sequence, const unsigned int length,
const bool remove_sequence=false) {
if (keycodes_sequence && length) {
const unsigned int
*const ps_end = keycodes_sequence + length - 1,
*const pk_end = (unsigned int*)_keys + 1 + 128 - length,
k = *ps_end;
for (unsigned int *pk = (unsigned int*)_keys; pk<pk_end; ) {
if (*(pk++)==k) {
bool res = true;
const unsigned int *ps = ps_end, *pk2 = pk;
for (unsigned int i = 1; i<length; ++i) res = (*(--ps)==*(pk2++));
if (res) {
if (remove_sequence) std::memset((void*)(pk - 1),0,sizeof(unsigned int)*length);
return true;
}
}
}
}
return false;
}

#define _cimg_iskey_def(k) \
    bool is_key##k() const { \
      return _is_key##k; \
    }

//! Return \c true if the \c ESC key is being pressed on the associated window, \c false otherwise.
/**
       \note Similar methods exist for all keys managed by \CImg (see cimg::keyESC).
    **/
_cimg_iskey_def(ESC); _cimg_iskey_def(F1); _cimg_iskey_def(F2); _cimg_iskey_def(F3);
_cimg_iskey_def(F4); _cimg_iskey_def(F5); _cimg_iskey_def(F6); _cimg_iskey_def(F7);
_cimg_iskey_def(F8); _cimg_iskey_def(F9); _cimg_iskey_def(F10); _cimg_iskey_def(F11);
_cimg_iskey_def(F12); _cimg_iskey_def(PAUSE); _cimg_iskey_def(1); _cimg_iskey_def(2);
_cimg_iskey_def(3); _cimg_iskey_def(4); _cimg_iskey_def(5); _cimg_iskey_def(6);
_cimg_iskey_def(7); _cimg_iskey_def(8); _cimg_iskey_def(9); _cimg_iskey_def(0);
_cimg_iskey_def(BACKSPACE); _cimg_iskey_def(INSERT); _cimg_iskey_def(HOME);
_cimg_iskey_def(PAGEUP); _cimg_iskey_def(TAB); _cimg_iskey_def(Q); _cimg_iskey_def(W);
_cimg_iskey_def(E); _cimg_iskey_def(R); _cimg_iskey_def(T); _cimg_iskey_def(Y);
_cimg_iskey_def(U); _cimg_iskey_def(I); _cimg_iskey_def(O); _cimg_iskey_def(P);
_cimg_iskey_def(DELETE); _cimg_iskey_def(END); _cimg_iskey_def(PAGEDOWN);
_cimg_iskey_def(CAPSLOCK); _cimg_iskey_def(A); _cimg_iskey_def(S); _cimg_iskey_def(D);
_cimg_iskey_def(F); _cimg_iskey_def(G); _cimg_iskey_def(H); _cimg_iskey_def(J);
_cimg_iskey_def(K); _cimg_iskey_def(L); _cimg_iskey_def(ENTER);
_cimg_iskey_def(SHIFTLEFT); _cimg_iskey_def(Z); _cimg_iskey_def(X); _cimg_iskey_def(C);
_cimg_iskey_def(V); _cimg_iskey_def(B); _cimg_iskey_def(N); _cimg_iskey_def(M);
_cimg_iskey_def(SHIFTRIGHT); _cimg_iskey_def(ARROWUP); _cimg_iskey_def(CTRLLEFT);
_cimg_iskey_def(APPLEFT); _cimg_iskey_def(ALT); _cimg_iskey_def(SPACE); _cimg_iskey_def(ALTGR);
_cimg_iskey_def(APPRIGHT); _cimg_iskey_def(MENU); _cimg_iskey_def(CTRLRIGHT);
_cimg_iskey_def(ARROWLEFT); _cimg_iskey_def(ARROWDOWN); _cimg_iskey_def(ARROWRIGHT);
_cimg_iskey_def(PAD0); _cimg_iskey_def(PAD1); _cimg_iskey_def(PAD2);
_cimg_iskey_def(PAD3); _cimg_iskey_def(PAD4); _cimg_iskey_def(PAD5);
_cimg_iskey_def(PAD6); _cimg_iskey_def(PAD7); _cimg_iskey_def(PAD8);
_cimg_iskey_def(PAD9); _cimg_iskey_def(PADADD); _cimg_iskey_def(PADSUB);
_cimg_iskey_def(PADMUL); _cimg_iskey_def(PADDIV);

//@}
//------------------------------------------
//
//! \name Instance Characteristics
//@{
//------------------------------------------

#if cimg_display==0

//! Return width of the screen (current resolution along the X-axis).
/**
    **/
static int screen_width() {
_no_display_exception();
return 0;
}

//! Return height of the screen (current resolution along the Y-axis).
/**
    **/
static int screen_height() {
_no_display_exception();
return 0;
}

#endif

//! Return display width.
/**
       \note The width of the display (i.e. the width of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual width of the associated window.
    **/
int width() const {
return (int)_width;
}

//! Return display height.
/**
       \note The height of the display (i.e. the height of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual height of the associated window.
    **/
int height() const {
return (int)_height;
}

//! Return normalization type of the display.
/**
       The normalization type tells about how the values of an input image are normalized by the CImgDisplay to be
       correctly displayed. The range of values for pixels displayed on screen is <tt>[0,255]</tt>.
       If the range of values of the data to display is different, a normalization may be required for displaying
       the data in a correct way. The normalization type can be one of:
       - \c 0: Value normalization is disabled. It is then assumed that all input data to be displayed by the
       CImgDisplay instance have values in range <tt>[0,255]</tt>.
       - \c 1: Value normalization is always performed (this is the default behavior).
       Before displaying an input image, its values will be (virtually) stretched
       in range <tt>[0,255]</tt>, so that the contrast of the displayed pixels will be maximum.
       Use this mode for images whose minimum and maximum values are not prescribed to known values
       (e.g. float-valued images).
       Note that when normalized versions of images are computed for display purposes, the actual values of these
       images are not modified.
       - \c 2: Value normalization is performed once (on the first image display), then the same normalization
       coefficients are kept for next displayed frames.
       - \c 3: Value normalization depends on the pixel type of the data to display. For integer pixel types,
       the normalization is done regarding the minimum/maximum values of the type (no normalization occurs then
       for <tt>unsigned char</tt>).
       For float-valued pixel types, the normalization is done regarding the minimum/maximum value of the image
       data instead.
    **/
unsigned int normalization() const {
return _normalization;
}

//! Return title of the associated window as a C-string.
/**
       \note Window title may be not visible, depending on the used window manager or if the current display is
       in fullscreen mode.
    **/
const char *title() const {
return _title?_title:"";
}

//! Return width of the associated window.
/**
       \note The width of the display (i.e. the width of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual width of the associated window.
    **/
int window_width() const {
return (int)_window_width;
}

//! Return height of the associated window.
/**
       \note The height of the display (i.e. the height of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual height of the associated window.
    **/
int window_height() const {
return (int)_window_height;
}

//! Return X-coordinate of the associated window.
/**
       \note The returned coordinate corresponds to the location of the upper-left corner of the associated window.
    **/
int window_x() const {
return _window_x;
}

//! Return Y-coordinate of the associated window.
/**
       \note The returned coordinate corresponds to the location of the upper-left corner of the associated window.
    **/
int window_y() const {
return _window_y;
}

//! Return X-coordinate of the mouse pointer.
/**
       \note
       - If the mouse pointer is outside window area, \c -1 is returned.
       - Otherwise, the returned value is in the range [0,width()-1].
    **/
int mouse_x() const {
return _mouse_x;
}

//! Return Y-coordinate of the mouse pointer.
/**
       \note
       - If the mouse pointer is outside window area, \c -1 is returned.
       - Otherwise, the returned value is in the range [0,height()-1].
    **/
int mouse_y() const {
return _mouse_y;
}

//! Return current state of the mouse buttons.
/**
       \note Three mouse buttons can be managed. If one button is pressed, its corresponding bit in the returned
       value is set:
       - bit \c 0 (value \c 0x1): State of the left mouse button.
       - bit \c 1 (value \c 0x2): State of the right mouse button.
       - bit \c 2 (value \c 0x4): State of the middle mouse button.

       Several bits can be activated if more than one button are pressed at the same time.
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.button()&1) { // Left button clicked
           ...
         }
         if (disp.button()&2) { // Right button clicked
           ...
         }
         if (disp.button()&4) { // Middle button clicked
           ...
         }
         disp.wait();
       }
       \endcode
    **/
unsigned int button() const {
return _button;
}

//! Return current state of the mouse wheel.
/**
       \note
       - The returned value can be positive or negative depending on whether the mouse wheel has been scrolled
       forward or backward.
       - Scrolling the wheel forward add \c 1 to the wheel value.
       - Scrolling the wheel backward substract \c 1 to the wheel value.
       - The returned value cumulates the number of forward of backward scrolls since the creation of the display,
       or since the last reset of the wheel value (using set_wheel()). It is strongly recommended to quickly reset
       the wheel counter when an action has been performed regarding the current wheel value.
       Otherwise, the returned wheel value may be for instance \c 0 despite the fact that many scrolls have been done
       (as many in forward as in backward directions).
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.wheel()) {
           int counter = disp.wheel();  // Read the state of the mouse wheel
           ...                          // Do what you want with 'counter'
           disp.set_wheel();            // Reset the wheel value to 0
         }
         disp.wait();
       }
       \endcode
    **/
int wheel() const {
return _wheel;
}

//! Return one entry from the pressed keys history.
/**
       \param pos Index to read from the pressed keys history (index \c 0 corresponds to latest entry).
       \return Keycode of a pressed key or \c 0 for a released key.
       \note
       - Each CImgDisplay stores a history of the pressed keys in a buffer of size \c 128. When a new key is pressed,
       its keycode is stored in the pressed keys history. When a key is released, \c 0 is put instead.
       This means that up to the 64 last pressed keys may be read from the pressed keys history.
       When a new value is stored, the pressed keys history is shifted so that the latest entry is always
       stored at position \c 0.
       - Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
unsigned int key(const unsigned int pos=0) const {
return pos<128?_keys[pos]:0;
}

//! Return one entry from the released keys history.
/**
       \param pos Index to read from the released keys history (index \c 0 corresponds to latest entry).
       \return Keycode of a released key or \c 0 for a pressed key.
       \note
       - Each CImgDisplay stores a history of the released keys in a buffer of size \c 128. When a new key is released,
       its keycode is stored in the pressed keys history. When a key is pressed, \c 0 is put instead.
       This means that up to the 64 last released keys may be read from the released keys history.
       When a new value is stored, the released keys history is shifted so that the latest entry is always
       stored at position \c 0.
       - Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
unsigned int released_key(const unsigned int pos=0) const {
return pos<128?_released_keys[pos]:0;
}

//! Return keycode corresponding to the specified string.
/**
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       const unsigned int keyTAB = CImgDisplay::keycode("TAB");  // Return cimg::keyTAB
       \endcode
    **/
static unsigned int keycode(const char *const keycode) {
#define _cimg_keycode(k) if (!cimg::strcasecmp(keycode,#k)) return cimg::key##k;
_cimg_keycode(ESC); _cimg_keycode(F1); _cimg_keycode(F2); _cimg_keycode(F3);
_cimg_keycode(F4); _cimg_keycode(F5); _cimg_keycode(F6); _cimg_keycode(F7);
_cimg_keycode(F8); _cimg_keycode(F9); _cimg_keycode(F10); _cimg_keycode(F11);
_cimg_keycode(F12); _cimg_keycode(PAUSE); _cimg_keycode(1); _cimg_keycode(2);
_cimg_keycode(3); _cimg_keycode(4); _cimg_keycode(5); _cimg_keycode(6);
_cimg_keycode(7); _cimg_keycode(8); _cimg_keycode(9); _cimg_keycode(0);
_cimg_keycode(BACKSPACE); _cimg_keycode(INSERT); _cimg_keycode(HOME);
_cimg_keycode(PAGEUP); _cimg_keycode(TAB); _cimg_keycode(Q); _cimg_keycode(W);
_cimg_keycode(E); _cimg_keycode(R); _cimg_keycode(T); _cimg_keycode(Y);
_cimg_keycode(U); _cimg_keycode(I); _cimg_keycode(O); _cimg_keycode(P);
_cimg_keycode(DELETE); _cimg_keycode(END); _cimg_keycode(PAGEDOWN);
_cimg_keycode(CAPSLOCK); _cimg_keycode(A); _cimg_keycode(S); _cimg_keycode(D);
_cimg_keycode(F); _cimg_keycode(G); _cimg_keycode(H); _cimg_keycode(J);
_cimg_keycode(K); _cimg_keycode(L); _cimg_keycode(ENTER);
_cimg_keycode(SHIFTLEFT); _cimg_keycode(Z); _cimg_keycode(X); _cimg_keycode(C);
_cimg_keycode(V); _cimg_keycode(B); _cimg_keycode(N); _cimg_keycode(M);
_cimg_keycode(SHIFTRIGHT); _cimg_keycode(ARROWUP); _cimg_keycode(CTRLLEFT);
_cimg_keycode(APPLEFT); _cimg_keycode(ALT); _cimg_keycode(SPACE); _cimg_keycode(ALTGR);
_cimg_keycode(APPRIGHT); _cimg_keycode(MENU); _cimg_keycode(CTRLRIGHT);
_cimg_keycode(ARROWLEFT); _cimg_keycode(ARROWDOWN); _cimg_keycode(ARROWRIGHT);
_cimg_keycode(PAD0); _cimg_keycode(PAD1); _cimg_keycode(PAD2);
_cimg_keycode(PAD3); _cimg_keycode(PAD4); _cimg_keycode(PAD5);
_cimg_keycode(PAD6); _cimg_keycode(PAD7); _cimg_keycode(PAD8);
_cimg_keycode(PAD9); _cimg_keycode(PADADD); _cimg_keycode(PADSUB);
_cimg_keycode(PADMUL); _cimg_keycode(PADDIV);
return 0;
}

//! Return the current refresh rate, in frames per second.
/**
       \note Returns a significant value when the current instance is used to display successive frames.
       It measures the delay between successive calls to frames_per_second().
    **/
float frames_per_second() {
if (!_fps_timer) _fps_timer = cimg::time();
const float delta = (cimg::time() - _fps_timer)/1000.f;
++_fps_frames;
if (delta>=1) {
_fps_fps = _fps_frames/delta;
_fps_frames = 0;
_fps_timer = cimg::time();
}
return _fps_fps;
}

// Move current display window so that its content stays inside the current screen.
CImgDisplay& move_inside_screen() {
if (is_empty()) return *this;
const int
x0 = window_x(),
y0 = window_y(),
x1 = x0 + window_width() - 1,
y1 = y0 + window_height() - 1,
sw = CImgDisplay::screen_width(),
sh = CImgDisplay::screen_height();
if (x0<0 || y0<0 || x1>=sw || y1>=sh)
move(std::max(0,std::min(x0,sw - x1 + x0)),
std::max(0,std::min(y0,sh - y1 + y0)));
return *this;
}

//@}
//---------------------------------------
//
//! \name Window Manipulation
//@{
//---------------------------------------

#if cimg_display==0

//! Display image on associated window.
/**
       \param img Input image to display.
       \note This method returns immediately.
    **/
template<typename T>
CImgDisplay& display(const CImg<T>& img) {
return assign(img);
}

#endif

//! Display list of images on associated window.
/**
       \param list List of images to display.
       \param axis Axis used to append the images along, for the visualization (can be \c x, \c y, \c z or \c c).
       \param align Relative position of aligned images when displaying lists with images of different sizes
       (\c 0 for upper-left, \c 0.5 for centering and \c 1 for lower-right).
       \note This method returns immediately.
    **/
template<typename T>
CImgDisplay& display(const CImgList<T>& list, const char axis='x', const float align=0) {
if (list._width==1) {
const CImg<T>& img = list[0];
if (img._depth==1 && (img._spectrum==1 || img._spectrum>=3) && _normalization!=1) return display(img);
}
CImgList<typename CImg<T>::ucharT> visu(list._width);
unsigned int dims = 0;
cimglist_for(list,l) {
const CImg<T>& img = list._data[l];
img._get_select(*this,_normalization,(img._width - 1)/2,(img._height - 1)/2,
(img._depth - 1)/2).move_to(visu[l]);
dims = std::max(dims,visu[l]._spectrum);
}
cimglist_for(list,l) if (visu[l]._spectrum<dims) visu[l].resize(-100,-100,-100,dims,1);
visu.get_append(axis,align).display(*this);
return *this;
}

#if cimg_display==0

//! Show (closed) associated window on the screen.
/**
       \note
       - Force the associated window of a display to be visible on the screen, even if it has been closed before.
       - Using show() on a visible display does nothing.
    **/
CImgDisplay& show() {
return assign();
}

//! Close (visible) associated window and make it disappear from the screen.
/**
       \note
       - A closed display only means the associated window is not visible anymore. This does not mean the display has
       been destroyed.
       Use show() to make the associated window reappear.
       - Using close() on a closed display does nothing.
    **/
CImgDisplay& close() {
return assign();
}

//! Move associated window to a new location.
/**
       \param pos_x X-coordinate of the new window location.
       \param pos_y Y-coordinate of the new window location.
       \note Depending on the window manager behavior, this method may not succeed (no exceptions are thrown
       nevertheless).
    **/
CImgDisplay& move(const int pos_x, const int pos_y) {
return assign(pos_x,pos_y);
}

#endif

//! Resize display to the size of the associated window.
/**
       \param force_redraw Tells if the previous window content must be updated and refreshed as well.
       \note
       - Calling this method ensures that width() and window_width() become equal, as well as height() and
       window_height().
       - The associated window is also resized to specified dimensions.
    **/
CImgDisplay& resize(const bool force_redraw=true) {
resize(window_width(),window_height(),force_redraw);
return *this;
}

#if cimg_display==0

//! Resize display to the specified size.
/**
       \param width Requested display width.
       \param height Requested display height.
       \param force_redraw Tells if the previous window content must be updated and refreshed as well.
       \note The associated window is also resized to specified dimensions.
    **/
CImgDisplay& resize(const int width, const int height, const bool force_redraw=true) {
return assign(width,height,0,3,force_redraw);
}

#endif

//! Resize display to the size of an input image.
/**
       \param img Input image to take size from.
       \param force_redraw Tells if the previous window content must be resized and updated as well.
       \note
       - Calling this method ensures that width() and <tt>img.width()</tt> become equal, as well as height() and
       <tt>img.height()</tt>.
       - The associated window is also resized to specified dimensions.
    **/
template<typename T>
CImgDisplay& resize(const CImg<T>& img, const bool force_redraw=true) {
return resize(img._width,img._height,force_redraw);
}

//! Resize display to the size of another CImgDisplay instance.
/**
       \param disp Input display to take size from.
       \param force_redraw Tells if the previous window content must be resized and updated as well.
       \note
       - Calling this method ensures that width() and <tt>disp.width()</tt> become equal, as well as height() and
       <tt>disp.height()</tt>.
       - The associated window is also resized to specified dimensions.
    **/
CImgDisplay& resize(const CImgDisplay& disp, const bool force_redraw=true) {
return resize(disp.width(),disp.height(),force_redraw);
}

// [internal] Render pixel buffer with size (wd,hd) from source buffer of size (ws,hs).
template<typename t, typename T>
static void _render_resize(const T *ptrs, const unsigned int ws, const unsigned int hs,
t *ptrd, const unsigned int wd, const unsigned int hd) {
typedef typename cimg::last<T,cimg_ulong>::type ulongT;
const ulongT one = (ulongT)1;
CImg<ulongT> off_x(wd), off_y(hd + 1);
if (wd==ws) off_x.fill(1);
else {
ulongT *poff_x = off_x._data, curr = 0;
for (unsigned int x = 0; x<wd; ++x) {
const ulongT old = curr;
curr = (x + one)*ws/wd;
*(poff_x++) = curr - old;
}
}
if (hd==hs) off_y.fill(ws);
else {
ulongT *poff_y = off_y._data, curr = 0;
for (unsigned int y = 0; y<hd; ++y) {
const ulongT old = curr;
curr = (y + one)*hs/hd;
*(poff_y++) = ws*(curr - old);
}
*poff_y = 0;
}
ulongT *poff_y = off_y._data;
for (unsigned int y = 0; y<hd; ) {
const T *ptr = ptrs;
ulongT *poff_x = off_x._data;
for (unsigned int x = 0; x<wd; ++x) { *(ptrd++) = *ptr; ptr+=*(poff_x++); }
++y;
ulongT dy = *(poff_y++);
for ( ; !dy && y<hd; std::memcpy(ptrd,ptrd - wd,sizeof(t)*wd), ++y, ptrd+=wd, dy = *(poff_y++)) {}
ptrs+=dy;
}
}

//! Set normalization type.
/**
       \param normalization New normalization mode.
    **/
CImgDisplay& set_normalization(const unsigned int normalization) {
_normalization = normalization;
_min = _max = 0;
return *this;
}

#if cimg_display==0

//! Set title of the associated window.
/**
       \param format C-string containing the format of the title, as with <tt>std::printf()</tt>.
       \warning As the first argument is a format string, it is highly recommended to write
       \code
       disp.set_title("%s",window_title);
       \endcode
       instead of
       \code
       disp.set_title(window_title);
       \endcode
       if \c window_title can be arbitrary, to prevent nasty memory access.
    **/
CImgDisplay& set_title(const char *const format, ...) {
return assign(0,0,format);
}

#endif

//! Enable or disable fullscreen mode.
/**
       \param is_fullscreen Tells is the fullscreen mode must be activated or not.
       \param force_redraw Tells if the previous window content must be displayed as well.
       \note
       - When the fullscreen mode is enabled, the associated window fills the entire screen but the size of the
       current display is not modified.
       - The screen resolution may be switched to fit the associated window size and ensure it appears the largest
       as possible.
       For X-Window (X11) users, the configuration flag \c cimg_use_xrandr has to be set to allow the screen
       resolution change (requires the X11 extensions to be enabled).
    **/
CImgDisplay& set_fullscreen(const bool is_fullscreen, const bool force_redraw=true) {
if (is_empty() || _is_fullscreen==is_fullscreen) return *this;
return toggle_fullscreen(force_redraw);
}

#if cimg_display==0

//! Toggle fullscreen mode.
/**
       \param force_redraw Tells if the previous window content must be displayed as well.
       \note Enable fullscreen mode if it was not enabled, and disable it otherwise.
    **/
CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
return assign(_width,_height,0,3,force_redraw);
}

//! Show mouse pointer.
/**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
CImgDisplay& show_mouse() {
return assign();
}

//! Hide mouse pointer.
/**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
CImgDisplay& hide_mouse() {
return assign();
}

//! Move mouse pointer to a specified location.
/**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
CImgDisplay& set_mouse(const int pos_x, const int pos_y) {
return assign(pos_x,pos_y);
}

#endif

//! Simulate a mouse button release event.
/**
       \note All mouse buttons are considered released at the same time.
    **/
CImgDisplay& set_button() {
_button = 0;
_is_event = true;
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
return *this;
}

//! Simulate a mouse button press or release event.
/**
       \param button Buttons event code, where each button is associated to a single bit.
       \param is_pressed Tells if the mouse button is considered as pressed or released.
    **/
CImgDisplay& set_button(const unsigned int button, const bool is_pressed=true) {
const unsigned int buttoncode = button==1U?1U:button==2U?2U:button==3U?4U:0U;
if (is_pressed) _button |= buttoncode; else _button &= ~buttoncode;
_is_event = buttoncode?true:false;
if (buttoncode) {
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
}
return *this;
}

//! Flush all mouse wheel events.
/**
       \note Make wheel() to return \c 0, if called afterwards.
    **/
CImgDisplay& set_wheel() {
_wheel = 0;
_is_event = true;
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
return *this;
}

//! Simulate a wheel event.
/**
       \param amplitude Amplitude of the wheel scrolling to simulate.
       \note Make wheel() to return \c amplitude, if called afterwards.
    **/
CImgDisplay& set_wheel(const int amplitude) {
_wheel+=amplitude;
_is_event = amplitude?true:false;
if (amplitude) {
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
}
return *this;
}

//! Flush all key events.
/**
       \note Make key() to return \c 0, if called afterwards.
    **/
CImgDisplay& set_key() {
std::memset((void*)_keys,0,128*sizeof(unsigned int));
std::memset((void*)_released_keys,0,128*sizeof(unsigned int));
_is_keyESC = _is_keyF1 = _is_keyF2 = _is_keyF3 = _is_keyF4 = _is_keyF5 = _is_keyF6 = _is_keyF7 = _is_keyF8 =
_is_keyF9 = _is_keyF10 = _is_keyF11 = _is_keyF12 = _is_keyPAUSE = _is_key1 = _is_key2 = _is_key3 = _is_key4 =
_is_key5 = _is_key6 = _is_key7 = _is_key8 = _is_key9 = _is_key0 = _is_keyBACKSPACE = _is_keyINSERT =
_is_keyHOME = _is_keyPAGEUP = _is_keyTAB = _is_keyQ = _is_keyW = _is_keyE = _is_keyR = _is_keyT = _is_keyY =
_is_keyU = _is_keyI = _is_keyO = _is_keyP = _is_keyDELETE = _is_keyEND = _is_keyPAGEDOWN = _is_keyCAPSLOCK =
_is_keyA = _is_keyS = _is_keyD = _is_keyF = _is_keyG = _is_keyH = _is_keyJ = _is_keyK = _is_keyL =
_is_keyENTER = _is_keySHIFTLEFT = _is_keyZ = _is_keyX = _is_keyC = _is_keyV = _is_keyB = _is_keyN =
_is_keyM = _is_keySHIFTRIGHT = _is_keyARROWUP = _is_keyCTRLLEFT = _is_keyAPPLEFT = _is_keyALT = _is_keySPACE =
_is_keyALTGR = _is_keyAPPRIGHT = _is_keyMENU = _is_keyCTRLRIGHT = _is_keyARROWLEFT = _is_keyARROWDOWN =
_is_keyARROWRIGHT = _is_keyPAD0 = _is_keyPAD1 = _is_keyPAD2 = _is_keyPAD3 = _is_keyPAD4 = _is_keyPAD5 =
_is_keyPAD6 = _is_keyPAD7 = _is_keyPAD8 = _is_keyPAD9 = _is_keyPADADD = _is_keyPADSUB = _is_keyPADMUL =
_is_keyPADDIV = false;
_is_event = true;
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
return *this;
}

//! Simulate a keyboard press/release event.
/**
       \param keycode Keycode of the associated key.
       \param is_pressed Tells if the key is considered as pressed or released.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
CImgDisplay& set_key(const unsigned int keycode, const bool is_pressed=true) {
#define _cimg_set_key(k) if (keycode==cimg::key##k) _is_key##k = is_pressed;
_cimg_set_key(ESC); _cimg_set_key(F1); _cimg_set_key(F2); _cimg_set_key(F3);
_cimg_set_key(F4); _cimg_set_key(F5); _cimg_set_key(F6); _cimg_set_key(F7);
_cimg_set_key(F8); _cimg_set_key(F9); _cimg_set_key(F10); _cimg_set_key(F11);
_cimg_set_key(F12); _cimg_set_key(PAUSE); _cimg_set_key(1); _cimg_set_key(2);
_cimg_set_key(3); _cimg_set_key(4); _cimg_set_key(5); _cimg_set_key(6);
_cimg_set_key(7); _cimg_set_key(8); _cimg_set_key(9); _cimg_set_key(0);
_cimg_set_key(BACKSPACE); _cimg_set_key(INSERT); _cimg_set_key(HOME);
_cimg_set_key(PAGEUP); _cimg_set_key(TAB); _cimg_set_key(Q); _cimg_set_key(W);
_cimg_set_key(E); _cimg_set_key(R); _cimg_set_key(T); _cimg_set_key(Y);
_cimg_set_key(U); _cimg_set_key(I); _cimg_set_key(O); _cimg_set_key(P);
_cimg_set_key(DELETE); _cimg_set_key(END); _cimg_set_key(PAGEDOWN);
_cimg_set_key(CAPSLOCK); _cimg_set_key(A); _cimg_set_key(S); _cimg_set_key(D);
_cimg_set_key(F); _cimg_set_key(G); _cimg_set_key(H); _cimg_set_key(J);
_cimg_set_key(K); _cimg_set_key(L); _cimg_set_key(ENTER);
_cimg_set_key(SHIFTLEFT); _cimg_set_key(Z); _cimg_set_key(X); _cimg_set_key(C);
_cimg_set_key(V); _cimg_set_key(B); _cimg_set_key(N); _cimg_set_key(M);
_cimg_set_key(SHIFTRIGHT); _cimg_set_key(ARROWUP); _cimg_set_key(CTRLLEFT);
_cimg_set_key(APPLEFT); _cimg_set_key(ALT); _cimg_set_key(SPACE); _cimg_set_key(ALTGR);
_cimg_set_key(APPRIGHT); _cimg_set_key(MENU); _cimg_set_key(CTRLRIGHT);
_cimg_set_key(ARROWLEFT); _cimg_set_key(ARROWDOWN); _cimg_set_key(ARROWRIGHT);
_cimg_set_key(PAD0); _cimg_set_key(PAD1); _cimg_set_key(PAD2);
_cimg_set_key(PAD3); _cimg_set_key(PAD4); _cimg_set_key(PAD5);
_cimg_set_key(PAD6); _cimg_set_key(PAD7); _cimg_set_key(PAD8);
_cimg_set_key(PAD9); _cimg_set_key(PADADD); _cimg_set_key(PADSUB);
_cimg_set_key(PADMUL); _cimg_set_key(PADDIV);
if (is_pressed) {
if (*_keys)
std::memmove((void*)(_keys + 1),(void*)_keys,127*sizeof(unsigned int));
*_keys = keycode;
if (*_released_keys) {
std::memmove((void*)(_released_keys + 1),(void*)_released_keys,127*sizeof(unsigned int));
*_released_keys = 0;
}
} else {
if (*_keys) {
std::memmove((void*)(_keys + 1),(void*)_keys,127*sizeof(unsigned int));
*_keys = 0;
}
if (*_released_keys)
std::memmove((void*)(_released_keys + 1),(void*)_released_keys,127*sizeof(unsigned int));
*_released_keys = keycode;
}
_is_event = keycode?true:false;
if (keycode) {
#if cimg_display==1
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
SetEvent(cimg::Win32_attr().wait_event);
#endif
}
return *this;
}

//! Flush all display events.
/**
       \note Remove all passed events from the current display.
    **/
CImgDisplay& flush() {
set_key().set_button().set_wheel();
_is_resized = _is_moved = _is_event = false;
_fps_timer = _fps_frames = _timer = 0;
_fps_fps = 0;
return *this;
}

//! Wait for any user event occuring on the current display.
CImgDisplay& wait() {
wait(*this);
return *this;
}

//! Wait for a given number of milliseconds since the last call to wait().
/**
       \param milliseconds Number of milliseconds to wait for.
       \note Similar to cimg::wait().
    **/
CImgDisplay& wait(const unsigned int milliseconds) {
cimg::wait(milliseconds,&_timer);
return *this;
}

//! Wait for any event occuring on the display \c disp1.
static void wait(CImgDisplay& disp1) {
disp1._is_event = false;
while (!disp1._is_closed && !disp1._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1 or \c disp2.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2) {
disp1._is_event = disp2._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed) &&
!disp1._is_event && !disp2._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2 or \c disp3.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3) {
disp1._is_event = disp2._is_event = disp3._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3 or \c disp4.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4 or \c disp5.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4,
CImgDisplay& disp5) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event)
wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp6.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
CImgDisplay& disp6) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
disp6._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
!disp6._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
!disp6._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp7.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
CImgDisplay& disp6, CImgDisplay& disp7) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
disp6._is_event = disp7._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
!disp6._is_closed || !disp7._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
!disp6._is_event && !disp7._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp8.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
disp6._is_event = disp7._is_event = disp8._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
!disp6._is_closed || !disp7._is_closed || !disp8._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
!disp6._is_event && !disp7._is_event && !disp8._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp9.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8, CImgDisplay& disp9) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
disp6._is_event = disp7._is_event = disp8._is_event = disp9._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
!disp6._is_closed || !disp7._is_closed || !disp8._is_closed || !disp9._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
!disp6._is_event && !disp7._is_event && !disp8._is_event && !disp9._is_event) wait_all();
}

//! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp10.
static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8, CImgDisplay& disp9,
CImgDisplay& disp10) {
disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
disp6._is_event = disp7._is_event = disp8._is_event = disp9._is_event = disp10._is_event = false;
while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
!disp6._is_closed || !disp7._is_closed || !disp8._is_closed || !disp9._is_closed || !disp10._is_closed) &&
!disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
!disp6._is_event && !disp7._is_event && !disp8._is_event && !disp9._is_event && !disp10._is_event)
wait_all();
}

#if cimg_display==0

//! Wait for any window event occuring in any opened CImgDisplay.
static void wait_all() {
return _no_display_exception();
}

//! Render image into internal display buffer.
/**
       \param img Input image data to render.
       \note
       - Convert image data representation into the internal display buffer (architecture-dependent structure).
       - The content of the associated window is not modified, until paint() is called.
       - Should not be used for common CImgDisplay uses, since display() is more useful.
    **/
template<typename T>
CImgDisplay& render(const CImg<T>& img) {
return assign(img);
}

//! Paint internal display buffer on associated window.
/**
       \note
       - Update the content of the associated window with the internal display buffer, e.g. after a render() call.
       - Should not be used for common CImgDisplay uses, since display() is more useful.
    **/
CImgDisplay& paint() {
return assign();
}


//! Take a snapshot of the current screen content.
/**
       \param x0 X-coordinate of the upper left corner.
       \param y0 Y-coordinate of the upper left corner.
       \param x1 X-coordinate of the lower right corner.
       \param y1 Y-coordinate of the lower right corner.
       \param[out] img Output screenshot. Can be empty on input
    **/
template<typename T>
static void screenshot(const int x0, const int y0, const int x1, const int y1, CImg<T>& img) {
cimg::unused(x0,y0,x1,y1,&img);
_no_display_exception();
}

//! Take a snapshot of the associated window content.
/**
       \param[out] img Output snapshot. Can be empty on input.
    **/
template<typename T>
const CImgDisplay& snapshot(CImg<T>& img) const {
cimg::unused(img);
_no_display_exception();
return *this;
}
#endif

// X11-based implementation
//--------------------------
#if cimg_display==1

Atom _wm_window_atom, _wm_protocol_atom;
Window _window, _background_window;
Colormap _colormap;
XImage *_image;
void *_data;

#ifdef cimg_use_xshm
XShmSegmentInfo *_shminfo;
#endif

static int screen_width() {
Display *const dpy = cimg::X11_attr().display;
int res = 0;
if (!dpy) {
Display *const _dpy = XOpenDisplay(0);
if (!_dpy)
throw CImgDisplayException("CImgDisplay::screen_width(): Failed to open X11 display.");
res = DisplayWidth(_dpy,DefaultScreen(_dpy));
XCloseDisplay(_dpy);
} else {

#ifdef cimg_use_xrandr
if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution)
res = cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].width;
else res = DisplayWidth(dpy,DefaultScreen(dpy));
#else
res = DisplayWidth(dpy,DefaultScreen(dpy));
#endif
}
return res;
}

static int screen_height() {
Display *const dpy = cimg::X11_attr().display;
int res = 0;
if (!dpy) {
Display *const _dpy = XOpenDisplay(0);
if (!_dpy)
throw CImgDisplayException("CImgDisplay::screen_height(): Failed to open X11 display.");
res = DisplayHeight(_dpy,DefaultScreen(_dpy));
XCloseDisplay(_dpy);
} else {

#ifdef cimg_use_xrandr
if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution)
res = cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].height;
else res = DisplayHeight(dpy,DefaultScreen(dpy));
#else
res = DisplayHeight(dpy,DefaultScreen(dpy));
#endif
}
return res;
}

static void wait_all() {
if (!cimg::X11_attr().display) return;
pthread_mutex_lock(&cimg::X11_attr().wait_event_mutex);
pthread_cond_wait(&cimg::X11_attr().wait_event,&cimg::X11_attr().wait_event_mutex);
pthread_mutex_unlock(&cimg::X11_attr().wait_event_mutex);
}

void _handle_events(const XEvent *const pevent) {
Display *const dpy = cimg::X11_attr().display;
XEvent event = *pevent;
switch (event.type) {
case ClientMessage : {
if ((int)event.xclient.message_type==(int)_wm_protocol_atom &&
(int)event.xclient.data.l[0]==(int)_wm_window_atom) {
XUnmapWindow(cimg::X11_attr().display,_window);
_is_closed = _is_event = true;
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
}
} break;
case ConfigureNotify : {
while (XCheckWindowEvent(dpy,_window,StructureNotifyMask,&event)) {}
const unsigned int nw = event.xconfigure.width, nh = event.xconfigure.height;
const int nx = event.xconfigure.x, ny = event.xconfigure.y;
if (nw && nh && (nw!=_window_width || nh!=_window_height)) {
_window_width = nw; _window_height = nh; _mouse_x = _mouse_y = -1;
XResizeWindow(dpy,_window,_window_width,_window_height);
_is_resized = _is_event = true;
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
}
if (nx!=_window_x || ny!=_window_y) {
_window_x = nx; _window_y = ny; _is_moved = _is_event = true;
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
}
} break;
case Expose : {
while (XCheckWindowEvent(dpy,_window,ExposureMask,&event)) {}
_paint(false);
if (_is_fullscreen) {
XWindowAttributes attr;
XGetWindowAttributes(dpy,_window,&attr);
while (attr.map_state!=IsViewable) XSync(dpy,0);
XSetInputFocus(dpy,_window,RevertToParent,CurrentTime);
}
} break;
case ButtonPress : {
do {
_mouse_x = event.xmotion.x; _mouse_y = event.xmotion.y;
if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
switch (event.xbutton.button) {
case 1 : set_button(1); break;
case 3 : set_button(2); break;
case 2 : set_button(3); break;
}
} while (XCheckWindowEvent(dpy,_window,ButtonPressMask,&event));
} break;
case ButtonRelease : {
do {
_mouse_x = event.xmotion.x; _mouse_y = event.xmotion.y;
if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
switch (event.xbutton.button) {
case 1 : set_button(1,false); break;
case 3 : set_button(2,false); break;
case 2 : set_button(3,false); break;
case 4 : set_wheel(1); break;
case 5 : set_wheel(-1); break;
}
} while (XCheckWindowEvent(dpy,_window,ButtonReleaseMask,&event));
} break;
case KeyPress : {
char tmp = 0; KeySym ksym;
XLookupString(&event.xkey,&tmp,1,&ksym,0);
set_key((unsigned int)ksym,true);
} break;
case KeyRelease : {
char keys_return[32];  // Check that the key has been physically unpressed
XQueryKeymap(dpy,keys_return);
const unsigned int kc = event.xkey.keycode, kc1 = kc/8, kc2 = kc%8;
const bool is_key_pressed = kc1>=32?false:(keys_return[kc1]>>kc2)&1;
if (!is_key_pressed) {
char tmp = 0; KeySym ksym;
XLookupString(&event.xkey,&tmp,1,&ksym,0);
set_key((unsigned int)ksym,false);
}
} break;
case EnterNotify: {
while (XCheckWindowEvent(dpy,_window,EnterWindowMask,&event)) {}
_mouse_x = event.xmotion.x;
_mouse_y = event.xmotion.y;
if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
} break;
case LeaveNotify : {
while (XCheckWindowEvent(dpy,_window,LeaveWindowMask,&event)) {}
_mouse_x = _mouse_y = -1; _is_event = true;
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
} break;
case MotionNotify : {
while (XCheckWindowEvent(dpy,_window,PointerMotionMask,&event)) {}
_mouse_x = event.xmotion.x;
_mouse_y = event.xmotion.y;
if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
_is_event = true;
pthread_cond_broadcast(&cimg::X11_attr().wait_event);
} break;
}
}

static void* _events_thread(void *arg) { // Thread to manage events for all opened display windows
Display *const dpy = cimg::X11_attr().display;
XEvent event;
pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,0);
pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,0);
if (!arg) for ( ; ; ) {
cimg_lock_display();
bool event_flag = XCheckTypedEvent(dpy,ClientMessage,&event);
if (!event_flag) event_flag = XCheckMaskEvent(dpy,
ExposureMask | StructureNotifyMask | ButtonPressMask |
KeyPressMask | PointerMotionMask | EnterWindowMask |
LeaveWindowMask | ButtonReleaseMask | KeyReleaseMask,&event);
if (event_flag)
for (unsigned int i = 0; i<cimg::X11_attr().nb_wins; ++i)
if (!cimg::X11_attr().wins[i]->_is_closed && event.xany.window==cimg::X11_attr().wins[i]->_window)
cimg::X11_attr().wins[i]->_handle_events(&event);
cimg_unlock_display();
pthread_testcancel();
cimg::sleep(8);
}
return 0;
}

void _set_colormap(Colormap& _colormap, const unsigned int dim) {
XColor *const colormap = new XColor[256];
switch (dim) {
case 1 : { // colormap for greyscale images
for (unsigned int index = 0; index<256; ++index) {
colormap[index].pixel = index;
colormap[index].red = colormap[index].green = colormap[index].blue = (unsigned short)(index<<8);
colormap[index].flags = DoRed | DoGreen | DoBlue;
}
} break;
case 2 : { // colormap for RG images
for (unsigned int index = 0, r = 8; r<256; r+=16)
for (unsigned int g = 8; g<256; g+=16) {
colormap[index].pixel = index;
colormap[index].red = colormap[index].blue = (unsigned short)(r<<8);
colormap[index].green = (unsigned short)(g<<8);
colormap[index++].flags = DoRed | DoGreen | DoBlue;
}
} break;
default : { // colormap for RGB images
for (unsigned int index = 0, r = 16; r<256; r+=32)
for (unsigned int g = 16; g<256; g+=32)
for (unsigned int b = 32; b<256; b+=64) {
colormap[index].pixel = index;
colormap[index].red = (unsigned short)(r<<8);
colormap[index].green = (unsigned short)(g<<8);
colormap[index].blue = (unsigned short)(b<<8);
colormap[index++].flags = DoRed | DoGreen | DoBlue;
}
}
}
XStoreColors(cimg::X11_attr().display,_colormap,colormap,256);
delete[] colormap;
}

void _map_window() {
Display *const dpy = cimg::X11_attr().display;
bool is_exposed = false, is_mapped = false;
XWindowAttributes attr;
XEvent event;
XMapRaised(dpy,_window);
do { // Wait for the window to be mapped
XWindowEvent(dpy,_window,StructureNotifyMask | ExposureMask,&event);
switch (event.type) {
case MapNotify : is_mapped = true; break;
case Expose : is_exposed = true; break;
}
} while (!is_exposed || !is_mapped);
do { // Wait for the window to be visible
XGetWindowAttributes(dpy,_window,&attr);
if (attr.map_state!=IsViewable) { XSync(dpy,0); cimg::sleep(10); }
} while (attr.map_state!=IsViewable);
_window_x = attr.x;
_window_y = attr.y;
}

void _paint(const bool wait_expose=true) {
if (_is_closed || !_image) return;
Display *const dpy = cimg::X11_attr().display;
if (wait_expose) { // Send an expose event sticked to display window to force repaint
XEvent event;
event.xexpose.type = Expose;
event.xexpose.serial = 0;
event.xexpose.send_event = 1;
event.xexpose.display = dpy;
event.xexpose.window = _window;
event.xexpose.x = 0;
event.xexpose.y = 0;
event.xexpose.width = width();
event.xexpose.height = height();
event.xexpose.count = 0;
XSendEvent(dpy,_window,0,0,&event);
} else { // Repaint directly (may be called from the expose event)
GC gc = DefaultGC(dpy,DefaultScreen(dpy));

#ifdef cimg_use_xshm
if (_shminfo) XShmPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height,1);
else XPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height);
#else
XPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height);
#endif
}
}

template<typename T>
void _resize(T pixel_type, const unsigned int ndimx, const unsigned int ndimy, const bool force_redraw) {
Display *const dpy = cimg::X11_attr().display;
cimg::unused(pixel_type);

#ifdef cimg_use_xshm
if (_shminfo) {
XShmSegmentInfo *const nshminfo = new XShmSegmentInfo;
XImage *const nimage = XShmCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),
cimg::X11_attr().nb_bits,ZPixmap,0,nshminfo,ndimx,ndimy);
if (!nimage) { delete nshminfo; return; }
else {
nshminfo->shmid = shmget(IPC_PRIVATE,ndimx*ndimy*sizeof(T),IPC_CREAT | 0777);
if (nshminfo->shmid==-1) { XDestroyImage(nimage); delete nshminfo; return; }
else {
nshminfo->shmaddr = nimage->data = (char*)shmat(nshminfo->shmid,0,0);
if (nshminfo->shmaddr==(char*)-1) {
shmctl(nshminfo->shmid,IPC_RMID,0); XDestroyImage(nimage); delete nshminfo; return;
} else {
nshminfo->readOnly = 0;
cimg::X11_attr().is_shm_enabled = true;
XErrorHandler oldXErrorHandler = XSetErrorHandler(_assign_xshm);
XShmAttach(dpy,nshminfo);
XFlush(dpy);
XSetErrorHandler(oldXErrorHandler);
if (!cimg::X11_attr().is_shm_enabled) {
shmdt(nshminfo->shmaddr);
shmctl(nshminfo->shmid,IPC_RMID,0);
XDestroyImage(nimage);
delete nshminfo;
return;
} else {
T *const ndata = (T*)nimage->data;
if (force_redraw) _render_resize((T*)_data,_width,_height,ndata,ndimx,ndimy);
else std::memset(ndata,0,sizeof(T)*ndimx*ndimy);
XShmDetach(dpy,_shminfo);
XDestroyImage(_image);
shmdt(_shminfo->shmaddr);
shmctl(_shminfo->shmid,IPC_RMID,0);
delete _shminfo;
_shminfo = nshminfo;
_image = nimage;
_data = (void*)ndata;
}
}
}
}
} else
#endif
{
T *ndata = (T*)std::malloc(ndimx*ndimy*sizeof(T));
if (force_redraw) _render_resize((T*)_data,_width,_height,ndata,ndimx,ndimy);
else std::memset(ndata,0,sizeof(T)*ndimx*ndimy);
_data = (void*)ndata;
XDestroyImage(_image);
_image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),
cimg::X11_attr().nb_bits,ZPixmap,0,(char*)_data,ndimx,ndimy,8,0);
}
}

void _init_fullscreen() {
if (!_is_fullscreen || _is_closed) return;
Display *const dpy = cimg::X11_attr().display;
_background_window = 0;

#ifdef cimg_use_xrandr
int foo;
if (XRRQueryExtension(dpy,&foo,&foo)) {
XRRRotations(dpy,DefaultScreen(dpy),&cimg::X11_attr().curr_rotation);
if (!cimg::X11_attr().resolutions) {
cimg::X11_attr().resolutions = XRRSizes(dpy,DefaultScreen(dpy),&foo);
cimg::X11_attr().nb_resolutions = (unsigned int)foo;
}
if (cimg::X11_attr().resolutions) {
cimg::X11_attr().curr_resolution = 0;
for (unsigned int i = 0; i<cimg::X11_attr().nb_resolutions; ++i) {
const unsigned int
nw = (unsigned int)(cimg::X11_attr().resolutions[i].width),
nh = (unsigned int)(cimg::X11_attr().resolutions[i].height);
if (nw>=_width && nh>=_height &&
nw<=(unsigned int)(cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].width) &&
nh<=(unsigned int)(cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].height))
cimg::X11_attr().curr_resolution = i;
}
if (cimg::X11_attr().curr_resolution>0) {
XRRScreenConfiguration *config = XRRGetScreenInfo(dpy,DefaultRootWindow(dpy));
XRRSetScreenConfig(dpy,config,DefaultRootWindow(dpy),
cimg::X11_attr().curr_resolution,cimg::X11_attr().curr_rotation,CurrentTime);
XRRFreeScreenConfigInfo(config);
XSync(dpy,0);
}
}
}
if (!cimg::X11_attr().resolutions)
cimg::warn(_cimgdisplay_instance
"init_fullscreen(): Xrandr extension not supported by the X server.",
cimgdisplay_instance);
#endif

const unsigned int sx = screen_width(), sy = screen_height();
if (sx==_width && sy==_height) return;
XSetWindowAttributes winattr;
winattr.override_redirect = 1;
_background_window = XCreateWindow(dpy,DefaultRootWindow(dpy),0,0,sx,sy,0,0,
InputOutput,CopyFromParent,CWOverrideRedirect,&winattr);
const cimg_ulong buf_size = (cimg_ulong)sx*sy*(cimg::X11_attr().nb_bits==8?1:
(cimg::X11_attr().nb_bits==16?2:4));
void *background_data = std::malloc(buf_size);
std::memset(background_data,0,buf_size);
XImage *background_image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
ZPixmap,0,(char*)background_data,sx,sy,8,0);
XEvent event;
XSelectInput(dpy,_background_window,StructureNotifyMask);
XMapRaised(dpy,_background_window);
do XWindowEvent(dpy,_background_window,StructureNotifyMask,&event);
while (event.type!=MapNotify);
GC gc = DefaultGC(dpy,DefaultScreen(dpy));

#ifdef cimg_use_xshm
if (_shminfo) XShmPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy,0);
else XPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy);
#else
XPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy);
#endif
XWindowAttributes attr;
XGetWindowAttributes(dpy,_background_window,&attr);
while (attr.map_state!=IsViewable) XSync(dpy,0);
XDestroyImage(background_image);
}

void _desinit_fullscreen() {
if (!_is_fullscreen) return;
Display *const dpy = cimg::X11_attr().display;
XUngrabKeyboard(dpy,CurrentTime);

#ifdef cimg_use_xrandr
if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution) {
XRRScreenConfiguration *config = XRRGetScreenInfo(dpy,DefaultRootWindow(dpy));
XRRSetScreenConfig(dpy,config,DefaultRootWindow(dpy),0,cimg::X11_attr().curr_rotation,CurrentTime);
XRRFreeScreenConfigInfo(config);
XSync(dpy,0);
cimg::X11_attr().curr_resolution = 0;
}
#endif
if (_background_window) XDestroyWindow(dpy,_background_window);
_background_window = 0;
_is_fullscreen = false;
}

static int _assign_xshm(Display *dpy, XErrorEvent *error) {
cimg::unused(dpy,error);
cimg::X11_attr().is_shm_enabled = false;
return 0;
}

void _assign(const unsigned int dimw, const unsigned int dimh, const char *const ptitle=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
cimg::mutex(14);

// Allocate space for window title
const char *const nptitle = ptitle?ptitle:"";
const unsigned int s = (unsigned int)std::strlen(nptitle) + 1;
char *const tmp_title = s?new char[s]:0;
if (s) std::memcpy(tmp_title,nptitle,s*sizeof(char));

// Destroy previous display window if existing
if (!is_empty()) assign();

// Open X11 display and retrieve graphical properties.
Display* &dpy = cimg::X11_attr().display;
if (!dpy) {
dpy = XOpenDisplay(0);
if (!dpy)
throw CImgDisplayException(_cimgdisplay_instance
"assign(): Failed to open X11 display.",
cimgdisplay_instance);

cimg::X11_attr().nb_bits = DefaultDepth(dpy,DefaultScreen(dpy));
if (cimg::X11_attr().nb_bits!=8 && cimg::X11_attr().nb_bits!=16 &&
cimg::X11_attr().nb_bits!=24 && cimg::X11_attr().nb_bits!=32)
throw CImgDisplayException(_cimgdisplay_instance
"assign(): Invalid %u bits screen mode detected "
"(only 8, 16, 24 and 32 bits modes are managed).",
cimgdisplay_instance,
cimg::X11_attr().nb_bits);
XVisualInfo vtemplate;
vtemplate.visualid = XVisualIDFromVisual(DefaultVisual(dpy,DefaultScreen(dpy)));
int nb_visuals;
XVisualInfo *vinfo = XGetVisualInfo(dpy,VisualIDMask,&vtemplate,&nb_visuals);
if (vinfo && vinfo->red_mask<vinfo->blue_mask) cimg::X11_attr().is_blue_first = true;
cimg::X11_attr().byte_order = ImageByteOrder(dpy);
XFree(vinfo);

cimg_lock_display();
cimg::X11_attr().events_thread = new pthread_t;
pthread_create(cimg::X11_attr().events_thread,0,_events_thread,0);
} else cimg_lock_display();

// Set display variables.
_width = std::min(dimw,(unsigned int)screen_width());
_height = std::min(dimh,(unsigned int)screen_height());
_normalization = normalization_type<4?normalization_type:3;
_is_fullscreen = fullscreen_flag;
_window_x = _window_y = 0;
_is_closed = closed_flag;
_title = tmp_title;
flush();

// Create X11 window (and LUT, if 8bits display)
if (_is_fullscreen) {
if (!_is_closed) _init_fullscreen();
const unsigned int sx = screen_width(), sy = screen_height();
XSetWindowAttributes winattr;
winattr.override_redirect = 1;
_window = XCreateWindow(dpy,DefaultRootWindow(dpy),(sx - _width)/2,(sy - _height)/2,_width,_height,0,0,
InputOutput,CopyFromParent,CWOverrideRedirect,&winattr);
} else
_window = XCreateSimpleWindow(dpy,DefaultRootWindow(dpy),0,0,_width,_height,0,0L,0L);

XSelectInput(dpy,_window,
ExposureMask | StructureNotifyMask | ButtonPressMask | KeyPressMask | PointerMotionMask |
EnterWindowMask | LeaveWindowMask | ButtonReleaseMask | KeyReleaseMask);

XStoreName(dpy,_window,_title?_title:" ");
if (cimg::X11_attr().nb_bits==8) {
_colormap = XCreateColormap(dpy,_window,DefaultVisual(dpy,DefaultScreen(dpy)),AllocAll);
_set_colormap(_colormap,3);
XSetWindowColormap(dpy,_window,_colormap);
}

static const char *const _window_class = cimg_appname;
XClassHint *const window_class = XAllocClassHint();
window_class->res_name = (char*)_window_class;
window_class->res_class = (char*)_window_class;
XSetClassHint(dpy,_window,window_class);
XFree(window_class);

_window_width = _width;
_window_height = _height;

// Create XImage
#ifdef cimg_use_xshm
_shminfo = 0;
if (XShmQueryExtension(dpy)) {
_shminfo = new XShmSegmentInfo;
_image = XShmCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
ZPixmap,0,_shminfo,_width,_height);
if (!_image) { delete _shminfo; _shminfo = 0; }
else {
_shminfo->shmid = shmget(IPC_PRIVATE,_image->bytes_per_line*_image->height,IPC_CREAT|0777);
if (_shminfo->shmid==-1) { XDestroyImage(_image); delete _shminfo; _shminfo = 0; }
else {
_shminfo->shmaddr = _image->data = (char*)(_data = shmat(_shminfo->shmid,0,0));
if (_shminfo->shmaddr==(char*)-1) {
shmctl(_shminfo->shmid,IPC_RMID,0); XDestroyImage(_image); delete _shminfo; _shminfo = 0;
} else {
_shminfo->readOnly = 0;
cimg::X11_attr().is_shm_enabled = true;
XErrorHandler oldXErrorHandler = XSetErrorHandler(_assign_xshm);
XShmAttach(dpy,_shminfo);
XSync(dpy,0);
XSetErrorHandler(oldXErrorHandler);
if (!cimg::X11_attr().is_shm_enabled) {
shmdt(_shminfo->shmaddr); shmctl(_shminfo->shmid,IPC_RMID,0); XDestroyImage(_image);
delete _shminfo; _shminfo = 0;
}
}
}
}
}
if (!_shminfo)
#endif
{
const cimg_ulong buf_size = (cimg_ulong)_width*_height*(cimg::X11_attr().nb_bits==8?1:
(cimg::X11_attr().nb_bits==16?2:4));
_data = std::malloc(buf_size);
_image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
ZPixmap,0,(char*)_data,_width,_height,8,0);
}

_wm_window_atom = XInternAtom(dpy,"WM_DELETE_WINDOW",0);
_wm_protocol_atom = XInternAtom(dpy,"WM_PROTOCOLS",0);
XSetWMProtocols(dpy,_window,&_wm_window_atom,1);

if (_is_fullscreen) XGrabKeyboard(dpy,_window,1,GrabModeAsync,GrabModeAsync,CurrentTime);
cimg::X11_attr().wins[cimg::X11_attr().nb_wins++]=this;
if (!_is_closed) _map_window(); else { _window_x = _window_y = cimg::type<int>::min(); }
cimg_unlock_display();
cimg::mutex(14,0);
}

CImgDisplay& assign() {
if (is_empty()) return flush();
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();

// Remove display window from event thread list.
unsigned int i;
for (i = 0; i<cimg::X11_attr().nb_wins && cimg::X11_attr().wins[i]!=this; ++i) {}
for ( ; i<cimg::X11_attr().nb_wins - 1; ++i) cimg::X11_attr().wins[i] = cimg::X11_attr().wins[i + 1];
--cimg::X11_attr().nb_wins;

// Destroy window, image, colormap and title.
if (_is_fullscreen && !_is_closed) _desinit_fullscreen();
XDestroyWindow(dpy,_window);
_window = 0;

#ifdef cimg_use_xshm
if (_shminfo) {
XShmDetach(dpy,_shminfo);
XDestroyImage(_image);
shmdt(_shminfo->shmaddr);
shmctl(_shminfo->shmid,IPC_RMID,0);
delete _shminfo;
_shminfo = 0;
} else
#endif
XDestroyImage(_image);
_data = 0; _image = 0;
if (cimg::X11_attr().nb_bits==8) XFreeColormap(dpy,_colormap);
_colormap = 0;
XSync(dpy,0);

// Reset display variables.
delete[] _title;
_width = _height = _normalization = _window_width = _window_height = 0;
_window_x = _window_y = 0;
_is_fullscreen = false;
_is_closed = true;
_min = _max = 0;
_title = 0;
flush();

cimg_unlock_display();
return *this;
}

CImgDisplay& assign(const unsigned int dimw, const unsigned int dimh, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!dimw || !dimh) return assign();
_assign(dimw,dimh,title,normalization_type,fullscreen_flag,closed_flag);
_min = _max = 0;
std::memset(_data,0,(cimg::X11_attr().nb_bits==8?sizeof(unsigned char):
(cimg::X11_attr().nb_bits==16?sizeof(unsigned short):sizeof(unsigned int)))*
(size_t)_width*_height);
return paint();
}

template<typename T>
CImgDisplay& assign(const CImg<T>& img, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!img) return assign();
CImg<T> tmp;
const CImg<T>& nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
(img._height - 1)/2,
(img._depth - 1)/2));
_assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
if (_normalization==2) _min = (float)nimg.min_max(_max);
return render(nimg).paint();
}

template<typename T>
CImgDisplay& assign(const CImgList<T>& list, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!list) return assign();
CImg<T> tmp;
const CImg<T> img = list>'x', &nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
(img._height - 1)/2,
(img._depth - 1)/2));
_assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
if (_normalization==2) _min = (float)nimg.min_max(_max);
return render(nimg).paint();
}

CImgDisplay& assign(const CImgDisplay& disp) {
if (!disp) return assign();
_assign(disp._width,disp._height,disp._title,disp._normalization,disp._is_fullscreen,disp._is_closed);
std::memcpy(_data,disp._data,(cimg::X11_attr().nb_bits==8?sizeof(unsigned char):
cimg::X11_attr().nb_bits==16?sizeof(unsigned short):
sizeof(unsigned int))*(size_t)_width*_height);
return paint();
}

CImgDisplay& resize(const int nwidth, const int nheight, const bool force_redraw=true) {
if (!nwidth || !nheight || (is_empty() && (nwidth<0 || nheight<0))) return assign();
if (is_empty()) return assign(nwidth,nheight);
Display *const dpy = cimg::X11_attr().display;
const unsigned int
tmpdimx = (nwidth>0)?nwidth:(-nwidth*width()/100),
tmpdimy = (nheight>0)?nheight:(-nheight*height()/100),
dimx = tmpdimx?tmpdimx:1,
dimy = tmpdimy?tmpdimy:1;
if (_width!=dimx || _height!=dimy || _window_width!=dimx || _window_height!=dimy) {
show();
cimg_lock_display();
if (_window_width!=dimx || _window_height!=dimy) {
XWindowAttributes attr;
for (unsigned int i = 0; i<10; ++i) {
XResizeWindow(dpy,_window,dimx,dimy);
XGetWindowAttributes(dpy,_window,&attr);
if (attr.width==(int)dimx && attr.height==(int)dimy) break;
cimg::wait(5,&_timer);
}
}
if (_width!=dimx || _height!=dimy) switch (cimg::X11_attr().nb_bits) {
case 8 :  { unsigned char pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); } break;
case 16 : { unsigned short pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); } break;
default : { unsigned int pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); }
}
_window_width = _width = dimx; _window_height = _height = dimy;
cimg_unlock_display();
}
_is_resized = false;
if (_is_fullscreen) move((screen_width() - _width)/2,(screen_height() - _height)/2);
if (force_redraw) return paint();
return *this;
}

CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
if (is_empty()) return *this;
if (force_redraw) {
const cimg_ulong buf_size = (cimg_ulong)_width*_height*
(cimg::X11_attr().nb_bits==8?1:(cimg::X11_attr().nb_bits==16?2:4));
void *image_data = std::malloc(buf_size);
std::memcpy(image_data,_data,buf_size);
assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
std::memcpy(_data,image_data,buf_size);
std::free(image_data);
return paint();
}
return assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
}

CImgDisplay& show() {
if (is_empty() || !_is_closed) return *this;
cimg_lock_display();
if (_is_fullscreen) _init_fullscreen();
_map_window();
_is_closed = false;
cimg_unlock_display();
return paint();
}

CImgDisplay& close() {
if (is_empty() || _is_closed) return *this;
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
if (_is_fullscreen) _desinit_fullscreen();
XUnmapWindow(dpy,_window);
_window_x = _window_y = -1;
_is_closed = true;
cimg_unlock_display();
return *this;
}

CImgDisplay& move(const int posx, const int posy) {
if (is_empty()) return *this;
if (_window_x!=posx || _window_y!=posy) {
show();
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
XMoveWindow(dpy,_window,posx,posy);
_window_x = posx; _window_y = posy;
cimg_unlock_display();
}
_is_moved = false;
return paint();
}

CImgDisplay& show_mouse() {
if (is_empty()) return *this;
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
XUndefineCursor(dpy,_window);
cimg_unlock_display();
return *this;
}

CImgDisplay& hide_mouse() {
if (is_empty()) return *this;
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
static const char pix_data[8] = { 0 };
XColor col;
col.red = col.green = col.blue = 0;
Pixmap pix = XCreateBitmapFromData(dpy,_window,pix_data,8,8);
Cursor cur = XCreatePixmapCursor(dpy,pix,pix,&col,&col,0,0);
XFreePixmap(dpy,pix);
XDefineCursor(dpy,_window,cur);
cimg_unlock_display();
return *this;
}

CImgDisplay& set_mouse(const int posx, const int posy) {
if (is_empty() || _is_closed) return *this;
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
XWarpPointer(dpy,0L,_window,0,0,0,0,posx,posy);
_mouse_x = posx; _mouse_y = posy;
_is_moved = false;
XSync(dpy,0);
cimg_unlock_display();
return *this;
}

CImgDisplay& set_title(const char *const format, ...) {
if (is_empty()) return *this;
char *const tmp = new char[1024];
va_list ap;
va_start(ap, format);
cimg_vsnprintf(tmp,1024,format,ap);
va_end(ap);
if (!std::strcmp(_title,tmp)) { delete[] tmp; return *this; }
delete[] _title;
const unsigned int s = (unsigned int)std::strlen(tmp) + 1;
_title = new char[s];
std::memcpy(_title,tmp,s*sizeof(char));
Display *const dpy = cimg::X11_attr().display;
cimg_lock_display();
XStoreName(dpy,_window,tmp);
cimg_unlock_display();
delete[] tmp;
return *this;
}

template<typename T>
CImgDisplay& display(const CImg<T>& img) {
if (!img)
throw CImgArgumentException(_cimgdisplay_instance
"display(): Empty specified image.",
cimgdisplay_instance);
if (is_empty()) return assign(img);
return render(img).paint(false);
}

CImgDisplay& paint(const bool wait_expose=true) {
if (is_empty()) return *this;
cimg_lock_display();
_paint(wait_expose);
cimg_unlock_display();
return *this;
}

template<typename T>
CImgDisplay& render(const CImg<T>& img, const bool flag8=false) {
if (!img)
throw CImgArgumentException(_cimgdisplay_instance
"render(): Empty specified image.",
cimgdisplay_instance);
if (is_empty()) return *this;
if (img._depth!=1) return render(img.get_projections2d((img._width - 1)/2,(img._height - 1)/2,
(img._depth - 1)/2));
if (cimg::X11_attr().nb_bits==8 && (img._width!=_width || img._height!=_height))
return render(img.get_resize(_width,_height,1,-100,1));
if (cimg::X11_attr().nb_bits==8 && !flag8 && img._spectrum==3) {
static const CImg<typename CImg<T>::ucharT> default_colormap = CImg<typename CImg<T>::ucharT>::default_LUT256();
return render(img.get_index(default_colormap,1,false));
}

const T
*data1 = img._data,
*data2 = (img._spectrum>1)?img.data(0,0,0,1):data1,
*data3 = (img._spectrum>2)?img.data(0,0,0,2):data1;

if (cimg::X11_attr().is_blue_first) cimg::swap(data1,data3);
cimg_lock_display();

if (!_normalization || (_normalization==3 && cimg::type<T>::string()==cimg::type<unsigned char>::string())) {
_min = _max = 0;
switch (cimg::X11_attr().nb_bits) {
case 8 : { // 256 colormap, no normalization
_set_colormap(_colormap,img._spectrum);
unsigned char
*const ndata = (img._width==_width && img._height==_height)?(unsigned char*)_data:
new unsigned char[(size_t)img._width*img._height],
*ptrd = (unsigned char*)ndata;
switch (img._spectrum) {
case 1 :
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
(*ptrd++) = (unsigned char)*(data1++);
break;
case 2 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)*(data1++),
G = (unsigned char)*(data2++);
(*ptrd++) = (R&0xf0) | (G>>4);
} break;
default : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)*(data1++),
G = (unsigned char)*(data2++),
B = (unsigned char)*(data3++);
(*ptrd++) = (R&0xe0) | ((G>>5)<<2) | (B>>6);
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned char*)_data,_width,_height);
delete[] ndata;
}
} break;
case 16 : { // 16 bits colors, no normalization
unsigned short *const ndata = (img._width==_width && img._height==_height)?(unsigned short*)_data:
new unsigned short[(size_t)img._width*img._height];
unsigned char *ptrd = (unsigned char*)ndata;
const unsigned int M = 248;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)*(data1++), G = val>>2;
ptrd[0] = (val&M) | (G>>3);
ptrd[1] = (G<<5) | (G>>1);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)*(data1++), G = val>>2;
ptrd[0] = (G<<5) | (G>>1);
ptrd[1] = (val&M) | (G>>3);
ptrd+=2;
}
break;
case 2 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)*(data2++)>>2;
ptrd[0] = ((unsigned char)*(data1++)&M) | (G>>3);
ptrd[1] = (G<<5);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)*(data2++)>>2;
ptrd[0] = (G<<5);
ptrd[1] = ((unsigned char)*(data1++)&M) | (G>>3);
ptrd+=2;
}
break;
default :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)*(data2++)>>2;
ptrd[0] = ((unsigned char)*(data1++)&M) | (G>>3);
ptrd[1] = (G<<5) | ((unsigned char)*(data3++)>>3);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)*(data2++)>>2;
ptrd[0] = (G<<5) | ((unsigned char)*(data3++)>>3);
ptrd[1] = ((unsigned char)*(data1++)&M) | (G>>3);
ptrd+=2;
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned short*)_data,_width,_height);
delete[] ndata;
}
} break;
default : { // 24 bits colors, no normalization
unsigned int *const ndata = (img._width==_width && img._height==_height)?(unsigned int*)_data:
new unsigned int[(size_t)img._width*img._height];
if (sizeof(int)==4) { // 32 bits int uses optimized version
unsigned int *ptrd = ndata;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)*(data1++);
*(ptrd++) = (val<<16) | (val<<8) | val;
}
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)*(data1++);
*(ptrd++) = (val<<16) | (val<<8) | val;
}
break;
case 2 :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) = ((unsigned char)*(data1++)<<16) | ((unsigned char)*(data2++)<<8);
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) = ((unsigned char)*(data2++)<<16) | ((unsigned char)*(data1++)<<8);
break;
default :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) = ((unsigned char)*(data1++)<<16) | ((unsigned char)*(data2++)<<8) |
(unsigned char)*(data3++);
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) = ((unsigned char)*(data3++)<<24) | ((unsigned char)*(data2++)<<16) |
((unsigned char)*(data1++)<<8);
}
} else {
unsigned char *ptrd = (unsigned char*)ndata;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = (unsigned char)*(data1++);
ptrd[2] = 0;
ptrd[3] = 0;
ptrd+=4;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = 0;
ptrd[2] = (unsigned char)*(data1++);
ptrd[3] = 0;
ptrd+=4;
}
break;
case 2 :
if (cimg::X11_attr().byte_order) cimg::swap(data1,data2);
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = (unsigned char)*(data2++);
ptrd[2] = (unsigned char)*(data1++);
ptrd[3] = 0;
ptrd+=4;
}
break;
default :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = (unsigned char)*(data1++);
ptrd[2] = (unsigned char)*(data2++);
ptrd[3] = (unsigned char)*(data3++);
ptrd+=4;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = (unsigned char)*(data3++);
ptrd[1] = (unsigned char)*(data2++);
ptrd[2] = (unsigned char)*(data1++);
ptrd[3] = 0;
ptrd+=4;
}
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned int*)_data,_width,_height);
delete[] ndata;
}
}
}
} else {
if (_normalization==3) {
if (cimg::type<T>::is_float()) _min = (float)img.min_max(_max);
else { _min = (float)cimg::type<T>::min(); _max = (float)cimg::type<T>::max(); }
} else if ((_min>_max) || _normalization==1) _min = (float)img.min_max(_max);
const float delta = _max - _min, mm = 255/(delta?delta:1.f);
switch (cimg::X11_attr().nb_bits) {
case 8 : { // 256 colormap, with normalization
_set_colormap(_colormap,img._spectrum);
unsigned char *const ndata = (img._width==_width && img._height==_height)?(unsigned char*)_data:
new unsigned char[(size_t)img._width*img._height];
unsigned char *ptrd = (unsigned char*)ndata;
switch (img._spectrum) {
case 1 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char R = (unsigned char)((*(data1++) - _min)*mm);
*(ptrd++) = R;
} break;
case 2 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)((*(data1++) - _min)*mm),
G = (unsigned char)((*(data2++) - _min)*mm);
(*ptrd++) = (R&0xf0) | (G>>4);
} break;
default :
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)((*(data1++) - _min)*mm),
G = (unsigned char)((*(data2++) - _min)*mm),
B = (unsigned char)((*(data3++) - _min)*mm);
*(ptrd++) = (R&0xe0) | ((G>>5)<<2) | (B>>6);
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned char*)_data,_width,_height);
delete[] ndata;
}
} break;
case 16 : { // 16 bits colors, with normalization
unsigned short *const ndata = (img._width==_width && img._height==_height)?(unsigned short*)_data:
new unsigned short[(size_t)img._width*img._height];
unsigned char *ptrd = (unsigned char*)ndata;
const unsigned int M = 248;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm), G = val>>2;
ptrd[0] = (val&M) | (G>>3);
ptrd[1] = (G<<5) | (val>>3);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm), G = val>>2;
ptrd[0] = (G<<5) | (val>>3);
ptrd[1] = (val&M) | (G>>3);
ptrd+=2;
}
break;
case 2 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
ptrd[0] = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
ptrd[1] = (G<<5);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
ptrd[0] = (G<<5);
ptrd[1] = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
ptrd+=2;
}
break;
default :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
ptrd[0] = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
ptrd[1] = (G<<5) | ((unsigned char)((*(data3++) - _min)*mm)>>3);
ptrd+=2;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
ptrd[0] = (G<<5) | ((unsigned char)((*(data3++) - _min)*mm)>>3);
ptrd[1] = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
ptrd+=2;
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned short*)_data,_width,_height);
delete[] ndata;
}
} break;
default : { // 24 bits colors, with normalization
unsigned int *const ndata = (img._width==_width && img._height==_height)?(unsigned int*)_data:
new unsigned int[(size_t)img._width*img._height];
if (sizeof(int)==4) { // 32 bits int uses optimized version
unsigned int *ptrd = ndata;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
*(ptrd++) = (val<<16) | (val<<8) | val;
}
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
*(ptrd++) = (val<<24) | (val<<16) | (val<<8);
}
break;
case 2 :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) =
((unsigned char)((*(data1++) - _min)*mm)<<16) |
((unsigned char)((*(data2++) - _min)*mm)<<8);
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) =
((unsigned char)((*(data2++) - _min)*mm)<<16) |
((unsigned char)((*(data1++) - _min)*mm)<<8);
break;
default :
if (cimg::X11_attr().byte_order==cimg::endianness())
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) =
((unsigned char)((*(data1++) - _min)*mm)<<16) |
((unsigned char)((*(data2++) - _min)*mm)<<8) |
(unsigned char)((*(data3++) - _min)*mm);
else
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
*(ptrd++) =
((unsigned char)((*(data3++) - _min)*mm)<<24) |
((unsigned char)((*(data2++) - _min)*mm)<<16) |
((unsigned char)((*(data1++) - _min)*mm)<<8);
}
} else {
unsigned char *ptrd = (unsigned char*)ndata;
switch (img._spectrum) {
case 1 :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
ptrd[0] = 0;
ptrd[1] = val;
ptrd[2] = val;
ptrd[3] = val;
ptrd+=4;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
ptrd[0] = val;
ptrd[1] = val;
ptrd[2] = val;
ptrd[3] = 0;
ptrd+=4;
}
break;
case 2 :
if (cimg::X11_attr().byte_order) cimg::swap(data1,data2);
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = (unsigned char)((*(data2++) - _min)*mm);
ptrd[2] = (unsigned char)((*(data1++) - _min)*mm);
ptrd[3] = 0;
ptrd+=4;
}
break;
default :
if (cimg::X11_attr().byte_order)
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = 0;
ptrd[1] = (unsigned char)((*(data1++) - _min)*mm);
ptrd[2] = (unsigned char)((*(data2++) - _min)*mm);
ptrd[3] = (unsigned char)((*(data3++) - _min)*mm);
ptrd+=4;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
ptrd[0] = (unsigned char)((*(data3++) - _min)*mm);
ptrd[1] = (unsigned char)((*(data2++) - _min)*mm);
ptrd[2] = (unsigned char)((*(data1++) - _min)*mm);
ptrd[3] = 0;
ptrd+=4;
}
}
}
if (ndata!=_data) {
_render_resize(ndata,img._width,img._height,(unsigned int*)_data,_width,_height);
delete[] ndata;
}
}
}
}
cimg_unlock_display();
return *this;
}

template<typename T>
static void screenshot(const int x0, const int y0, const int x1, const int y1, CImg<T>& img) {
img.assign();
Display *dpy = cimg::X11_attr().display;
cimg_lock_display();
if (!dpy) {
dpy = XOpenDisplay(0);
if (!dpy)
throw CImgDisplayException("CImgDisplay::screenshot(): Failed to open X11 display.");
}
Window root = DefaultRootWindow(dpy);
XWindowAttributes gwa;
XGetWindowAttributes(dpy,root,&gwa);
const int width = gwa.width, height = gwa.height;
int _x0 = x0, _y0 = y0, _x1 = x1, _y1 = y1;
if (_x0>_x1) cimg::swap(_x0,_x1);
if (_y0>_y1) cimg::swap(_y0,_y1);

XImage *image = 0;
if (_x1>=0 && _x0<width && _y1>=0 && _y0<height) {
_x0 = std::max(_x0,0);
_y0 = std::max(_y0,0);
_x1 = std::min(_x1,width - 1);
_y1 = std::min(_y1,height - 1);
image = XGetImage(dpy,root,_x0,_y0,_x1 - _x0 + 1,_y1 - _y0 + 1,AllPlanes,ZPixmap);

if (image) {
const unsigned long
red_mask = image->red_mask,
green_mask = image->green_mask,
blue_mask = image->blue_mask;
img.assign(image->width,image->height,1,3);
T *pR = img.data(0,0,0,0), *pG = img.data(0,0,0,1), *pB = img.data(0,0,0,2);
cimg_forXY(img,x,y) {
const unsigned long pixel = XGetPixel(image,x,y);
*(pR++) = (T)((pixel & red_mask)>>16);
*(pG++) = (T)((pixel & green_mask)>>8);
*(pB++) = (T)(pixel & blue_mask);
}
XDestroyImage(image);
}
}
if (!cimg::X11_attr().display) XCloseDisplay(dpy);
cimg_unlock_display();
if (img.is_empty())
throw CImgDisplayException("CImgDisplay::screenshot(): Failed to take screenshot "
"with coordinates (%d,%d)-(%d,%d).",
x0,y0,x1,y1);
}

template<typename T>
const CImgDisplay& snapshot(CImg<T>& img) const {
if (is_empty()) { img.assign(); return *this; }
const unsigned char *ptrs = (unsigned char*)_data;
img.assign(_width,_height,1,3);
T
*data1 = img.data(0,0,0,0),
*data2 = img.data(0,0,0,1),
*data3 = img.data(0,0,0,2);
if (cimg::X11_attr().is_blue_first) cimg::swap(data1,data3);
switch (cimg::X11_attr().nb_bits) {
case 8 : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = *(ptrs++);
*(data1++) = (T)(val&0xe0);
*(data2++) = (T)((val&0x1c)<<3);
*(data3++) = (T)(val<<6);
}
} break;
case 16 : {
if (cimg::X11_attr().byte_order) for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
val0 = ptrs[0],
val1 = ptrs[1];
ptrs+=2;
*(data1++) = (T)(val0&0xf8);
*(data2++) = (T)((val0<<5) | ((val1&0xe0)>>5));
*(data3++) = (T)(val1<<3);
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned short
val0 = ptrs[0],
val1 = ptrs[1];
ptrs+=2;
*(data1++) = (T)(val1&0xf8);
*(data2++) = (T)((val1<<5) | ((val0&0xe0)>>5));
*(data3++) = (T)(val0<<3);
}
} break;
default : {
if (cimg::X11_attr().byte_order) for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
++ptrs;
*(data1++) = (T)ptrs[0];
*(data2++) = (T)ptrs[1];
*(data3++) = (T)ptrs[2];
ptrs+=3;
} else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
*(data3++) = (T)ptrs[0];
*(data2++) = (T)ptrs[1];
*(data1++) = (T)ptrs[2];
ptrs+=3;
++ptrs;
}
}
}
return *this;
}

// Windows-based implementation.
//-------------------------------
#elif cimg_display==2

bool _is_mouse_tracked, _is_cursor_visible;
HANDLE _thread, _is_created, _mutex;
HWND _window, _background_window;
CLIENTCREATESTRUCT _ccs;
unsigned int *_data;
DEVMODE _curr_mode;
BITMAPINFO _bmi;
HDC _hdc;

static int screen_width() {
DEVMODE mode;
mode.dmSize = sizeof(DEVMODE);
mode.dmDriverExtra = 0;
EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&mode);
return (int)mode.dmPelsWidth;
}

static int screen_height() {
DEVMODE mode;
mode.dmSize = sizeof(DEVMODE);
mode.dmDriverExtra = 0;
EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&mode);
return (int)mode.dmPelsHeight;
}

static void wait_all() {
WaitForSingleObject(cimg::Win32_attr().wait_event,INFINITE);
}

static LRESULT APIENTRY _handle_events(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
#ifdef _WIN64
CImgDisplay *const disp = (CImgDisplay*)GetWindowLongPtr(window,GWLP_USERDATA);
#else
CImgDisplay *const disp = (CImgDisplay*)GetWindowLong(window,GWL_USERDATA);
#endif
MSG st_msg;
switch (msg) {
case WM_CLOSE :
disp->_mouse_x = disp->_mouse_y = -1;
disp->_window_x = disp->_window_y = 0;
disp->set_button().set_key(0).set_key(0,false)._is_closed = true;
ReleaseMutex(disp->_mutex);
ShowWindow(disp->_window,SW_HIDE);
disp->_is_event = true;
SetEvent(cimg::Win32_attr().wait_event);
return 0;
case WM_SIZE : {
while (PeekMessage(&st_msg,window,WM_SIZE,WM_SIZE,PM_REMOVE)) {}
WaitForSingleObject(disp->_mutex,INFINITE);
const unsigned int nw = LOWORD(lParam),nh = HIWORD(lParam);
if (nw && nh && (nw!=disp->_width || nh!=disp->_height)) {
disp->_window_width = nw;
disp->_window_height = nh;
disp->_mouse_x = disp->_mouse_y = -1;
disp->_is_resized = disp->_is_event = true;
SetEvent(cimg::Win32_attr().wait_event);
}
ReleaseMutex(disp->_mutex);
} break;
case WM_MOVE : {
while (PeekMessage(&st_msg,window,WM_SIZE,WM_SIZE,PM_REMOVE)) {}
WaitForSingleObject(disp->_mutex,INFINITE);
const int nx = (int)(short)(LOWORD(lParam)), ny = (int)(short)(HIWORD(lParam));
if (nx!=disp->_window_x || ny!=disp->_window_y) {
disp->_window_x = nx;
disp->_window_y = ny;
disp->_is_moved = disp->_is_event = true;
SetEvent(cimg::Win32_attr().wait_event);
}
ReleaseMutex(disp->_mutex);
} break;
case WM_PAINT :
disp->paint();
cimg_lock_display();
if (disp->_is_cursor_visible) while (ShowCursor(TRUE)<0); else while (ShowCursor(FALSE)>=0);
cimg_unlock_display();
break;
case WM_ERASEBKGND :
//        return 0;
break;
case WM_KEYDOWN :
disp->set_key((unsigned int)wParam);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_KEYUP :
disp->set_key((unsigned int)wParam,false);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_MOUSEMOVE : {
while (PeekMessage(&st_msg,window,WM_MOUSEMOVE,WM_MOUSEMOVE,PM_REMOVE)) {}
disp->_mouse_x = LOWORD(lParam);
disp->_mouse_y = HIWORD(lParam);
#if (_WIN32_WINNT>=0x0400) && !defined(NOTRACKMOUSEEVENT)
if (!disp->_is_mouse_tracked) {
TRACKMOUSEEVENT tme;
tme.cbSize = sizeof(TRACKMOUSEEVENT);
tme.dwFlags = TME_LEAVE;
tme.hwndTrack = disp->_window;
if (TrackMouseEvent(&tme)) disp->_is_mouse_tracked = true;
}
#endif
if (disp->_mouse_x<0 || disp->_mouse_y<0 || disp->_mouse_x>=disp->width() || disp->_mouse_y>=disp->height())
disp->_mouse_x = disp->_mouse_y = -1;
disp->_is_event = true;
SetEvent(cimg::Win32_attr().wait_event);
cimg_lock_display();
if (disp->_is_cursor_visible) while (ShowCursor(TRUE)<0); else while (ShowCursor(FALSE)>=0);
cimg_unlock_display();
}	break;
case WM_MOUSELEAVE : {
disp->_mouse_x = disp->_mouse_y = -1;
disp->_is_mouse_tracked = false;
cimg_lock_display();
while (ShowCursor(TRUE)<0) {}
cimg_unlock_display();
} break;
case WM_LBUTTONDOWN :
disp->set_button(1);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_RBUTTONDOWN :
disp->set_button(2);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_MBUTTONDOWN :
disp->set_button(3);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_LBUTTONUP :
disp->set_button(1,false);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_RBUTTONUP :
disp->set_button(2,false);
SetEvent(cimg::Win32_attr().wait_event);
break;
case WM_MBUTTONUP :
disp->set_button(3,false);
SetEvent(cimg::Win32_attr().wait_event);
break;
case 0x020A : // WM_MOUSEWHEEL:
disp->set_wheel((int)((short)HIWORD(wParam))/120);
SetEvent(cimg::Win32_attr().wait_event);
}
return DefWindowProc(window,msg,wParam,lParam);
}

static DWORD WINAPI _events_thread(void* arg) {
CImgDisplay *const disp = (CImgDisplay*)(((void**)arg)[0]);
const char *const title = (const char*)(((void**)arg)[1]);
MSG msg;
delete[] (void**)arg;
disp->_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
disp->_bmi.bmiHeader.biWidth = disp->width();
disp->_bmi.bmiHeader.biHeight = -disp->height();
disp->_bmi.bmiHeader.biPlanes = 1;
disp->_bmi.bmiHeader.biBitCount = 32;
disp->_bmi.bmiHeader.biCompression = BI_RGB;
disp->_bmi.bmiHeader.biSizeImage = 0;
disp->_bmi.bmiHeader.biXPelsPerMeter = 1;
disp->_bmi.bmiHeader.biYPelsPerMeter = 1;
disp->_bmi.bmiHeader.biClrUsed = 0;
disp->_bmi.bmiHeader.biClrImportant = 0;
disp->_data = new unsigned int[(size_t)disp->_width*disp->_height];
if (!disp->_is_fullscreen) { // Normal window
RECT rect;
rect.left = rect.top = 0; rect.right = (LONG)disp->_width - 1; rect.bottom = (LONG)disp->_height - 1;
AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
const int
border1 = (int)((rect.right - rect.left + 1 - disp->_width)/2),
border2 = (int)(rect.bottom - rect.top + 1 - disp->_height - border1);
disp->_window = CreateWindowA("MDICLIENT",title?title:" ",
WS_OVERLAPPEDWINDOW | (disp->_is_closed?0:WS_VISIBLE), CW_USEDEFAULT,CW_USEDEFAULT,
disp->_width + 2*border1, disp->_height + border1 + border2,
0,0,0,&(disp->_ccs));
if (!disp->_is_closed) {
GetWindowRect(disp->_window,&rect);
disp->_window_x = rect.left + border1;
disp->_window_y = rect.top + border2;
} else disp->_window_x = disp->_window_y = 0;
} else { // Fullscreen window
const unsigned int
sx = (unsigned int)screen_width(),
sy = (unsigned int)screen_height();
disp->_window = CreateWindowA("MDICLIENT",title?title:" ",
WS_POPUP | (disp->_is_closed?0:WS_VISIBLE),
(sx - disp->_width)/2,
(sy - disp->_height)/2,
disp->_width,disp->_height,0,0,0,&(disp->_ccs));
disp->_window_x = disp->_window_y = 0;
}
SetForegroundWindow(disp->_window);
disp->_hdc = GetDC(disp->_window);
disp->_window_width = disp->_width;
disp->_window_height = disp->_height;
disp->flush();
#ifdef _WIN64
SetWindowLongPtr(disp->_window,GWLP_USERDATA,(LONG_PTR)disp);
SetWindowLongPtr(disp->_window,GWLP_WNDPROC,(LONG_PTR)_handle_events);
#else
SetWindowLong(disp->_window,GWL_USERDATA,(LONG)disp);
SetWindowLong(disp->_window,GWL_WNDPROC,(LONG)_handle_events);
#endif
SetEvent(disp->_is_created);
while (GetMessage(&msg,0,0,0)) DispatchMessage(&msg);
return 0;
}

CImgDisplay& _update_window_pos() {
if (_is_closed) _window_x = _window_y = -1;
else {
RECT rect;
rect.left = rect.top = 0; rect.right = (LONG)_width - 1; rect.bottom = (LONG)_height - 1;
AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
const int
border1 = (int)((rect.right - rect.left + 1 - _width)/2),
border2 = (int)(rect.bottom - rect.top + 1 - _height - border1);
GetWindowRect(_window,&rect);
_window_x = rect.left + border1;
_window_y = rect.top + border2;
}
return *this;
}

void _init_fullscreen() {
_background_window = 0;
if (!_is_fullscreen || _is_closed) _curr_mode.dmSize = 0;
else {
DEVMODE mode;
unsigned int imode = 0, ibest = 0, bestbpp = 0, bw = ~0U, bh = ~0U;
for (mode.dmSize = sizeof(DEVMODE), mode.dmDriverExtra = 0; EnumDisplaySettings(0,imode,&mode); ++imode) {
const unsigned int nw = mode.dmPelsWidth, nh = mode.dmPelsHeight;
if (nw>=_width && nh>=_height && mode.dmBitsPerPel>=bestbpp && nw<=bw && nh<=bh) {
bestbpp = mode.dmBitsPerPel;
ibest = imode;
bw = nw; bh = nh;
}
}
if (bestbpp) {
_curr_mode.dmSize = sizeof(DEVMODE); _curr_mode.dmDriverExtra = 0;
EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&_curr_mode);
EnumDisplaySettings(0,ibest,&mode);
ChangeDisplaySettings(&mode,0);
} else _curr_mode.dmSize = 0;

const unsigned int
sx = (unsigned int)screen_width(),
sy = (unsigned int)screen_height();
if (sx!=_width || sy!=_height) {
CLIENTCREATESTRUCT background_ccs;
_background_window = CreateWindowA("MDICLIENT","",WS_POPUP | WS_VISIBLE, 0,0,sx,sy,0,0,0,&background_ccs);
SetForegroundWindow(_background_window);
}
}
}

void _desinit_fullscreen() {
if (!_is_fullscreen) return;
if (_background_window) DestroyWindow(_background_window);
_background_window = 0;
if (_curr_mode.dmSize) ChangeDisplaySettings(&_curr_mode,0);
_is_fullscreen = false;
}

CImgDisplay& _assign(const unsigned int dimw, const unsigned int dimh, const char *const ptitle=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {

// Allocate space for window title
const char *const nptitle = ptitle?ptitle:"";
const unsigned int s = (unsigned int)std::strlen(nptitle) + 1;
char *const tmp_title = s?new char[s]:0;
if (s) std::memcpy(tmp_title,nptitle,s*sizeof(char));

// Destroy previous window if existing
if (!is_empty()) assign();

// Set display variables
_width = std::min(dimw,(unsigned int)screen_width());
_height = std::min(dimh,(unsigned int)screen_height());
_normalization = normalization_type<4?normalization_type:3;
_is_fullscreen = fullscreen_flag;
_window_x = _window_y = 0;
_is_closed = closed_flag;
_is_cursor_visible = true;
_is_mouse_tracked = false;
_title = tmp_title;
flush();
if (_is_fullscreen) _init_fullscreen();

// Create event thread
void *const arg = (void*)(new void*[2]);
((void**)arg)[0] = (void*)this;
((void**)arg)[1] = (void*)_title;
_mutex = CreateMutex(0,FALSE,0);
_is_created = CreateEvent(0,FALSE,FALSE,0);
_thread = CreateThread(0,0,_events_thread,arg,0,0);
WaitForSingleObject(_is_created,INFINITE);
return *this;
}

CImgDisplay& assign() {
if (is_empty()) return flush();
DestroyWindow(_window);
TerminateThread(_thread,0);
delete[] _data;
delete[] _title;
_data = 0;
_title = 0;
if (_is_fullscreen) _desinit_fullscreen();
_width = _height = _normalization = _window_width = _window_height = 0;
_window_x = _window_y = 0;
_is_fullscreen = false;
_is_closed = true;
_min = _max = 0;
_title = 0;
flush();
return *this;
}

CImgDisplay& assign(const unsigned int dimw, const unsigned int dimh, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!dimw || !dimh) return assign();
_assign(dimw,dimh,title,normalization_type,fullscreen_flag,closed_flag);
_min = _max = 0;
std::memset(_data,0,sizeof(unsigned int)*_width*_height);
return paint();
}

template<typename T>
CImgDisplay& assign(const CImg<T>& img, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!img) return assign();
CImg<T> tmp;
const CImg<T>& nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
(img._height - 1)/2,
(img._depth - 1)/2));
_assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
if (_normalization==2) _min = (float)nimg.min_max(_max);
return display(nimg);
}

template<typename T>
CImgDisplay& assign(const CImgList<T>& list, const char *const title=0,
const unsigned int normalization_type=3,
const bool fullscreen_flag=false, const bool closed_flag=false) {
if (!list) return assign();
CImg<T> tmp;
const CImg<T> img = list>'x', &nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
(img._height - 1)/2,
(img._depth - 1)/2));
_assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
if (_normalization==2) _min = (float)nimg.min_max(_max);
return display(nimg);
}

CImgDisplay& assign(const CImgDisplay& disp) {
if (!disp) return assign();
_assign(disp._width,disp._height,disp._title,disp._normalization,disp._is_fullscreen,disp._is_closed);
std::memcpy(_data,disp._data,sizeof(unsigned int)*_width*_height);
return paint();
}

CImgDisplay& resize(const int nwidth, const int nheight, const bool force_redraw=true) {
if (!nwidth || !nheight || (is_empty() && (nwidth<0 || nheight<0))) return assign();
if (is_empty()) return assign(nwidth,nheight);
const unsigned int
tmpdimx = (nwidth>0)?nwidth:(-nwidth*_width/100),
tmpdimy = (nheight>0)?nheight:(-nheight*_height/100),
dimx = tmpdimx?tmpdimx:1,
dimy = tmpdimy?tmpdimy:1;
if (_width!=dimx || _height!=dimy || _window_width!=dimx || _window_height!=dimy) {
if (_window_width!=dimx || _window_height!=dimy) {
RECT rect; rect.left = rect.top = 0; rect.right = (LONG)dimx - 1; rect.bottom = (LONG)dimy - 1;
AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
const int cwidth = rect.right - rect.left + 1, cheight = rect.bottom - rect.top + 1;
SetWindowPos(_window,0,0,0,cwidth,cheight,SWP_NOMOVE | SWP_NOZORDER | SWP_NOCOPYBITS);
}
if (_width!=dimx || _height!=dimy) {
unsigned int *const ndata = new unsigned int[dimx*dimy];
if (force_redraw) _render_resize(_data,_width,_height,ndata,dimx,dimy);
else std::memset(ndata,0x80,sizeof(unsigned int)*dimx*dimy);
delete[] _data;
_data = ndata;
_bmi.bmiHeader.biWidth = (LONG)dimx;
_bmi.bmiHeader.biHeight = -(int)dimy;
_width = dimx;
_height = dimy;
}
_window_width = dimx; _window_height = dimy;
show();
}
_is_resized = false;
if (_is_fullscreen) move((screen_width() - width())/2,(screen_height() - height())/2);
if (force_redraw) return paint();
return *this;
}

CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
if (is_empty()) return *this;
if (force_redraw) {
const cimg_ulong buf_size = (cimg_ulong)_width*_height*4;
void *odata = std::malloc(buf_size);
if (odata) {
std::memcpy(odata,_data,buf_size);
assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
std::memcpy(_data,odata,buf_size);
std::free(odata);
}
return paint();
}
return assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
}

CImgDisplay& show() {
if (is_empty() || !_is_closed) return *this;
_is_closed = false;
if (_is_fullscreen) _init_fullscreen();
ShowWindow(_window,SW_SHOW);
_update_window_pos();
return paint();
}

CImgDisplay& close() {
if (is_empty() || _is_closed) return *this;
_is_closed = true;
if (_is_fullscreen) _desinit_fullscreen();
ShowWindow(_window,SW_HIDE);
_window_x = _window_y = 0;
return *this;
}

CImgDisplay& move(const int posx, const int posy) {
if (is_empty()) return *this;
if (_window_x!=posx || _window_y!=posy) {
if (!_is_fullscreen) {
RECT rect;
rect.left = rect.top = 0; rect.right = (LONG)_window_width - 1; rect.bottom = (LONG)_window_height - 1;
AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
const int
border1 = (int)((rect.right - rect.left + 1 -_width)/2),
border2 = (int)(rect.bottom - rect.top + 1 - _height - border1);
SetWindowPos(_window,0,posx - border1,posy - border2,0,0,SWP_NOSIZE | SWP_NOZORDER);
} else SetWindowPos(_window,0,posx,posy,0,0,SWP_NOSIZE | SWP_NOZORDER);
_window_x = posx;
_window_y = posy;
show();
}
_is_moved = false;
return *this;
}

CImgDisplay& show_mouse() {
if (is_empty()) return *this;
_is_cursor_visible = true;
return *this;
}

CImgDisplay& hide_mouse() {
if (is_empty()) return *this;
_is_cursor_visible = false;
return *this;
}

CImgDisplay& set_mouse(const int posx, const int posy) {
if (is_empty() || _is_closed || posx<0 || posy<0) return *this;
_update_window_pos();
const int res = (int)SetCursorPos(_window_x + posx,_window_y + posy);
if (res) { _mouse_x = posx; _mouse_y = posy; }
return *this;
}

CImgDisplay& set_title(const char *const format, ...) {
if (is_empty()) return *this;
char *const tmp = new char[1024];
va_list ap;
va_start(ap, format);
cimg_vsnprintf(tmp,1024,format,ap);
va_end(ap);
if (!std::strcmp(_title,tmp)) { delete[] tmp; return *this; }
delete[] _title;
const unsigned int s = (unsigned int)std::strlen(tmp) + 1;
_title = new char[s];
std::memcpy(_title,tmp,s*sizeof(char));
SetWindowTextA(_window, tmp);
delete[] tmp;
return *this;
}

template<typename T>
CImgDisplay& display(const CImg<T>& img) {
if (!img)
throw CImgArgumentException(_cimgdisplay_instance
"display(): Empty specified image.",
cimgdisplay_instance);
if (is_empty()) return assign(img);
return render(img).paint();
}

CImgDisplay& paint() {
if (_is_closed) return *this;
WaitForSingleObject(_mutex,INFINITE);
SetDIBitsToDevice(_hdc,0,0,_width,_height,0,0,0,_height,_data,&_bmi,DIB_RGB_COLORS);
ReleaseMutex(_mutex);
return *this;
}

template<typename T>
CImgDisplay& render(const CImg<T>& img) {
if (!img)
throw CImgArgumentException(_cimgdisplay_instance
"render(): Empty specified image.",
cimgdisplay_instance);

if (is_empty()) return *this;
if (img._depth!=1) return render(img.get_projections2d((img._width - 1)/2,(img._height - 1)/2,
(img._depth - 1)/2));

const T
*data1 = img._data,
*data2 = (img._spectrum>=2)?img.data(0,0,0,1):data1,
*data3 = (img._spectrum>=3)?img.data(0,0,0,2):data1;

WaitForSingleObject(_mutex,INFINITE);
unsigned int
*const ndata = (img._width==_width && img._height==_height)?_data:
new unsigned int[(size_t)img._width*img._height],
*ptrd = ndata;

if (!_normalization || (_normalization==3 && cimg::type<T>::string()==cimg::type<unsigned char>::string())) {
_min = _max = 0;
switch (img._spectrum) {
case 1 : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)*(data1++);
*(ptrd++) = (unsigned int)((val<<16) | (val<<8) | val);
}
} break;
case 2 : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)*(data1++),
G = (unsigned char)*(data2++);
*(ptrd++) = (unsigned int)((R<<16) | (G<<8));
}
} break;
default : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)*(data1++),
G = (unsigned char)*(data2++),
B = (unsigned char)*(data3++);
*(ptrd++) = (unsigned int)((R<<16) | (G<<8) | B);
}
}
}
} else {
if (_normalization==3) {
if (cimg::type<T>::is_float()) _min = (float)img.min_max(_max);
else { _min = (float)cimg::type<T>::min(); _max = (float)cimg::type<T>::max(); }
} else if ((_min>_max) || _normalization==1) _min = (float)img.min_max(_max);
const float delta = _max - _min, mm = 255/(delta?delta:1.f);
switch (img._spectrum) {
case 1 : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
*(ptrd++) = (unsigned int)((val<<16) | (val<<8) | val);
}
} break;
case 2 : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)((*(data1++) - _min)*mm),
G = (unsigned char)((*(data2++) - _min)*mm);
*(ptrd++) = (unsigned int)((R<<16) | (G<<8));
}
} break;
default : {
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned char
R = (unsigned char)((*(data1++) - _min)*mm),
G = (unsigned char)((*(data2++) - _min)*mm),
B = (unsigned char)((*(data3++) - _min)*mm);
*(ptrd++) = (unsigned int)((R<<16) | (G<<8) | B);
}
}
}
}
if (ndata!=_data) { _render_resize(ndata,img._width,img._height,_data,_width,_height); delete[] ndata; }
ReleaseMutex(_mutex);
return *this;
}

template<typename T>
static void screenshot(const int x0, const int y0, const int x1, const int y1, CImg<T>& img) {
img.assign();
HDC hScreen = GetDC(GetDesktopWindow());
if (hScreen) {
const int
width = GetDeviceCaps(hScreen,HORZRES),
height = GetDeviceCaps(hScreen,VERTRES);
int _x0 = x0, _y0 = y0, _x1 = x1, _y1 = y1;
if (_x0>_x1) cimg::swap(_x0,_x1);
if (_y0>_y1) cimg::swap(_y0,_y1);
if (_x1>=0 && _x0<width && _y1>=0 && _y0<height) {
_x0 = std::max(_x0,0);
_y0 = std::max(_y0,0);
_x1 = std::min(_x1,width - 1);
_y1 = std::min(_y1,height - 1);
const int bw = _x1 - _x0 + 1, bh = _y1 - _y0 + 1;
HDC hdcMem = CreateCompatibleDC(hScreen);
if (hdcMem) {
HBITMAP hBitmap = CreateCompatibleBitmap(hScreen,bw,bh);
if (hBitmap) {
HGDIOBJ hOld = SelectObject(hdcMem,hBitmap);
if (hOld && BitBlt(hdcMem,0,0,bw,bh,hScreen,_x0,_y0,SRCCOPY) && SelectObject(hdcMem,hOld)) {
BITMAPINFOHEADER bmi;
bmi.biSize = sizeof(BITMAPINFOHEADER);
bmi.biWidth = bw;
bmi.biHeight = -bh;
bmi.biPlanes = 1;
bmi.biBitCount = 32;
bmi.biCompression = BI_RGB;
bmi.biSizeImage = 0;
bmi.biXPelsPerMeter = bmi.biYPelsPerMeter = 0;
bmi.biClrUsed = bmi.biClrImportant = 0;
unsigned char *buf = new unsigned char[4*bw*bh];
if (GetDIBits(hdcMem,hBitmap,0,bh,buf,(BITMAPINFO*)&bmi,DIB_RGB_COLORS)) {
img.assign(bw,bh,1,3);
const unsigned char *ptrs = buf;
T *pR = img.data(0,0,0,0), *pG = img.data(0,0,0,1), *pB = img.data(0,0,0,2);
cimg_forXY(img,x,y) {
*(pR++) = (T)ptrs[2];
*(pG++) = (T)ptrs[1];
*(pB++) = (T)ptrs[0];
ptrs+=4;
}
}
delete[] buf;
}
DeleteObject(hBitmap);
}
DeleteDC(hdcMem);
}
}
ReleaseDC(GetDesktopWindow(),hScreen);
}
if (img.is_empty())
throw CImgDisplayException("CImgDisplay::screenshot(): Failed to take screenshot "
"with coordinates (%d,%d)-(%d,%d).",
x0,y0,x1,y1);
}

template<typename T>
const CImgDisplay& snapshot(CImg<T>& img) const {
if (is_empty()) { img.assign(); return *this; }
const unsigned int *ptrs = _data;
img.assign(_width,_height,1,3);
T
*data1 = img.data(0,0,0,0),
*data2 = img.data(0,0,0,1),
*data3 = img.data(0,0,0,2);
for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
const unsigned int val = *(ptrs++);
*(data1++) = (T)(unsigned char)(val>>16);
*(data2++) = (T)(unsigned char)((val>>8)&0xFF);
*(data3++) = (T)(unsigned char)(val&0xFF);
}
return *this;
}
#endif

//@}
};

/*
   #--------------------------------------
   #
   #
   #
   # Definition of the CImg<T> structure
   #
   #
   #
   #--------------------------------------
   */

//! Class representing an image (up to 4 dimensions wide), each pixel being of type \c T.
/**
     This is the main class of the %CImg Library. It declares and constructs
     an image, allows access to its pixel values, and is able to perform various image operations.

     \par Image representation

     A %CImg image is defined as an instance of the container \c CImg<T>, which contains a regular grid of pixels,
     each pixel value being of type \c T. The image grid can have up to 4 dimensions: width, height, depth
     and number of channels.
     Usually, the three first dimensions are used to describe spatial coordinates <tt>(x,y,z)</tt>,
     while the number of channels is rather used as a vector-valued dimension
     (it may describe the R,G,B color channels for instance).
     If you need a fifth dimension, you can use image lists \c CImgList<T> rather than simple images \c CImg<T>.

     Thus, the \c CImg<T> class is able to represent volumetric images of vector-valued pixels,
     as well as images with less dimensions (1D scalar signal, 2D color images, ...).
     Most member functions of the class CImg<\c T> are designed to handle this maximum case of (3+1) dimensions.

     Concerning the pixel value type \c T:
     fully supported template types are the basic C++ types: <tt>unsigned char, char, short, unsigned int, int,
     unsigned long, long, float, double, ... </tt>.
     Typically, fast image display can be done using <tt>CImg<unsigned char></tt> images,
     while complex image processing algorithms may be rather coded using <tt>CImg<float></tt> or <tt>CImg<double></tt>
     images that have floating-point pixel values. The default value for the template T is \c float.
     Using your own template types may be possible. However, you will certainly have to define the complete set
     of arithmetic and logical operators for your class.

     \par Image structure

     The \c CImg<T> structure contains \e six fields:
     - \c _width defines the number of \a columns of the image (size along the X-axis).
     - \c _height defines the number of \a rows of the image (size along the Y-axis).
     - \c _depth defines the number of \a slices of the image (size along the Z-axis).
     - \c _spectrum defines the number of \a channels of the image (size along the C-axis).
     - \c _data defines a \a pointer to the \a pixel \a data (of type \c T).
     - \c _is_shared is a boolean that tells if the memory buffer \c data is shared with
       another image.

     You can access these fields publicly although it is recommended to use the dedicated functions
     width(), height(), depth(), spectrum() and ptr() to do so.
     Image dimensions are not limited to a specific range (as long as you got enough available memory).
     A value of \e 1 usually means that the corresponding dimension is \a flat.
     If one of the dimensions is \e 0, or if the data pointer is null, the image is considered as \e empty.
     Empty images should not contain any pixel data and thus, will not be processed by CImg member functions
     (a CImgInstanceException will be thrown instead).
     Pixel data are stored in memory, in a non interlaced mode (See \ref cimg_storage).

     \par Image declaration and construction

     Declaring an image can be done by using one of the several available constructors.
     Here is a list of the most used:

     - Construct images from arbitrary dimensions:
         - <tt>CImg<char> img;</tt> declares an empty image.
         - <tt>CImg<unsigned char> img(128,128);</tt> declares a 128x128 greyscale image with
         \c unsigned \c char pixel values.
         - <tt>CImg<double> img(3,3);</tt> declares a 3x3 matrix with \c double coefficients.
         - <tt>CImg<unsigned char> img(256,256,1,3);</tt> declares a 256x256x1x3 (color) image
         (colors are stored as an image with three channels).
         - <tt>CImg<double> img(128,128,128);</tt> declares a 128x128x128 volumetric and greyscale image
         (with \c double pixel values).
         - <tt>CImg<> img(128,128,128,3);</tt> declares a 128x128x128 volumetric color image
         (with \c float pixels, which is the default value of the template parameter \c T).
         - \b Note: images pixels are <b>not automatically initialized to 0</b>. You may use the function \c fill() to
         do it, or use the specific constructor taking 5 parameters like this:
         <tt>CImg<> img(128,128,128,3,0);</tt> declares a 128x128x128 volumetric color image with all pixel values to 0.

     - Construct images from filenames:
         - <tt>CImg<unsigned char> img("image.jpg");</tt> reads a JPEG color image from the file "image.jpg".
         - <tt>CImg<float> img("analyze.hdr");</tt> reads a volumetric image (ANALYZE7.5 format) from the
         file "analyze.hdr".
         - \b Note: You need to install <a href="http://www.imagemagick.org">ImageMagick</a>
         to be able to read common compressed image formats (JPG,PNG, ...) (See \ref cimg_files_io).

     - Construct images from C-style arrays:
         - <tt>CImg<int> img(data_buffer,256,256);</tt> constructs a 256x256 greyscale image from a \c int* buffer
         \c data_buffer (of size 256x256=65536).
         - <tt>CImg<unsigned char> img(data_buffer,256,256,1,3);</tt> constructs a 256x256 color image
         from a \c unsigned \c char* buffer \c data_buffer (where R,G,B channels follow each others).

         The complete list of constructors can be found <a href="#constructors">here</a>.

     \par Most useful functions

     The \c CImg<T> class contains a lot of functions that operates on images.
     Some of the most useful are:

     - operator()(): Read or write pixel values.
     - display(): displays the image in a new window.
  **/
template<typename T>
struct CImg {

unsigned int _width, _height, _depth, _spectrum;
bool _is_shared;
T *_data;

//! Simple iterator type, to loop through each pixel value of an image instance.
/**
       \note
       - The \c CImg<T>::iterator type is defined to be a <tt>T*</tt>.
       - You will seldom have to use iterators in %CImg, most classical operations
         being achieved (often in a faster way) using methods of \c CImg<T>.
       \par Example
       \code
       CImg<float> img("reference.jpg");                                         // Load image from file
       // Set all pixels to '0', with a CImg iterator.
       for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) *it = 0;
       img.fill(0);                                                              // Do the same with a built-in method
       \endcode
   **/
typedef T* iterator;

//! Simple const iterator type, to loop through each pixel value of a \c const image instance.
/**
       \note
       - The \c CImg<T>::const_iterator type is defined to be a \c const \c T*.
       - You will seldom have to use iterators in %CImg, most classical operations
         being achieved (often in a faster way) using methods of \c CImg<T>.
       \par Example
       \code
       const CImg<float> img("reference.jpg");                                    // Load image from file
       float sum = 0;
       // Compute sum of all pixel values, with a CImg iterator.
       for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) sum+=*it;
       const float sum2 = img.sum();                                              // Do the same with a built-in method
       \endcode
    **/
typedef const T* const_iterator;

//! Pixel value type.
/**
       Refer to the type of the pixel values of an image instance.
       \note
       - The \c CImg<T>::value_type type of a \c CImg<T> is defined to be a \c T.
       - \c CImg<T>::value_type is actually not used in %CImg methods. It has been mainly defined for
         compatibility with STL naming conventions.
    **/
typedef T value_type;

// Define common types related to template type T.
typedef typename cimg::superset<T,bool>::type Tbool;
typedef typename cimg::superset<T,unsigned char>::type Tuchar;
typedef typename cimg::superset<T,char>::type Tchar;
typedef typename cimg::superset<T,unsigned short>::type Tushort;
typedef typename cimg::superset<T,short>::type Tshort;
typedef typename cimg::superset<T,unsigned int>::type Tuint;
typedef typename cimg::superset<T,int>::type Tint;
typedef typename cimg::superset<T,cimg_ulong>::type Tulong;
typedef typename cimg::superset<T,cimg_long>::type Tlong;
typedef typename cimg::superset<T,float>::type Tfloat;
typedef typename cimg::superset<T,double>::type Tdouble;
typedef typename cimg::last<T,bool>::type boolT;
typedef typename cimg::last<T,unsigned char>::type ucharT;
typedef typename cimg::last<T,char>::type charT;
typedef typename cimg::last<T,unsigned short>::type ushortT;
typedef typename cimg::last<T,short>::type shortT;
typedef typename cimg::last<T,unsigned int>::type uintT;
typedef typename cimg::last<T,int>::type intT;
typedef typename cimg::last<T,cimg_ulong>::type ulongT;
typedef typename cimg::last<T,cimg_long>::type longT;
typedef typename cimg::last<T,cimg_uint64>::type uint64T;
typedef typename cimg::last<T,cimg_int64>::type int64T;
typedef typename cimg::last<T,float>::type floatT;
typedef typename cimg::last<T,double>::type doubleT;

//@}
//---------------------------
//
//! \name Plugins
//@{
//---------------------------
#ifdef cimg_plugin
#include cimg_plugin
#endif
#ifdef cimg_plugin1
#include cimg_plugin1
#endif
#ifdef cimg_plugin2
#include cimg_plugin2
#endif
#ifdef cimg_plugin3
#include cimg_plugin3
#endif
#ifdef cimg_plugin4
#include cimg_plugin4
#endif
#ifdef cimg_plugin5
#include cimg_plugin5
#endif
#ifdef cimg_plugin6
#include cimg_plugin6
#endif
#ifdef cimg_plugin7
#include cimg_plugin7
#endif
#ifdef cimg_plugin8
#include cimg_plugin8
#endif

//@}
//---------------------------------------------------------
//
//! \name Constructors / Destructor / Instance Management
//@{
//---------------------------------------------------------

//! Destroy image.
/**
       \note
       - The pixel buffer data() is deallocated if necessary, e.g. for non-empty and non-shared image instances.
       - Destroying an empty or shared image does nothing actually.
       \warning
       - When destroying a non-shared image, make sure that you will \e not operate on a remaining shared image
         that shares its buffer with the destroyed instance, in order to avoid further invalid memory access
         (to a deallocated buffer).
    **/
~CImg() {
if (!_is_shared) delete[] _data;
}

//! Construct empty image.
/**
       \note
       - An empty image has no pixel data and all of its dimensions width(), height(), depth(), spectrum()
         are set to \c 0, as well as its pixel buffer pointer data().
       - An empty image may be re-assigned afterwards, e.g. with the family of
         assign(unsigned int,unsigned int,unsigned int,unsigned int) methods,
         or by operator=(const CImg<t>&). In all cases, the type of pixels stays \c T.
       - An empty image is never shared.
       \par Example
       \code
       CImg<float> img1, img2;      // Construct two empty images
       img1.assign(256,256,1,3);    // Re-assign 'img1' to be a 256x256x1x3 (color) image
       img2 = img1.get_rand(0,255); // Re-assign 'img2' to be a random-valued version of 'img1'
       img2.assign();               // Re-assign 'img2' to be an empty image again
       \endcode
    **/
CImg():_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {}

//! Construct image with specified size.
/**
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \note
       - It is able to create only \e non-shared images, and allocates thus a pixel buffer data()
         for each constructed image instance.
       - Setting one dimension \c size_x,\c size_y,\c size_z or \c size_c to \c 0 leads to the construction of
         an \e empty image.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. when requested size is too big for available memory).
       \warning
       - The allocated pixel buffer is \e not filled with a default value, and is likely to contain garbage values.
         In order to initialize pixel values during construction (e.g. with \c 0), use constructor
         CImg(unsigned int,unsigned int,unsigned int,unsigned int,T) instead.
       \par Example
       \code
       CImg<float> img1(256,256,1,3);   // Construct a 256x256x1x3 (color) image, filled with garbage values
       CImg<float> img2(256,256,1,3,0); // Construct a 256x256x1x3 (color) image, filled with value '0'
       \endcode
    **/
explicit CImg(const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1):
_is_shared(false) {
size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (siz) {
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Construct image with specified size and initialize pixel values.
/**
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value Initialization value.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int),
         but it also fills the pixel buffer with the specified \c value.
       \warning
       - It cannot be used to construct a vector-valued image and initialize it with \e vector-valued pixels
         (e.g. RGB vector, for color images).
         For this task, you may use fillC() after construction.
    **/
CImg(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c, const T& value):
_is_shared(false) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (siz) {
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
fill(value);
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Construct image with specified size and initialize pixel values from a sequence of integers.
/**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c,
       with pixels of type \c T, and initialize pixel
       values from the specified sequence of integers \c value0,\c value1,\c ...
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value0 First value of the initialization sequence (must be an \e integer).
       \param value1 Second value of the initialization sequence (must be an \e integer).
       \param ...
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with a sequence of specified integer values.
       \warning
       - You must specify \e exactly \c size_x*\c size_y*\c size_z*\c size_c integers in the initialization sequence.
         Otherwise, the constructor may crash or fill your image pixels with garbage.
       \par Example
       \code
       const CImg<float> img(2,2,1,3,      // Construct a 2x2 color (RGB) image
                             0,255,0,255,  // Set the 4 values for the red component
                             0,0,255,255,  // Set the 4 values for the green component
                             64,64,64,64); // Set the 4 values for the blue component
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
     **/
CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
const int value0, const int value1, ...):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
#define _CImg_stdarg(img,a0,a1,N,t) { \
	size_t _siz = (size_t)N; \
	if (_siz--) { \
	  va_list ap; \
	  va_start(ap,a1); \
	  T *ptrd = (img)._data; \
	  *(ptrd++) = (T)a0; \
	  if (_siz--) { \
	    *(ptrd++) = (T)a1; \
	    for ( ; _siz; --_siz) *(ptrd++) = (T)va_arg(ap,t); \
	  } \
	  va_end(ap); \
	} \
      }
assign(size_x,size_y,size_z,size_c);
_CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,int);
}

#if cimg_use_cpp11==1
//! Construct image with specified size and initialize pixel values from an initializer list of integers.
/**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c,
       with pixels of type \c T, and initialize pixel
       values from the specified initializer list of integers { \c value0,\c value1,\c ... }
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param { value0, value1, ... } Initialization list
       \param repeat_values Tells if the value filling process is repeated over the image.

       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with a sequence of specified integer values.
       \par Example
       \code
       const CImg<float> img(2,2,1,3,      // Construct a 2x2 color (RGB) image
                             { 0,255,0,255,    // Set the 4 values for the red component
                               0,0,255,255,    // Set the 4 values for the green component
                               64,64,64,64 }); // Set the 4 values for the blue component
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
    **/
template<typename t>
CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
const std::initializer_list<t> values,
const bool repeat_values=true):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
#define _cimg_constructor_cpp11(repeat_values) \
  auto it = values.begin(); \
  size_t siz = size(); \
  if (repeat_values) for (T *ptrd = _data; siz--; ) { \
    *(ptrd++) = (T)(*(it++)); if (it==values.end()) it = values.begin(); } \
  else { siz = std::min(siz,values.size()); for (T *ptrd = _data; siz--; ) *(ptrd++) = (T)(*(it++)); }
assign(size_x,size_y,size_z,size_c);
_cimg_constructor_cpp11(repeat_values);
}

template<typename t>
CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z,
std::initializer_list<t> values,
const bool repeat_values=true):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(size_x,size_y,size_z);
_cimg_constructor_cpp11(repeat_values);
}

template<typename t>
CImg(const unsigned int size_x, const unsigned int size_y,
std::initializer_list<t> values,
const bool repeat_values=true):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(size_x,size_y);
_cimg_constructor_cpp11(repeat_values);
}

template<typename t>
CImg(const unsigned int size_x,
std::initializer_list<t> values,
const bool repeat_values=true):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(size_x);
_cimg_constructor_cpp11(repeat_values);
}

//! Construct single channel 1D image with pixel values and width obtained from an initializer list of integers.
/**
       Construct a new image instance of size \c width x \c 1 x \c 1 x \c 1,
       with pixels of type \c T, and initialize pixel
       values from the specified initializer list of integers { \c value0,\c value1,\c ... }. Image width is
       given by the size of the initializer list.
       \param { value0, value1, ... } Initialization list
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int) with height=1, depth=1, and spectrum=1,
         but it also fills the pixel buffer with a sequence of specified integer values.
       \par Example
       \code
       const CImg<float> img = {10,20,30,20,10 }; // Construct a 5x1 image with one channel, and set its pixel values
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
     **/
template<typename t>
CImg(const std::initializer_list<t> values):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(values.size(),1,1,1);
auto it = values.begin();
unsigned int siz = _width;
for (T *ptrd = _data; siz--; ) *(ptrd++) = (T)(*(it++));
}

template<typename t>
CImg<T> & operator=(std::initializer_list<t> values) {
_cimg_constructor_cpp11(siz>values.size());
return *this;
}
#endif

//! Construct image with specified size and initialize pixel values from a sequence of doubles.
/**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initialize pixel values from the specified sequence of doubles \c value0,\c value1,\c ...
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value0 First value of the initialization sequence (must be a \e double).
       \param value1 Second value of the initialization sequence (must be a \e double).
       \param ...
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int,int,int,...), but
         takes a sequence of double values instead of integers.
       \warning
       - You must specify \e exactly \c dx*\c dy*\c dz*\c dc doubles in the initialization sequence.
         Otherwise, the constructor may crash or fill your image with garbage.
         For instance, the code below will probably crash on most platforms:
         \code
         const CImg<float> img(2,2,1,1, 0.5,0.5,255,255); // FAIL: The two last arguments are 'int', not 'double'!
         \endcode
     **/
CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
const double value0, const double value1, ...):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(size_x,size_y,size_z,size_c);
_CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,double);
}

//! Construct image with specified size and initialize pixel values from a value string.
/**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initializes pixel values from the specified string \c values.
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param values Value string describing the way pixel values are set.
       \param repeat_values Tells if the value filling process is repeated over the image.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with values described in the value string \c values.
       - Value string \c values may describe two different filling processes:
         - Either \c values is a sequences of values assigned to the image pixels, as in <tt>"1,2,3,7,8,2"</tt>.
           In this case, set \c repeat_values to \c true to periodically fill the image with the value sequence.
         - Either, \c values is a formula, as in <tt>"cos(x/10)*sin(y/20)"</tt>.
           In this case, parameter \c repeat_values is pointless.
       - For both cases, specifying \c repeat_values is mandatory.
         It disambiguates the possible overloading of constructor
         CImg(unsigned int,unsigned int,unsigned int,unsigned int,T) with \c T being a <tt>const char*</tt>.
       - A \c CImgArgumentException is thrown when an invalid value string \c values is specified.
       \par Example
       \code
       const CImg<float> img1(129,129,1,3,"0,64,128,192,255",true), // Construct image from a value sequence
                         img2(129,129,1,3,"if(c==0,255*abs(cos(x/10)),1.8*y)",false); // Construct image from a formula
       (img1,img2).display();
       \endcode
       \image html ref_constructor2.jpg
     **/
CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
const char *const values, const bool repeat_values):_is_shared(false) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (siz) {
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
fill(values,repeat_values);
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Construct image with specified size and initialize pixel values from a memory buffer.
/**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initializes pixel values from the specified \c t* memory buffer.
       \param values Pointer to the input memory buffer.
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param is_shared Tells if input memory buffer must be shared by the current instance.
       \note
       - If \c is_shared is \c false, the image instance allocates its own pixel buffer,
         and values from the specified input buffer are copied to the instance buffer.
         If buffer types \c T and \c t are different, a regular static cast is performed during buffer copy.
       - Otherwise, the image instance does \e not allocate a new buffer, and uses the input memory buffer as its
         own pixel buffer. This case requires that types \c T and \c t are the same. Later, destroying such a shared
         image will not deallocate the pixel buffer, this task being obviously charged to the initial buffer allocator.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. when requested size is too big for available memory).
       \warning
       - You must take care when operating on a shared image, since it may have an invalid pixel buffer pointer data()
         (e.g. already deallocated).
       \par Example
       \code
       unsigned char tab[256*256] = { 0 };
       CImg<unsigned char> img1(tab,256,256,1,1,false), // Construct new non-shared image from buffer 'tab'
                           img2(tab,256,256,1,1,true);  // Construct new shared-image from buffer 'tab'
       tab[1024] = 255;                                 // Here, 'img2' is indirectly modified, but not 'img1'
       \endcode
    **/
template<typename t>
CImg(const t *const values, const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1, const bool is_shared=false):_is_shared(false) {
if (is_shared) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgArgumentException(_cimg_instance
"CImg(): Invalid construction request of a (%u,%u,%u,%u) shared instance "
"from a (%s*) buffer (pixel types are different).",
cimg_instance,
size_x,size_y,size_z,size_c,CImg<t>::pixel_type());
}
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (values && siz) {
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);

}
const t *ptrs = values; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Construct image with specified size and initialize pixel values from a memory buffer \specialization.
CImg(const T *const values, const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1, const bool is_shared=false) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (values && siz) {
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c; _is_shared = is_shared;
if (_is_shared) _data = const_cast<T*>(values);
else {
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
std::memcpy(_data,values,siz*sizeof(T));
}
} else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
}

//! Construct image from reading an image file.
/**
       Construct a new image instance with pixels of type \c T, and initialize pixel values with the data read from
       an image file.
       \param filename Filename, as a C-string.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it reads the image
         dimensions and pixel values from the specified image file.
       - The recognition of the image file format by %CImg higly depends on the tools installed on your system
         and on the external libraries you used to link your code against.
       - Considered pixel type \c T should better fit the file format specification, or data loss may occur during
         file load (e.g. constructing a \c CImg<unsigned char> from a float-valued image file).
       - A \c CImgIOException is thrown when the specified \c filename cannot be read, or if the file format is not
         recognized.
       \par Example
       \code
       const CImg<float> img("reference.jpg");
       img.display();
       \endcode
       \image html ref_image.jpg
    **/
explicit CImg(const char *const filename):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(filename);
}

//! Construct image copy.
/**
       Construct a new image instance with pixels of type \c T, as a copy of an existing \c CImg<t> instance.
       \param img Input image to copy.
       \note
       - Constructed copy has the same size width() x height() x depth() x spectrum() and pixel values as the
         input image \c img.
       - If input image \c img is \e shared and if types \c T and \c t are the same, the constructed copy is also
         \e shared, and shares its pixel buffer with \c img.
         Modifying a pixel value in the constructed copy will thus also modifies it in the input image \c img.
         This behavior is needful to allow functions to return shared images.
       - Otherwise, the constructed copy allocates its own pixel buffer, and copies pixel values from the input
         image \c img into its buffer. The copied pixel values may be eventually statically casted if types \c T and
         \c t are different.
       - Constructing a copy from an image \c img when types \c t and \c T are the same is significantly faster than
         with different types.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. not enough available memory).
    **/
template<typename t>
CImg(const CImg<t>& img):_is_shared(false) {
const size_t siz = (size_t)img.size();
if (img._data && siz) {
_width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
img._width,img._height,img._depth,img._spectrum);
}
const t *ptrs = img._data; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Construct image copy \specialization.
CImg(const CImg<T>& img) {
const size_t siz = (size_t)img.size();
if (img._data && siz) {
_width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
_is_shared = img._is_shared;
if (_is_shared) _data = const_cast<T*>(img._data);
else {
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
img._width,img._height,img._depth,img._spectrum);

}
std::memcpy(_data,img._data,siz*sizeof(T));
}
} else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
}

//! Advanced copy constructor.
/**
       Construct a new image instance with pixels of type \c T, as a copy of an existing \c CImg<t> instance,
       while forcing the shared state of the constructed copy.
       \param img Input image to copy.
       \param is_shared Tells about the shared state of the constructed copy.
       \note
       - Similar to CImg(const CImg<t>&), except that it allows to decide the shared state of
         the constructed image, which does not depend anymore on the shared state of the input image \c img:
         - If \c is_shared is \c true, the constructed copy will share its pixel buffer with the input image \c img.
           For that case, the pixel types \c T and \c t \e must be the same.
         - If \c is_shared is \c false, the constructed copy will allocate its own pixel buffer, whether the input
           image \c img is shared or not.
       - A \c CImgArgumentException is thrown when a shared copy is requested with different pixel types \c T and \c t.
    **/
template<typename t>
CImg(const CImg<t>& img, const bool is_shared):_is_shared(false) {
if (is_shared) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgArgumentException(_cimg_instance
"CImg(): Invalid construction request of a shared instance from a "
"CImg<%s> image (%u,%u,%u,%u,%p) (pixel types are different).",
cimg_instance,
CImg<t>::pixel_type(),img._width,img._height,img._depth,img._spectrum,img._data);
}
const size_t siz = (size_t)img.size();
if (img._data && siz) {
_width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
img._width,img._height,img._depth,img._spectrum);
}
const t *ptrs = img._data; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
} else { _width = _height = _depth = _spectrum = 0; _data = 0; }
}

//! Advanced copy constructor \specialization.
CImg(const CImg<T>& img, const bool is_shared) {
const size_t siz = (size_t)img.size();
if (img._data && siz) {
_width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
_is_shared = is_shared;
if (_is_shared) _data = const_cast<T*>(img._data);
else {
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
img._width,img._height,img._depth,img._spectrum);
}
std::memcpy(_data,img._data,siz*sizeof(T));
}
} else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
}

//! Construct image with dimensions borrowed from another image.
/**
       Construct a new image instance with pixels of type \c T, and size get from some dimensions of an existing
       \c CImg<t> instance.
       \param img Input image from which dimensions are borrowed.
       \param dimensions C-string describing the image size along the X,Y,Z and C-dimensions.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it takes the image dimensions
         (\e not its pixel values) from an existing \c CImg<t> instance.
       - The allocated pixel buffer is \e not filled with a default value, and is likely to contain garbage values.
         In order to initialize pixel values (e.g. with \c 0), use constructor CImg(const CImg<t>&,const char*,T)
         instead.
       \par Example
       \code
       const CImg<float> img1(256,128,1,3),      // 'img1' is a 256x128x1x3 image
                         img2(img1,"xyzc"),      // 'img2' is a 256x128x1x3 image
                         img3(img1,"y,x,z,c"),   // 'img3' is a 128x256x1x3 image
                         img4(img1,"c,x,y,3",0), // 'img4' is a 3x128x256x3 image (with pixels initialized to '0')
       \endcode
     **/
template<typename t>
CImg(const CImg<t>& img, const char *const dimensions):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(img,dimensions);
}

//! Construct image with dimensions borrowed from another image and initialize pixel values.
/**
       Construct a new image instance with pixels of type \c T, and size get from the dimensions of an existing
       \c CImg<t> instance, and set all pixel values to specified \c value.
       \param img Input image from which dimensions are borrowed.
       \param dimensions String describing the image size along the X,Y,Z and V-dimensions.
       \param value Value used for initialization.
       \note
       - Similar to CImg(const CImg<t>&,const char*), but it also fills the pixel buffer with the specified \c value.
     **/
template<typename t>
CImg(const CImg<t>& img, const char *const dimensions, const T& value):
_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
assign(img,dimensions).fill(value);
}

//! Construct image from a display window.
/**
       Construct a new image instance with pixels of type \c T, as a snapshot of an existing \c CImgDisplay instance.
       \param disp Input display window.
       \note
       - The width() and height() of the constructed image instance are the same as the specified \c CImgDisplay.
       - The depth() and spectrum() of the constructed image instance are respectively set to \c 1 and \c 3
         (i.e. a 2D color image).
       - The image pixels are read as 8-bits RGB values.
     **/
explicit CImg(const CImgDisplay &disp):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
disp.snapshot(*this);
}

// Constructor and assignment operator for rvalue references (c++11).
// This avoids an additional image copy for methods returning new images. Can save RAM for big images !
#if cimg_use_cpp11==1
CImg(CImg<T>&& img):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
swap(img);
}
CImg<T>& operator=(CImg<T>&& img) {
if (_is_shared) return assign(img);
return img.swap(*this);
}
#endif

//! Construct empty image \inplace.
/**
       In-place version of the default constructor CImg(). It simply resets the instance to an empty image.
    **/
CImg<T>& assign() {
if (!_is_shared) delete[] _data;
_width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0;
return *this;
}

//! Construct image with specified size \inplace.
/**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int).
    **/
CImg<T>& assign(const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (!siz) return assign();
const size_t curr_siz = (size_t)size();
if (siz!=curr_siz) {
if (_is_shared)
throw CImgArgumentException(_cimg_instance
"assign(): Invalid assignement request of shared instance from specified "
"image (%u,%u,%u,%u).",
cimg_instance,
size_x,size_y,size_z,size_c);
else {
delete[] _data;
try { _data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"assign(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
}
}
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
return *this;
}

//! Construct image with specified size and initialize pixel values \inplace.
/**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,T).
    **/
CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c, const T& value) {
return assign(size_x,size_y,size_z,size_c).fill(value);
}

//! Construct image with specified size and initialize pixel values from a sequence of integers \inplace.
/**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,int,int,...).
    **/
CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c,
const int value0, const int value1, ...) {
assign(size_x,size_y,size_z,size_c);
_CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,int);
return *this;
}

//! Construct image with specified size and initialize pixel values from a sequence of doubles \inplace.
/**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,double,double,...).
    **/
CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c,
const double value0, const double value1, ...) {
assign(size_x,size_y,size_z,size_c);
_CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,double);
return *this;
}

//! Construct image with specified size and initialize pixel values from a value string \inplace.
/**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,const char*,bool).
    **/
CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c,
const char *const values, const bool repeat_values) {
return assign(size_x,size_y,size_z,size_c).fill(values,repeat_values);
}

//! Construct image with specified size and initialize pixel values from a memory buffer \inplace.
/**
       In-place version of the constructor CImg(const t*,unsigned int,unsigned int,unsigned int,unsigned int).
    **/
template<typename t>
CImg<T>& assign(const t *const values, const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (!values || !siz) return assign();
assign(size_x,size_y,size_z,size_c);
const t *ptrs = values; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
return *this;
}

//! Construct image with specified size and initialize pixel values from a memory buffer \specialization.
CImg<T>& assign(const T *const values, const unsigned int size_x, const unsigned int size_y=1,
const unsigned int size_z=1, const unsigned int size_c=1) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (!values || !siz) return assign();
const size_t curr_siz = (size_t)size();
if (values==_data && siz==curr_siz) return assign(size_x,size_y,size_z,size_c);
if (_is_shared || values + siz<_data || values>=_data + size()) {
assign(size_x,size_y,size_z,size_c);
if (_is_shared) std::memmove((void*)_data,(void*)values,siz*sizeof(T));
else std::memcpy((void*)_data,(void*)values,siz*sizeof(T));
} else {
T *new_data = 0;
try { new_data = new T[siz]; } catch (...) {
_width = _height = _depth = _spectrum = 0; _data = 0;
throw CImgInstanceException(_cimg_instance
"assign(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
cimg_instance,
cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
size_x,size_y,size_z,size_c);
}
std::memcpy((void*)new_data,(void*)values,siz*sizeof(T));
delete[] _data; _data = new_data; _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
}
return *this;
}

//! Construct image with specified size and initialize pixel values from a memory buffer \overloading.
template<typename t>
CImg<T>& assign(const t *const values, const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c, const bool is_shared) {
if (is_shared)
throw CImgArgumentException(_cimg_instance
"assign(): Invalid assignment request of shared instance from (%s*) buffer"
"(pixel types are different).",
cimg_instance,
CImg<t>::pixel_type());
return assign(values,size_x,size_y,size_z,size_c);
}

//! Construct image with specified size and initialize pixel values from a memory buffer \overloading.
CImg<T>& assign(const T *const values, const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c, const bool is_shared) {
const size_t siz = (size_t)size_x*size_y*size_z*size_c;
if (!values || !siz) return assign();
if (!is_shared) { if (_is_shared) assign(); assign(values,size_x,size_y,size_z,size_c); }
else {
if (!_is_shared) {
if (values + siz<_data || values>=_data + size()) assign();
else cimg::warn(_cimg_instance
"assign(): Shared image instance has overlapping memory.",
cimg_instance);
}
_width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c; _is_shared = true;
_data = const_cast<T*>(values);
}
return *this;
}

//! Construct image from reading an image file \inplace.
/**
       In-place version of the constructor CImg(const char*).
    **/
CImg<T>& assign(const char *const filename) {
return load(filename);
}

//! Construct image copy \inplace.
/**
       In-place version of the constructor CImg(const CImg<t>&).
    **/
template<typename t>
CImg<T>& assign(const CImg<t>& img) {
return assign(img._data,img._width,img._height,img._depth,img._spectrum);
}

//! In-place version of the advanced copy constructor.
/**
       In-place version of the constructor CImg(const CImg<t>&,bool).
     **/
template<typename t>
CImg<T>& assign(const CImg<t>& img, const bool is_shared) {
return assign(img._data,img._width,img._height,img._depth,img._spectrum,is_shared);
}

//! Construct image with dimensions borrowed from another image \inplace.
/**
       In-place version of the constructor CImg(const CImg<t>&,const char*).
    **/
template<typename t>
CImg<T>& assign(const CImg<t>& img, const char *const dimensions) {
if (!dimensions || !*dimensions) return assign(img._width,img._height,img._depth,img._spectrum);
unsigned int siz[4] = { 0,1,1,1 }, k = 0;
CImg<charT> item(256);
for (const char *s = dimensions; *s && k<4; ++k) {
if (cimg_sscanf(s,"%255[^0-9%xyzvwhdcXYZVWHDC]",item._data)>0) s+=std::strlen(item);
if (*s) {
unsigned int val = 0; char sep = 0;
if (cimg_sscanf(s,"%u%c",&val,&sep)>0) {
if (sep=='%') siz[k] = val*(k==0?_width:k==1?_height:k==2?_depth:_spectrum)/100;
else siz[k] = val;
while (*s>='0' && *s<='9') ++s;
if (sep=='%') ++s;
} else switch (cimg::lowercase(*s)) {
case 'x' : case 'w' : siz[k] = img._width; ++s; break;
case 'y' : case 'h' : siz[k] = img._height; ++s; break;
case 'z' : case 'd' : siz[k] = img._depth; ++s; break;
case 'c' : case 's' : siz[k] = img._spectrum; ++s; break;
default :
throw CImgArgumentException(_cimg_instance
"assign(): Invalid character '%c' detected in specified dimension string '%s'.",
cimg_instance,
*s,dimensions);
}
}
}
return assign(siz[0],siz[1],siz[2],siz[3]);
}

//! Construct image with dimensions borrowed from another image and initialize pixel values \inplace.
/**
       In-place version of the constructor CImg(const CImg<t>&,const char*,T).
    **/
template<typename t>
CImg<T>& assign(const CImg<t>& img, const char *const dimensions, const T& value) {
return assign(img,dimensions).fill(value);
}

//! Construct image from a display window \inplace.
/**
       In-place version of the constructor CImg(const CImgDisplay&).
    **/
CImg<T>& assign(const CImgDisplay &disp) {
disp.snapshot(*this);
return *this;
}

//! Construct empty image \inplace.
/**
       Equivalent to assign().
       \note
       - It has been defined for compatibility with STL naming conventions.
    **/
CImg<T>& clear() {
return assign();
}

//! Transfer content of an image instance into another one.
/**
       Transfer the dimensions and the pixel buffer content of an image instance into another one,
       and replace instance by an empty image. It avoids the copy of the pixel buffer
       when possible.
       \param img Destination image.
       \note
       - Pixel types \c T and \c t of source and destination images can be different, though the process is
         designed to be instantaneous when \c T and \c t are the same.
       \par Example
       \code
       CImg<float> src(256,256,1,3,0), // Construct a 256x256x1x3 (color) image filled with value '0'
                   dest(16,16);        // Construct a 16x16x1x1 (scalar) image
       src.move_to(dest);              // Now, 'src' is empty and 'dest' is the 256x256x1x3 image
       \endcode
    **/
template<typename t>
CImg<t>& move_to(CImg<t>& img) {
img.assign(*this);
assign();
return img;
}

//! Transfer content of an image instance into another one \specialization.
CImg<T>& move_to(CImg<T>& img) {
if (_is_shared || img._is_shared) img.assign(*this);
else swap(img);
assign();
return img;
}

//! Transfer content of an image instance into a new image in an image list.
/**
       Transfer the dimensions and the pixel buffer content of an image instance
       into a newly inserted image at position \c pos in specified \c CImgList<t> instance.
       \param list Destination list.
       \param pos Position of the newly inserted image in the list.
       \note
       - When optional parameter \c pos is ommited, the image instance is transfered as a new
         image at the end of the specified \c list.
       - It is convenient to sequentially insert new images into image lists, with no
         additional copies of memory buffer.
       \par Example
       \code
       CImgList<float> list;             // Construct an empty image list
       CImg<float> img("reference.jpg"); // Read image from filename
       img.move_to(list);                // Transfer image content as a new item in the list (no buffer copy)
       \endcode
    **/
template<typename t>
CImgList<t>& move_to(CImgList<t>& list, const unsigned int pos=~0U) {
const unsigned int npos = pos>list._width?list._width:pos;
move_to(list.insert(1,npos)[npos]);
return list;
}

//! Swap fields of two image instances.
/**
      \param img Image to swap fields with.
      \note
      - It can be used to interchange the content of two images in a very fast way. Can be convenient when dealing
        with algorithms requiring two swapping buffers.
      \par Example
      \code
      CImg<float> img1("lena.jpg"),
                  img2("milla.jpg");
      img1.swap(img2);    // Now, 'img1' is 'milla' and 'img2' is 'lena'
      \endcode
    **/
CImg<T>& swap(CImg<T>& img) {
cimg::swap(_width,img._width,_height,img._height,_depth,img._depth,_spectrum,img._spectrum);
cimg::swap(_data,img._data);
cimg::swap(_is_shared,img._is_shared);
return img;
}

//! Return a reference to an empty image.
/**
       \note
       This function is useful mainly to declare optional parameters having type \c CImg<T> in functions prototypes,
       e.g.
       \code
       void f(const int x=0, const int y=0, const CImg<float>& img=CImg<float>::empty());
       \endcode
     **/
static CImg<T>& empty() {
static CImg<T> _empty;
return _empty.assign();
}

//! Return a reference to an empty image \const.
static const CImg<T>& const_empty() {
static const CImg<T> _empty;
return _empty;
}

//@}
//------------------------------------------
//
//! \name Overloaded Operators
//@{
//------------------------------------------

//! Access to a pixel value.
/**
       Return a reference to a located pixel value of the image instance,
       being possibly \e const, whether the image instance is \e const or not.
       This is the standard method to get/set pixel values in \c CImg<T> images.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Range of pixel coordinates start from <tt>(0,0,0,0)</tt> to
         <tt>(width() - 1,height() - 1,depth() - 1,spectrum() - 1)</tt>.
       - Due to the particular arrangement of the pixel buffers defined in %CImg, you can omit one coordinate if the
         corresponding dimension is equal to \c 1.
         For instance, pixels of a 2D image (depth() equal to \c 1) can be accessed by <tt>img(x,y,c)</tt> instead of
         <tt>img(x,y,0,c)</tt>.
       \warning
       - There is \e no boundary checking done in this operator, to make it as fast as possible.
         You \e must take care of out-of-bounds access by yourself, if necessary.
         For debuging purposes, you may want to define macro \c 'cimg_verbosity'>=3 to enable additional boundary
         checking operations in this operator. In that case, warning messages will be printed on the error output
         when accessing out-of-bounds pixels.
       \par Example
       \code
       CImg<float> img(100,100,1,3,0); // Construct a 100x100x1x3 (color) image with pixels set to '0'
       const float
          valR = img(10,10,0,0), // Read red value at coordinates (10,10)
          valG = img(10,10,0,1), // Read green value at coordinates (10,10)
          valB = img(10,10,2),   // Read blue value at coordinates (10,10) (Z-coordinate can be omitted)
          avg = (valR + valG + valB)/3; // Compute average pixel value
       img(10,10,0) = img(10,10,1) = img(10,10,2) = avg; // Replace the color pixel (10,10) by the average grey value
       \endcode
    **/
#if cimg_verbosity>=3
T& operator()(const unsigned int x, const unsigned int y=0,
const unsigned int z=0, const unsigned int c=0) {
const ulongT off = (ulongT)offset(x,y,z,c);
if (!_data || off>=size()) {
cimg::warn(_cimg_instance
"operator(): Invalid pixel request, at coordinates (%d,%d,%d,%d) [offset=%u].",
cimg_instance,
(int)x,(int)y,(int)z,(int)c,off);
return *_data;
}
else return _data[off];
}

//! Access to a pixel value \const.
const T& operator()(const unsigned int x, const unsigned int y=0,
const unsigned int z=0, const unsigned int c=0) const {
return const_cast<CImg<T>*>(this)->operator()(x,y,z,c);
}

//! Access to a pixel value.
/**
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param wh Precomputed offset, must be equal to <tt>width()*\ref height()</tt>.
       \param whd Precomputed offset, must be equal to <tt>width()*\ref height()*\ref depth()</tt>.
       \note
       - Similar to (but faster than) operator()().
         It uses precomputed offsets to optimize memory access. You may use it to optimize
         the reading/writing of several pixel values in the same image (e.g. in a loop).
     **/
T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
const ulongT wh, const ulongT whd=0) {
cimg::unused(wh,whd);
return (*this)(x,y,z,c);
}

//! Access to a pixel value \const.
const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
const ulongT wh, const ulongT whd=0) const {
cimg::unused(wh,whd);
return (*this)(x,y,z,c);
}
#else
T& operator()(const unsigned int x) {
return _data[x];
}

const T& operator()(const unsigned int x) const {
return _data[x];
}

T& operator()(const unsigned int x, const unsigned int y) {
return _data[x + y*_width];
}

const T& operator()(const unsigned int x, const unsigned int y) const {
return _data[x + y*_width];
}

T& operator()(const unsigned int x, const unsigned int y, const unsigned int z) {
return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height];
}

const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z) const {
return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height];
}

T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c) {
return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height + c*(ulongT)_width*_height*_depth];
}

const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c) const {
return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height + c*(ulongT)_width*_height*_depth];
}

T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int,
const ulongT wh) {
return _data[x + y*_width + z*wh];
}

const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int,
const ulongT wh) const {
return _data[x + y*_width + z*wh];
}

T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
const ulongT wh, const ulongT whd) {
return _data[x + y*_width + z*wh + c*whd];
}

const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
const ulongT wh, const ulongT whd) const {
return _data[x + y*_width + z*wh + c*whd];
}
#endif

//! Implicitely cast an image into a \c T*.
/**
       Implicitely cast a \c CImg<T> instance into a \c T* or \c const \c T* pointer, whether the image instance
       is \e const or not. The returned pointer points on the first value of the image pixel buffer.
       \note
       - It simply returns the pointer data() to the pixel buffer.
       - This implicit conversion is convenient to test the empty state of images (data() being \c 0 in this case), e.g.
       \code
       CImg<float> img1(100,100), img2; // 'img1' is a 100x100 image, 'img2' is an empty image
       if (img1) {                      // Test succeeds, 'img1' is not an empty image
         if (!img2) {                   // Test succeeds, 'img2' is an empty image
           std::printf("'img1' is not empty, 'img2' is empty.");
         }
       }
       \endcode
       - It also allows to use brackets to access pixel values, without need for a \c CImg<T>::operator[](), e.g.
       \code
       CImg<float> img(100,100);
       const float value = img[99]; // Access to value of the last pixel on the first row
       img[510] = 255;              // Set pixel value at (10,5)
       \endcode
    **/
operator T*() {
return _data;
}

//! Implicitely cast an image into a \c T* \const.
operator const T*() const {
return _data;
}

//! Assign a value to all image pixels.
/**
       Assign specified \c value to each pixel value of the image instance.
       \param value Value that will be assigned to image pixels.
       \note
       - The image size is never modified.
       - The \c value may be casted to pixel type \c T if necessary.
       \par Example
       \code
       CImg<char> img(100,100); // Declare image (with garbage values)
       img = 0;                 // Set all pixel values to '0'
       img = 1.2;               // Set all pixel values to '1' (cast of '1.2' as a 'char')
       \endcode
    **/
CImg<T>& operator=(const T& value) {
return fill(value);
}

//! Assign pixels values from a specified expression.
/**
       Initialize all pixel values from the specified string \c expression.
       \param expression Value string describing the way pixel values are set.
       \note
       - String parameter \c expression may describe different things:
         - If \c expression is a list of values (as in \c "1,2,3,8,3,2"), or a formula (as in \c "(x*y)%255"),
           the pixel values are set from specified \c expression and the image size is not modified.
         - If \c expression is a filename (as in \c "reference.jpg"), the corresponding image file is loaded and
           replace the image instance. The image size is modified if necessary.
       \par Example
       \code
       CImg<float> img1(100,100), img2(img1), img3(img1); // Declare 3 scalar images 100x100 with unitialized values
       img1 = "0,50,100,150,200,250,200,150,100,50"; // Set pixel values of 'img1' from a value sequence
       img2 = "10*((x*y)%25)";                       // Set pixel values of 'img2' from a formula
       img3 = "reference.jpg";                       // Set pixel values of 'img3' from a file (image size is modified)
       (img1,img2,img3).display();
       \endcode
       \image html ref_operator_eq.jpg
    **/
CImg<T>& operator=(const char *const expression) {
const unsigned int omode = cimg::exception_mode();
cimg::exception_mode(0);
try {
_fill(expression,true,1,0,0,"operator=",0);
} catch (CImgException&) {
cimg::exception_mode(omode);
load(expression);
}
cimg::exception_mode(omode);
return *this;
}

//! Copy an image into the current image instance.
/**
       Similar to the in-place copy constructor assign(const CImg<t>&).
    **/
template<typename t>
CImg<T>& operator=(const CImg<t>& img) {
return assign(img);
}

//! Copy an image into the current image instance \specialization.
CImg<T>& operator=(const CImg<T>& img) {
return assign(img);
}

//! Copy the content of a display window to the current image instance.
/**
       Similar to assign(const CImgDisplay&).
    **/
CImg<T>& operator=(const CImgDisplay& disp) {
disp.snapshot(*this);
return *this;
}

//! In-place addition operator.
/**
       Add specified \c value to all pixels of an image instance.
       \param value Value to add.
       \note
       - Resulting pixel values are casted to fit the pixel type \c T.
         For instance, adding \c 0.2 to a \c CImg<char> is possible but does nothing indeed.
       - Overflow values are treated as with standard C++ numeric types. For instance,
       \code
       CImg<unsigned char> img(100,100,1,1,255); // Construct a 100x100 image with pixel values '255'
       img+=1;                                   // Add '1' to each pixels -> Overflow
       // here all pixels of image 'img' are equal to '0'.
       \endcode
       - To prevent value overflow, you may want to consider pixel type \c T as \c float or \c double,
         and use cut() after addition.
       \par Example
       \code
       CImg<unsigned char> img1("reference.jpg"); // Load a 8-bits RGB image (values in [0,255])
       CImg<float> img2(img1); // Construct a float-valued copy of 'img1'
       img2+=100; // Add '100' to pixel values -> goes out of [0,255] but no problems with floats
       img2.cut(0,255); // Cut values in [0,255] to fit the 'unsigned char' constraint
       img1 = img2; // Rewrite safe result in 'unsigned char' version 'img1'
       const CImg<unsigned char> img3 = (img1 + 100).cut(0,255); // Do the same in a more simple and elegant way
       (img1,img2,img3).display();
       \endcode
       \image html ref_operator_plus.jpg
     **/
template<typename t>
CImg<T>& operator+=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr + value,524288);
return *this;
}

//! In-place addition operator.
/**
       Add values to image pixels, according to the specified string \c expression.
       \param expression Value string describing the way pixel values are added.
       \note
       - Similar to operator=(const char*), except that it adds values to the pixels of the current image instance,
         instead of assigning them.
    **/
CImg<T>& operator+=(const char *const expression) {
return *this+=(+*this)._fill(expression,true,1,0,0,"operator+=",this);
}

//! In-place addition operator.
/**
       Add values to image pixels, according to the values of the input image \c img.
       \param img Input image to add.
       \note
       - The size of the image instance is never modified.
       - It is not mandatory that input image \c img has the same size as the image instance.
         If less values are available in \c img, then the values are added periodically. For instance, adding one
         WxH scalar image (spectrum() equal to \c 1) to one WxH color image (spectrum() equal to \c 3)
         means each color channel will be incremented with the same values at the same locations.
       \par Example
       \code
       CImg<float> img1("reference.jpg"); // Load a RGB color image (img1.spectrum()==3)
       // Construct a scalar shading (img2.spectrum()==1).
       const CImg<float> img2(img1.width(),img.height(),1,1,"255*(x/w)^2");
       img1+=img2; // Add shading to each channel of 'img1'
       img1.cut(0,255); // Prevent [0,255] overflow
       (img2,img1).display();
       \endcode
       \image html ref_operator_plus1.jpg
    **/
template<typename t>
CImg<T>& operator+=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this+=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)(*ptrd + *(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd + *(ptrs++));
}
return *this;
}

//! In-place increment operator (prefix).
/**
       Add \c 1 to all image pixels, and return a reference to the current incremented image instance.
       \note
       - Writing \c ++img is equivalent to \c img+=1.
     **/
CImg<T>& operator++() {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr + 1,524288);
return *this;
}

//! In-place increment operator (postfix).
/**
       Add \c 1 to all image pixels, and return a new copy of the initial (pre-incremented) image instance.
       \note
       - Use the prefixed version operator++() if you don't need a copy of the initial
         (pre-incremented) image instance, since a useless image copy may be expensive in terms of memory usage.
     **/
CImg<T> operator++(int) {
const CImg<T> copy(*this,false);
++*this;
return copy;
}

//! Return a non-shared copy of the image instance.
/**
       \note
       - Use this operator to ensure you get a non-shared copy of an image instance with same pixel type \c T.
         Indeed, the usual copy constructor CImg<T>(const CImg<T>&) returns a shared copy of a shared input image,
         and it may be not desirable to work on a regular copy (e.g. for a resize operation) if you have no
         information about the shared state of the input image.
       - Writing \c (+img) is equivalent to \c CImg<T>(img,false).
    **/
CImg<T> operator+() const {
return CImg<T>(*this,false);
}

//! Addition operator.
/**
       Similar to operator+=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
template<typename t>
CImg<_cimg_Tt> operator+(const t value) const {
return CImg<_cimg_Tt>(*this,false)+=value;
}

//! Addition operator.
/**
       Similar to operator+=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
CImg<Tfloat> operator+(const char *const expression) const {
return CImg<Tfloat>(*this,false)+=expression;
}

//! Addition operator.
/**
       Similar to operator+=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
template<typename t>
CImg<_cimg_Tt> operator+(const CImg<t>& img) const {
return CImg<_cimg_Tt>(*this,false)+=img;
}

//! In-place substraction operator.
/**
       Similar to operator+=(const t), except that it performs a substraction instead of an addition.
     **/
template<typename t>
CImg<T>& operator-=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr - value,524288);
return *this;
}

//! In-place substraction operator.
/**
       Similar to operator+=(const char*), except that it performs a substraction instead of an addition.
     **/
CImg<T>& operator-=(const char *const expression) {
return *this-=(+*this)._fill(expression,true,1,0,0,"operator-=",this);
}

//! In-place substraction operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a substraction instead of an addition.
     **/
template<typename t>
CImg<T>& operator-=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this-=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)(*ptrd - *(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd - *(ptrs++));
}
return *this;
}

//! In-place decrement operator (prefix).
/**
       Similar to operator++(), except that it performs a decrement instead of an increment.
    **/
CImg<T>& operator--() {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr - 1,524288);
return *this;
}

//! In-place decrement operator (postfix).
/**
       Similar to operator++(int), except that it performs a decrement instead of an increment.
    **/
CImg<T> operator--(int) {
const CImg<T> copy(*this,false);
--*this;
return copy;
}

//! Replace each pixel by its opposite value.
/**
       \note
       - If the computed opposite values are out-of-range, they are treated as with standard C++ numeric types.
         For instance, the \c unsigned \c char opposite of \c 1 is \c 255.
       \par Example
       \code
       const CImg<unsigned char>
         img1("reference.jpg"),   // Load a RGB color image
         img2 = -img1;            // Compute its opposite (in 'unsigned char')
       (img1,img2).display();
       \endcode
       \image html ref_operator_minus.jpg
     **/
CImg<T> operator-() const {
return CImg<T>(_width,_height,_depth,_spectrum,(T)0)-=*this;
}

//! Substraction operator.
/**
       Similar to operator-=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator-(const t value) const {
return CImg<_cimg_Tt>(*this,false)-=value;
}

//! Substraction operator.
/**
       Similar to operator-=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
CImg<Tfloat> operator-(const char *const expression) const {
return CImg<Tfloat>(*this,false)-=expression;
}

//! Substraction operator.
/**
       Similar to operator-=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator-(const CImg<t>& img) const {
return CImg<_cimg_Tt>(*this,false)-=img;
}

//! In-place multiplication operator.
/**
       Similar to operator+=(const t), except that it performs a multiplication instead of an addition.
     **/
template<typename t>
CImg<T>& operator*=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr * value,262144);
return *this;
}

//! In-place multiplication operator.
/**
       Similar to operator+=(const char*), except that it performs a multiplication instead of an addition.
     **/
CImg<T>& operator*=(const char *const expression) {
return mul((+*this)._fill(expression,true,1,0,0,"operator*=",this));
}

//! In-place multiplication operator.
/**
       Replace the image instance by the matrix multiplication between the image instance and the specified matrix
       \c img.
       \param img Second operand of the matrix multiplication.
       \note
       - It does \e not compute a pointwise multiplication between two images. For this purpose, use
         mul(const CImg<t>&) instead.
       - The size of the image instance can be modified by this operator.
       \par Example
       \code
       CImg<float> A(2,2,1,1, 1,2,3,4);   // Construct 2x2 matrix A = [1,2;3,4]
       const CImg<float> X(1,2,1,1, 1,2); // Construct 1x2 vector X = [1;2]
       A*=X;                              // Assign matrix multiplication A*X to 'A'
       // 'A' is now a 1x2 vector whose values are [5;11].
       \endcode
    **/
template<typename t>
CImg<T>& operator*=(const CImg<t>& img) {
return ((*this)*img).move_to(*this);
}

//! Multiplication operator.
/**
       Similar to operator*=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator*(const t value) const {
return CImg<_cimg_Tt>(*this,false)*=value;
}

//! Multiplication operator.
/**
       Similar to operator*=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
CImg<Tfloat> operator*(const char *const expression) const {
return CImg<Tfloat>(*this,false)*=expression;
}

//! Multiplication operator.
/**
       Similar to operator*=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator*(const CImg<t>& img) const {
typedef _cimg_Ttdouble Ttdouble;
typedef _cimg_Tt Tt;
if (_width!=img._height || _depth!=1 || _spectrum!=1)
throw CImgArgumentException(_cimg_instance
"operator*(): Invalid multiplication of instance by specified "
"matrix (%u,%u,%u,%u,%p)",
cimg_instance,
img._width,img._height,img._depth,img._spectrum,img._data);
CImg<Tt> res(img._width,_height);

// Check for common cases to optimize.
if (img._width==1) { // Matrix * Vector
if (_height==1) switch (_width) { // Vector^T * Vector
case 1 :
res[0] = (Tt)((Ttdouble)_data[0]*img[0]);
return res;
case 2 :
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1]);
return res;
case 3 :
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1] +
(Ttdouble)_data[2]*img[2]);
return res;
case 4 :
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1] +
(Ttdouble)_data[2]*img[2] + (Ttdouble)_data[3]*img[3]);
return res;
default : {
Ttdouble val = 0;
cimg_forX(*this,i) val+=(Ttdouble)_data[i]*img[i];
res[0] = val;
return res;
}
} else if (_height==_width) switch (_width) { // Square_matrix * Vector
case 2 : // 2x2_matrix * Vector
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1]);
res[1] = (Tt)((Ttdouble)_data[2]*img[0] + (Ttdouble)_data[3]*img[1]);
return res;
case 3 : // 3x3_matrix * Vector
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1] +
(Ttdouble)_data[2]*img[2]);
res[1] = (Tt)((Ttdouble)_data[3]*img[0] + (Ttdouble)_data[4]*img[1] +
(Ttdouble)_data[5]*img[2]);
res[2] = (Tt)((Ttdouble)_data[6]*img[0] + (Ttdouble)_data[7]*img[1] +
(Ttdouble)_data[8]*img[2]);
return res;
case 4 : // 4x4_matrix * Vector
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[1] +
(Ttdouble)_data[2]*img[2] + (Ttdouble)_data[3]*img[3]);
res[1] = (Tt)((Ttdouble)_data[4]*img[0] + (Ttdouble)_data[5]*img[1] +
(Ttdouble)_data[6]*img[2] + (Ttdouble)_data[7]*img[3]);
res[2] = (Tt)((Ttdouble)_data[8]*img[0] + (Ttdouble)_data[9]*img[1] +
(Ttdouble)_data[10]*img[2] + (Ttdouble)_data[11]*img[3]);
res[3] = (Tt)((Ttdouble)_data[12]*img[0] + (Ttdouble)_data[13]*img[1] +
(Ttdouble)_data[14]*img[2] + (Ttdouble)_data[15]*img[3]);
return res;
}
} else if (_height==_width) {
if (img._height==img._width) switch (_width) { // Square_matrix * Square_matrix
case 2 : // 2x2_matrix * 2x2_matrix
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[2]);
res[1] = (Tt)((Ttdouble)_data[0]*img[1] + (Ttdouble)_data[1]*img[3]);
res[2] = (Tt)((Ttdouble)_data[2]*img[0] + (Ttdouble)_data[3]*img[2]);
res[3] = (Tt)((Ttdouble)_data[2]*img[1] + (Ttdouble)_data[3]*img[3]);
return res;
case 3 : // 3x3_matrix * 3x3_matrix
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[3] +
(Ttdouble)_data[2]*img[6]);
res[1] = (Tt)((Ttdouble)_data[0]*img[1] + (Ttdouble)_data[1]*img[4] +
(Ttdouble)_data[2]*img[7]);
res[2] = (Tt)((Ttdouble)_data[0]*img[2] + (Ttdouble)_data[1]*img[5] +
(Ttdouble)_data[2]*img[8]);
res[3] = (Tt)((Ttdouble)_data[3]*img[0] + (Ttdouble)_data[4]*img[3] +
(Ttdouble)_data[5]*img[6]);
res[4] = (Tt)((Ttdouble)_data[3]*img[1] + (Ttdouble)_data[4]*img[4] +
(Ttdouble)_data[5]*img[7]);
res[5] = (Tt)((Ttdouble)_data[3]*img[2] + (Ttdouble)_data[4]*img[5] +
(Ttdouble)_data[5]*img[8]);
res[6] = (Tt)((Ttdouble)_data[6]*img[0] + (Ttdouble)_data[7]*img[3] +
(Ttdouble)_data[8]*img[6]);
res[7] = (Tt)((Ttdouble)_data[6]*img[1] + (Ttdouble)_data[7]*img[4] +
(Ttdouble)_data[8]*img[7]);
res[8] = (Tt)((Ttdouble)_data[6]*img[2] + (Ttdouble)_data[7]*img[5] +
(Ttdouble)_data[8]*img[8]);
return res;
case 4 : // 4x4_matrix * 4x4_matrix
res[0] = (Tt)((Ttdouble)_data[0]*img[0] + (Ttdouble)_data[1]*img[4] +
(Ttdouble)_data[2]*img[8] + (Ttdouble)_data[3]*img[12]);
res[1] = (Tt)((Ttdouble)_data[0]*img[1] + (Ttdouble)_data[1]*img[5] +
(Ttdouble)_data[2]*img[9] + (Ttdouble)_data[3]*img[13]);
res[2] = (Tt)((Ttdouble)_data[0]*img[2] + (Ttdouble)_data[1]*img[6] +
(Ttdouble)_data[2]*img[10] + (Ttdouble)_data[3]*img[14]);
res[3] = (Tt)((Ttdouble)_data[0]*img[3] + (Ttdouble)_data[1]*img[7] +
(Ttdouble)_data[2]*img[11] + (Ttdouble)_data[3]*img[15]);
res[4] = (Tt)((Ttdouble)_data[4]*img[0] + (Ttdouble)_data[5]*img[4] +
(Ttdouble)_data[6]*img[8] + (Ttdouble)_data[7]*img[12]);
res[5] = (Tt)((Ttdouble)_data[4]*img[1] + (Ttdouble)_data[5]*img[5] +
(Ttdouble)_data[6]*img[9] + (Ttdouble)_data[7]*img[13]);
res[6] = (Tt)((Ttdouble)_data[4]*img[2] + (Ttdouble)_data[5]*img[6] +
(Ttdouble)_data[6]*img[10] + (Ttdouble)_data[7]*img[14]);
res[7] = (Tt)((Ttdouble)_data[4]*img[3] + (Ttdouble)_data[5]*img[7] +
(Ttdouble)_data[6]*img[11] + (Ttdouble)_data[7]*img[15]);
res[8] = (Tt)((Ttdouble)_data[8]*img[0] + (Ttdouble)_data[9]*img[4] +
(Ttdouble)_data[10]*img[8] + (Ttdouble)_data[11]*img[12]);
res[9] = (Tt)((Ttdouble)_data[8]*img[1] + (Ttdouble)_data[9]*img[5] +
(Ttdouble)_data[10]*img[9] + (Ttdouble)_data[11]*img[13]);
res[10] = (Tt)((Ttdouble)_data[8]*img[2] + (Ttdouble)_data[9]*img[6] +
(Ttdouble)_data[10]*img[10] + (Ttdouble)_data[11]*img[14]);
res[11] = (Tt)((Ttdouble)_data[8]*img[3] + (Ttdouble)_data[9]*img[7] +
(Ttdouble)_data[10]*img[11] + (Ttdouble)_data[11]*img[15]);
res[12] = (Tt)((Ttdouble)_data[12]*img[0] + (Ttdouble)_data[13]*img[4] +
(Ttdouble)_data[14]*img[8] + (Ttdouble)_data[15]*img[12]);
res[13] = (Tt)((Ttdouble)_data[12]*img[1] + (Ttdouble)_data[13]*img[5] +
(Ttdouble)_data[14]*img[9] + (Ttdouble)_data[15]*img[13]);
res[14] = (Tt)((Ttdouble)_data[12]*img[2] + (Ttdouble)_data[13]*img[6] +
(Ttdouble)_data[14]*img[10] + (Ttdouble)_data[15]*img[14]);
res[15] = (Tt)((Ttdouble)_data[12]*img[3] + (Ttdouble)_data[13]*img[7] +
(Ttdouble)_data[14]*img[11] + (Ttdouble)_data[15]*img[15]);
return res;
} else switch (_width) { // Square_matrix * Matrix
case 2 : { // 2x2_matrix * Matrix
const t *ps0 = img.data(), *ps1 = img.data(0,1);
Tt *pd0 = res.data(), *pd1 = res.data(0,1);
const Ttdouble
a0 = (Ttdouble)_data[0], a1 = (Ttdouble)_data[1],
a2 = (Ttdouble)_data[2], a3 = (Ttdouble)_data[3];
cimg_forX(img,i) {
const Ttdouble x = (Ttdouble)*(ps0++), y = (Ttdouble)*(ps1++);
*(pd0++) = (Tt)(a0*x + a1*y);
*(pd1++) = (Tt)(a2*x + a3*y);
}
return res;
}
case 3 : { // 3x3_matrix * Matrix
const t *ps0 = img.data(), *ps1 = img.data(0,1), *ps2 = img.data(0,2);
Tt *pd0 = res.data(), *pd1 = res.data(0,1), *pd2 = res.data(0,2);
const Ttdouble
a0 = (Ttdouble)_data[0], a1 = (Ttdouble)_data[1], a2 = (Ttdouble)_data[2],
a3 = (Ttdouble)_data[3], a4 = (Ttdouble)_data[4], a5 = (Ttdouble)_data[5],
a6 = (Ttdouble)_data[6], a7 = (Ttdouble)_data[7], a8 = (Ttdouble)_data[8];
cimg_forX(img,i) {
const Ttdouble x = (Ttdouble)*(ps0++), y = (Ttdouble)*(ps1++), z = (Ttdouble)*(ps2++);
*(pd0++) = (Tt)(a0*x + a1*y + a2*z);
*(pd1++) = (Tt)(a3*x + a4*y + a5*z);
*(pd2++) = (Tt)(a6*x + a7*y + a8*z);
}
return res;
}
case 4 : { // 4x4_matrix * Matrix
const t *ps0 = img.data(), *ps1 = img.data(0,1), *ps2 = img.data(0,2), *ps3 = img.data(0,3);
Tt *pd0 = res.data(), *pd1 = res.data(0,1), *pd2 = res.data(0,2), *pd3 = res.data(0,3);
const Ttdouble
a0 = (Ttdouble)_data[0], a1 = (Ttdouble)_data[1], a2 = (Ttdouble)_data[2], a3 = (Ttdouble)_data[3],
a4 = (Ttdouble)_data[4], a5 = (Ttdouble)_data[5], a6 = (Ttdouble)_data[6], a7 = (Ttdouble)_data[7],
a8 = (Ttdouble)_data[8], a9 = (Ttdouble)_data[9], a10 = (Ttdouble)_data[10], a11 = (Ttdouble)_data[11],
a12 = (Ttdouble)_data[12], a13 = (Ttdouble)_data[13], a14 = (Ttdouble)_data[14],
a15 = (Ttdouble)_data[15];
cimg_forX(img,col) {
const Ttdouble x = (Ttdouble)*(ps0++), y = (Ttdouble)*(ps1++), z = (Ttdouble)*(ps2++),
c = (Ttdouble)*(ps3++);
*(pd0++) = (Tt)(a0*x + a1*y + a2*z + a3*c);
*(pd1++) = (Tt)(a4*x + a5*y + a6*z + a7*c);
*(pd2++) = (Tt)(a8*x + a9*y + a10*z + a11*c);
*(pd3++) = (Tt)(a12*x + a13*y + a14*z + a15*c);
}
return res;
}
}
}

// Fallback to generic version.
#if cimg_use_openmp!=0
cimg_pragma_openmp(parallel for cimg_openmp_collapse(2)
cimg_openmp_if(size()>(cimg_openmp_sizefactor)*1024 &&
img.size()>(cimg_openmp_sizefactor)*1024))
cimg_forXY(res,i,j) {
Ttdouble value = 0; cimg_forX(*this,k) value+=(*this)(k,j)*img(i,k); res(i,j) = (Tt)value;
}
#else
Tt *ptrd = res._data;
cimg_forXY(res,i,j) {
Ttdouble value = 0; cimg_forX(*this,k) value+=(*this)(k,j)*img(i,k); *(ptrd++) = (Tt)value;
}
#endif
return res;
}

//! In-place division operator.
/**
       Similar to operator+=(const t), except that it performs a division instead of an addition.
     **/
template<typename t>
CImg<T>& operator/=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,*ptr / value,32768);
return *this;
}

//! In-place division operator.
/**
       Similar to operator+=(const char*), except that it performs a division instead of an addition.
     **/
CImg<T>& operator/=(const char *const expression) {
return div((+*this)._fill(expression,true,1,0,0,"operator/=",this));
}

//! In-place division operator.
/**
       Replace the image instance by the (right) matrix division between the image instance and the specified
       matrix \c img.
       \param img Second operand of the matrix division.
       \note
       - It does \e not compute a pointwise division between two images. For this purpose, use
         div(const CImg<t>&) instead.
       - It returns the matrix operation \c A*inverse(img).
       - The size of the image instance can be modified by this operator.
     **/
template<typename t>
CImg<T>& operator/=(const CImg<t>& img) {
return (*this*img.get_invert()).move_to(*this);
}

//! Division operator.
/**
       Similar to operator/=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator/(const t value) const {
return CImg<_cimg_Tt>(*this,false)/=value;
}

//! Division operator.
/**
       Similar to operator/=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
CImg<Tfloat> operator/(const char *const expression) const {
return CImg<Tfloat>(*this,false)/=expression;
}

//! Division operator.
/**
       Similar to operator/=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator/(const CImg<t>& img) const {
return (*this)*img.get_invert();
}

//! In-place modulo operator.
/**
       Similar to operator+=(const t), except that it performs a modulo operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator%=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,cimg::mod(*ptr,(T)value),16384);
return *this;
}

//! In-place modulo operator.
/**
       Similar to operator+=(const char*), except that it performs a modulo operation instead of an addition.
    **/
CImg<T>& operator%=(const char *const expression) {
return *this%=(+*this)._fill(expression,true,1,0,0,"operator%=",this);
}

//! In-place modulo operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a modulo operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator%=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this%=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = cimg::mod(*ptrd,(T)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = cimg::mod(*ptrd,(T)*(ptrs++));
}
return *this;
}

//! Modulo operator.
/**
       Similar to operator%=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator%(const t value) const {
return CImg<_cimg_Tt>(*this,false)%=value;
}

//! Modulo operator.
/**
       Similar to operator%=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
CImg<Tfloat> operator%(const char *const expression) const {
return CImg<Tfloat>(*this,false)%=expression;
}

//! Modulo operator.
/**
       Similar to operator%=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
template<typename t>
CImg<_cimg_Tt> operator%(const CImg<t>& img) const {
return CImg<_cimg_Tt>(*this,false)%=img;
}

//! In-place bitwise AND operator.
/**
       Similar to operator+=(const t), except that it performs a bitwise AND operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator&=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,(ulongT)*ptr & (ulongT)value,32768);
return *this;
}

//! In-place bitwise AND operator.
/**
       Similar to operator+=(const char*), except that it performs a bitwise AND operation instead of an addition.
    **/
CImg<T>& operator&=(const char *const expression) {
return *this&=(+*this)._fill(expression,true,1,0,0,"operator&=",this);
}

//! In-place bitwise AND operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise AND operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator&=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this&=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)((ulongT)*ptrd & (ulongT)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd & (ulongT)*(ptrs++));
}
return *this;
}

//! Bitwise AND operator.
/**
       Similar to operator&=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator&(const t value) const {
return (+*this)&=value;
}

//! Bitwise AND operator.
/**
       Similar to operator&=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
CImg<T> operator&(const char *const expression) const {
return (+*this)&=expression;
}

//! Bitwise AND operator.
/**
       Similar to operator&=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator&(const CImg<t>& img) const {
return (+*this)&=img;
}

//! In-place bitwise OR operator.
/**
       Similar to operator+=(const t), except that it performs a bitwise OR operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator|=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,(ulongT)*ptr | (ulongT)value,32768);
return *this;
}

//! In-place bitwise OR operator.
/**
       Similar to operator+=(const char*), except that it performs a bitwise OR operation instead of an addition.
    **/
CImg<T>& operator|=(const char *const expression) {
return *this|=(+*this)._fill(expression,true,1,0,0,"operator|=",this);
}

//! In-place bitwise OR operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise OR operation instead of an addition.
    **/
template<typename t>
CImg<T>& operator|=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this|=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)((ulongT)*ptrd | (ulongT)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd | (ulongT)*(ptrs++));
}
return *this;
}

//! Bitwise OR operator.
/**
       Similar to operator|=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator|(const t value) const {
return (+*this)|=value;
}

//! Bitwise OR operator.
/**
       Similar to operator|=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
CImg<T> operator|(const char *const expression) const {
return (+*this)|=expression;
}

//! Bitwise OR operator.
/**
       Similar to operator|=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator|(const CImg<t>& img) const {
return (+*this)|=img;
}

//! In-place bitwise XOR operator.
/**
       Similar to operator+=(const t), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const t) instead.
    **/
template<typename t>
CImg<T>& operator^=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,(ulongT)*ptr ^ (ulongT)value,32768);
return *this;
}

//! In-place bitwise XOR operator.
/**
       Similar to operator+=(const char*), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const char*) instead.
    **/
CImg<T>& operator^=(const char *const expression) {
return *this^=(+*this)._fill(expression,true,1,0,0,"operator^=",this);
}

//! In-place bitwise XOR operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const CImg<t>&) instead.
    **/
template<typename t>
CImg<T>& operator^=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this^=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)((ulongT)*ptrd ^ (ulongT)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd ^ (ulongT)*(ptrs++));
}
return *this;
}

//! Bitwise XOR operator.
/**
       Similar to operator^=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator^(const t value) const {
return (+*this)^=value;
}

//! Bitwise XOR operator.
/**
       Similar to operator^=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
CImg<T> operator^(const char *const expression) const {
return (+*this)^=expression;
}

//! Bitwise XOR operator.
/**
       Similar to operator^=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator^(const CImg<t>& img) const {
return (+*this)^=img;
}

//! In-place bitwise left shift operator.
/**
       Similar to operator+=(const t), except that it performs a bitwise left shift instead of an addition.
    **/
template<typename t>
CImg<T>& operator<<=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,((longT)*ptr) << (int)value,65536);
return *this;
}

//! In-place bitwise left shift operator.
/**
       Similar to operator+=(const char*), except that it performs a bitwise left shift instead of an addition.
    **/
CImg<T>& operator<<=(const char *const expression) {
return *this<<=(+*this)._fill(expression,true,1,0,0,"operator<<=",this);
}

//! In-place bitwise left shift operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise left shift instead of an addition.
    **/
template<typename t>
CImg<T>& operator<<=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this^=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)((longT)*ptrd << (int)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((longT)*ptrd << (int)*(ptrs++));
}
return *this;
}

//! Bitwise left shift operator.
/**
       Similar to operator<<=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator<<(const t value) const {
return (+*this)<<=value;
}

//! Bitwise left shift operator.
/**
       Similar to operator<<=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
CImg<T> operator<<(const char *const expression) const {
return (+*this)<<=expression;
}

//! Bitwise left shift operator.
/**
       Similar to operator<<=(const CImg<t>&), except that it returns a new image instance instead of
       operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator<<(const CImg<t>& img) const {
return (+*this)<<=img;
}

//! In-place bitwise right shift operator.
/**
       Similar to operator+=(const t), except that it performs a bitwise right shift instead of an addition.
    **/
template<typename t>
CImg<T>& operator>>=(const t value) {
if (is_empty()) return *this;
cimg_openmp_for(*this,((longT)*ptr) >> (int)value,65536);
return *this;
}

//! In-place bitwise right shift operator.
/**
       Similar to operator+=(const char*), except that it performs a bitwise right shift instead of an addition.
    **/
CImg<T>& operator>>=(const char *const expression) {
return *this>>=(+*this)._fill(expression,true,1,0,0,"operator>>=",this);
}

//! In-place bitwise right shift operator.
/**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise right shift instead of an addition.
    **/
template<typename t>
CImg<T>& operator>>=(const CImg<t>& img) {
const ulongT siz = size(), isiz = img.size();
if (siz && isiz) {
if (is_overlapped(img)) return *this^=+img;
T *ptrd = _data, *const ptre = _data + siz;
if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
*ptrd = (T)((longT)*ptrd >> (int)*(ptrs++));
for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((longT)*ptrd >> (int)*(ptrs++));
}
return *this;
}

//! Bitwise right shift operator.
/**
       Similar to operator>>=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator>>(const t value) const {
return (+*this)>>=value;
}

//! Bitwise right shift operator.
/**
       Similar to operator>>=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
CImg<T> operator>>(const char *const expression) const {
return (+*this)>>=expression;
}

//! Bitwise right shift operator.
/**
       Similar to operator>>=(const CImg<t>&), except that it returns a new image instance instead of
       operating in-place.
       The pixel type of the returned image is \c T.
    **/
template<typename t>
CImg<T> operator>>(const CImg<t>& img) const {
return (+*this)>>=img;
}

//! Bitwise inversion operator.
/**
       Similar to operator-(), except that it compute the bitwise inverse instead of the opposite value.
    **/
CImg<T> operator~() const {
CImg<T> res(_width,_height,_depth,_spectrum);
const T *ptrs = _data;
cimg_for(res,ptrd,T) { const ulongT value = (ulongT)*(ptrs++); *ptrd = (T)~value; }
return res;
}

//! Test if all pixels of an image have the same value.
/**
       Return \c true is all pixels of the image instance are equal to the specified \c value.
       \param value Reference value to compare with.
    **/
template<typename t>
bool operator==(const t value) const {
if (is_empty()) return false;
typedef _cimg_Tt Tt;
bool is_equal = true;
for (T *ptrd = _data + size(); is_equal && ptrd>_data; is_equal = ((Tt)*(--ptrd)==(Tt)value)) {}
return is_equal;
}

//! Test if all pixel values of an image follow a specified expression.
/**
       Return \c true is all pixels of the image instance are equal to the specified \c expression.
       \param expression Value string describing the way pixel values are compared.
    **/
bool operator==(const char *const expression) const {
return *this==(+*this)._fill(expression,true,1,0,0,"operator==",this);
}

//! Test if two images have the same size and values.
/**
       Return \c true if the image instance and the input image \c img have the same dimensions and pixel values,
       and \c false otherwise.
       \param img Input image to compare with.
       \note
       - The pixel buffer pointers data() of the two compared images do not have to be the same for operator==()
         to return \c true.
         Only the dimensions and the pixel values matter. Thus, the comparison can be \c true even for different
         pixel types \c T and \c t.
       \par Example
       \code
       const CImg<float> img1(1,3,1,1, 0,1,2); // Construct a 1x3 vector [0;1;2] (with 'float' pixel values)
       const CImg<char> img2(1,3,1,1, 0,1,2);  // Construct a 1x3 vector [0;1;2] (with 'char' pixel values)
       if (img1==img2) {                       // Test succeeds, image dimensions and values are the same
         std::printf("'img1' and 'img2' have same dimensions and values.");
       }
       \endcode
    **/
template<typename t>
bool operator==(const CImg<t>& img) const {
typedef _cimg_Tt Tt;
const ulongT siz = size();
bool is_equal = true;
if (siz!=img.size()) return false;
t *ptrs = img._data + siz;
for (T *ptrd = _data + siz; is_equal && ptrd>_data; is_equal = ((Tt)*(--ptrd)==(Tt)*(--ptrs))) {}
return is_equal;
}

//! Test if pixels of an image are all different from a value.
/**
       Return \c true is all pixels of the image instance are different than the specified \c value.
       \param value Reference value to compare with.
    **/
template<typename t>
bool operator!=(const t value) const {
return !((*this)==value);
}

//! Test if all pixel values of an image are different from a specified expression.
/**
       Return \c true is all pixels of the image instance are different to the specified \c expression.
       \param expression Value string describing the way pixel values are compared.
    **/
bool operator!=(const char *const expression) const {
return !((*this)==expression);
}

//! Test if two images have different sizes or values.
/**
       Return \c true if the image instance and the input image \c img have different dimensions or pixel values,
       and \c false otherwise.
       \param img Input image to compare with.
       \note
       - Writing \c img1!=img2 is equivalent to \c !(img1==img2).
    **/
template<typename t>
bool operator!=(const CImg<t>& img) const {
return !((*this)==img);
}

//! Construct an image list from two images.
/**
       Return a new list of image (\c CImgList instance) containing exactly two elements:
         - A copy of the image instance, at position [\c 0].
         - A copy of the specified image \c img, at position [\c 1].

       \param img Input image that will be the second image of the resulting list.
       \note
       - The family of operator,() is convenient to easily create list of images, but it is also \e quite \e slow
         in practice (see warning below).
       - Constructed lists contain no shared images. If image instance or input image \c img are shared, they are
         inserted as new non-shared copies in the resulting list.
       - The pixel type of the returned list may be a superset of the initial pixel type \c T, if necessary.
       \warning
       - Pipelining operator,() \c N times will perform \c N copies of the entire content of a (growing) image list.
         This may become very expensive in terms of speed and used memory. You should avoid using this technique to
         build a new CImgList instance from several images, if you are seeking for performance.
         Fast insertions of images in an image list are possible with
         CImgList<T>::insert(const CImg<t>&,unsigned int,bool) or move_to(CImgList<t>&,unsigned int).
       \par Example
       \code
       const CImg<float>
          img1("reference.jpg"),
          img2 = img1.get_mirror('x'),
          img3 = img2.get_blur(5);
       const CImgList<float> list = (img1,img2); // Create list of two elements from 'img1' and 'img2'
       (list,img3).display();                    // Display image list containing copies of 'img1','img2' and 'img3'
       \endcode
       \image html ref_operator_comma.jpg
    **/
template<typename t>
CImgList<_cimg_Tt> operator,(const CImg<t>& img) const {
return CImgList<_cimg_Tt>(*this,img);
}

//! Construct an image list from image instance and an input image list.
/**
       Return a new list of images (\c CImgList instance) containing exactly \c list.size() \c + \c 1 elements:
         - A copy of the image instance, at position [\c 0].
         - A copy of the specified image list \c list, from positions [\c 1] to [\c list.size()].

       \param list Input image list that will be appended to the image instance.
       \note
       - Similar to operator,(const CImg<t>&) const, except that it takes an image list as an argument.
    **/
template<typename t>
CImgList<_cimg_Tt> operator,(const CImgList<t>& list) const {
return CImgList<_cimg_Tt>(list,false).insert(*this,0);
}

//! Split image along specified axis.
/**
       Return a new list of images (\c CImgList instance) containing the splitted components
       of the instance image along the specified axis.
       \param axis Splitting axis (can be '\c x','\c y','\c z' or '\c c')
       \note
       - Similar to get_split(char,int) const, with default second argument.
       \par Example
       \code
       const CImg<unsigned char> img("reference.jpg"); // Load a RGB color image
       const CImgList<unsigned char> list = (img<'c'); // Get a list of its three R,G,B channels
       (img,list).display();
       \endcode
       \image html ref_operator_less.jpg
    **/
CImgList<T> operator<(const char axis) const {
return get_split(axis);
}

//@}
//-------------------------------------
//
//! \name Instance Characteristics
//@{
//-------------------------------------

//! Return the type of image pixel values as a C string.
/**
       Return a \c char* string containing the usual type name of the image pixel values
       (i.e. a stringified version of the template parameter \c T).
       \note
       - The returned string may contain spaces (as in \c "unsigned char").
       - If the pixel type \c T does not correspond to a registered type, the string <tt>"unknown"</tt> is returned.
    **/
static const char* pixel_type() {
return cimg::type<T>::string();
}

//! Return the number of image columns.
/**
       Return the image width, i.e. the image dimension along the X-axis.
       \note
       - The width() of an empty image is equal to \c 0.
       - width() is typically equal to \c 1 when considering images as \e vectors for matrix calculations.
       - width() returns an \c int, although the image width is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._width</tt>.
    **/
int width() const {
return (int)_width;
}

//! Return the number of image rows.
/**
       Return the image height, i.e. the image dimension along the Y-axis.
       \note
       - The height() of an empty image is equal to \c 0.
       - height() returns an \c int, although the image height is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._height</tt>.
    **/
int height() const {
return (int)_height;
}

//! Return the number of image slices.
/**
       Return the image depth, i.e. the image dimension along the Z-axis.
       \note
       - The depth() of an empty image is equal to \c 0.
       - depth() is typically equal to \c 1 when considering usual 2D images. When depth()\c > \c 1, the image
         is said to be \e volumetric.
       - depth() returns an \c int, although the image depth is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._depth</tt>.
    **/
int depth() const {
return (int)_depth;
}

//! Return the number of image channels.
/**
       Return the number of image channels, i.e. the image dimension along the C-axis.
       \note
       - The spectrum() of an empty image is equal to \c 0.
       - spectrum() is typically equal to \c 1 when considering scalar-valued images, to \c 3
         for RGB-coded color images, and to \c 4 for RGBA-coded color images (with alpha-channel).
         The number of channels of an image instance is not limited. The meaning of the pixel values is not linked
         up to the number of channels (e.g. a 4-channel image may indifferently stands for a RGBA or CMYK color image).
       - spectrum() returns an \c int, although the image spectrum is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._spectrum</tt>.
    **/
int spectrum() const {
return (int)_spectrum;
}

//! Return the total number of pixel values.
/**
       Return <tt>width()*\ref height()*\ref depth()*\ref spectrum()</tt>,
       i.e. the total number of values of type \c T in the pixel buffer of the image instance.
       \note
       - The size() of an empty image is equal to \c 0.
       - The allocated memory size for a pixel buffer of a non-shared \c CImg<T> instance is equal to
         <tt>size()*sizeof(T)</tt>.
       \par Example
       \code
       const CImg<float> img(100,100,1,3);               // Construct new 100x100 color image
       if (img.size()==30000)                            // Test succeeds
         std::printf("Pixel buffer uses %lu bytes",
                     img.size()*sizeof(float));
       \endcode
    **/
ulongT size() const {
return (ulongT)_width*_height*_depth*_spectrum;
}

//! Return a pointer to the first pixel value.
/**
       Return a \c T*, or a \c const \c T* pointer to the first value in the pixel buffer of the image instance,
       whether the instance is \c const or not.
       \note
       - The data() of an empty image is equal to \c 0 (null pointer).
       - The allocated pixel buffer for the image instance starts from \c data()
         and goes to <tt>data()+\ref size() - 1</tt> (included).
       - To get the pointer to one particular location of the pixel buffer, use
         data(unsigned int,unsigned int,unsigned int,unsigned int) instead.
    **/
T* data() {
return _data;
}

//! Return a pointer to the first pixel value \const.
const T* data() const {
return _data;
}

//! Return a pointer to a located pixel value.
/**
       Return a \c T*, or a \c const \c T* pointer to the value located at (\c x,\c y,\c z,\c c) in the pixel buffer
       of the image instance,
       whether the instance is \c const or not.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Writing \c img.data(x,y,z,c) is equivalent to <tt>&(img(x,y,z,c))</tt>. Thus, this method has the same
         properties as operator()(unsigned int,unsigned int,unsigned int,unsigned int).
     **/
#if cimg_verbosity>=3
T *data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) {
const ulongT off = (ulongT)offset(x,y,z,c);
if (off>=size())
cimg::warn(_cimg_instance
"data(): Invalid pointer request, at coordinates (%u,%u,%u,%u) [offset=%u].",
cimg_instance,
x,y,z,c,off);
return _data + off;
}

//! Return a pointer to a located pixel value \const.
const T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) const {
return const_cast<CImg<T>*>(this)->data(x,y,z,c);
}
#else
T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) {
return _data + x + (ulongT)y*_width + (ulongT)z*_width*_height + (ulongT)c*_width*_height*_depth;
}

const T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) const {
return _data + x + (ulongT)y*_width + (ulongT)z*_width*_height + (ulongT)c*_width*_height*_depth;
}
#endif

//! Return the offset to a located pixel value, with respect to the beginning of the pixel buffer.
/**
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Writing \c img.data(x,y,z,c) is equivalent to <tt>&(img(x,y,z,c)) - img.data()</tt>.
         Thus, this method has the same properties as operator()(unsigned int,unsigned int,unsigned int,unsigned int).
       \par Example
       \code
       const CImg<float> img(100,100,1,3);      // Define a 100x100 RGB-color image
       const long off = img.offset(10,10,0,2);  // Get the offset of the blue value of the pixel located at (10,10)
       const float val = img[off];              // Get the blue value of this pixel
       \endcode
    **/
longT offset(const int x, const int y=0, const int z=0, const int c=0) const {
return x + (longT)y*_width + (longT)z*_width*_height + (longT)c*_width*_height*_depth;
}

//! Return a CImg<T>::iterator pointing to the first pixel value.
/**
       \note
       - Equivalent to data().
       - It has been mainly defined for compatibility with STL naming conventions.
     **/
iterator begin() {
return _data;
}

//! Return a CImg<T>::iterator pointing to the first value of the pixel buffer \const.
const_iterator begin() const {
return _data;
}

//! Return a CImg<T>::iterator pointing next to the last pixel value.
/**
       \note
       - Writing \c img.end() is equivalent to <tt>img.data() + img.size()</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
       \warning
       - The returned iterator actually points to a value located \e outside the acceptable bounds of the pixel buffer.
         Trying to read or write the content of the returned iterator will probably result in a crash.
         Use it mainly as a strict upper bound for a CImg<T>::iterator.
       \par Example
       \code
       CImg<float> img(100,100,1,3); // Define a 100x100 RGB color image
       // 'img.end()' used below as an upper bound for the iterator.
       for (CImg<float>::iterator it = img.begin(); it<img.end(); ++it)
         *it = 0;
       \endcode
    **/
iterator end() {
return _data + size();
}

//! Return a CImg<T>::iterator pointing next to the last pixel value \const.
const_iterator end() const {
return _data + size();
}

//! Return a reference to the first pixel value.
/**
       \note
       - Writing \c img.front() is equivalent to <tt>img[0]</tt>, or <tt>img(0,0,0,0)</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
    **/
T& front() {
return *_data;
}

//! Return a reference to the first pixel value \const.
const T& front() const {
return *_data;
}

//! Return a reference to the last pixel value.
/**
       \note
       - Writing \c img.back() is equivalent to <tt>img[img.size() - 1]</tt>, or
         <tt>img(img.width() - 1,img.height() - 1,img.depth() - 1,img.spectrum() - 1)</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
    **/
T& back() {
return *(_data + size() - 1);
}

//! Return a reference to the last pixel value \const.
const T& back() const {
return *(_data + size() - 1);
}

//! Access to a pixel value at a specified offset, using Dirichlet boundary conditions.
/**
       Return a reference to the pixel value of the image instance located at a specified \c offset,
       or to a specified default value in case of out-of-bounds access.
       \param offset Offset to the desired pixel value.
       \param out_value Default value returned if \c offset is outside image bounds.
       \note
       - Writing \c img.at(offset,out_value) is similar to <tt>img[offset]</tt>, except that if \c offset
         is outside bounds (e.g. \c offset<0 or \c offset>=img.size()), a reference to a value \c out_value
         is safely returned instead.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel offset.
    **/
T& at(const int offset, const T& out_value) {
return (offset<0 || offset>=(int)size())?(cimg::temporary(out_value)=out_value):(*this)[offset];
}

//! Access to a pixel value at a specified offset, using Dirichlet boundary conditions \const.
T at(const int offset, const T& out_value) const {
return (offset<0 || offset>=(int)size())?out_value:(*this)[offset];
}

//! Access to a pixel value at a specified offset, using Neumann boundary conditions.
/**
       Return a reference to the pixel value of the image instance located at a specified \c offset,
       or to the nearest pixel location in the image instance in case of out-of-bounds access.
       \param offset Offset to the desired pixel value.
       \note
       - Similar to at(int,const T), except that an out-of-bounds access returns the value of the
         nearest pixel in the image instance, regarding the specified offset, i.e.
         - If \c offset<0, then \c img[0] is returned.
         - If \c offset>=img.size(), then \c img[img.size() - 1] is returned.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel offset.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method \c _at(int).
     **/
T& at(const int offset) {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"at(): Empty instance.",
cimg_instance);
return _at(offset);
}

T& _at(const int offset) {
const unsigned int siz = (unsigned int)size();
return (*this)[offset<0?0:(unsigned int)offset>=siz?siz - 1:offset];
}

//! Access to a pixel value at a specified offset, using Neumann boundary conditions \const.
const T& at(const int offset) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"at(): Empty instance.",
cimg_instance);
return _at(offset);
}

const T& _at(const int offset) const {
const unsigned int siz = (unsigned int)size();
return (*this)[offset<0?0:(unsigned int)offset>=siz?siz - 1:offset];
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X-coordinate.
/**
       Return a reference to the pixel value of the image instance located at (\c x,\c y,\c z,\c c),
       or to a specified default value in case of out-of-bounds access along the X-axis.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c x,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to operator()(), except that an out-of-bounds access along the X-axis returns the specified value
         \c out_value.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel coordinates.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
T& atX(const int x, const int y, const int z, const int c, const T& out_value) {
return (x<0 || x>=width())?(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X-coordinate \const.
T atX(const int x, const int y, const int z, const int c, const T& out_value) const {
return (x<0 || x>=width())?out_value:(*this)(x,y,z,c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X-coordinate.
/**
       Return a reference to the pixel value of the image instance located at (\c x,\c y,\c z,\c c),
       or to the nearest pixel location in the image instance in case of out-of-bounds access along the X-axis.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to at(int,int,int,int,const T), except that an out-of-bounds access returns the value of the
         nearest pixel in the image instance, regarding the specified X-coordinate.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel coordinates.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _at(int,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
     **/
T& atX(const int x, const int y=0, const int z=0, const int c=0) {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atX(): Empty instance.",
cimg_instance);
return _atX(x,y,z,c);
}

T& _atX(const int x, const int y=0, const int z=0, const int c=0) {
return (*this)(x<0?0:(x>=width()?width() - 1:x),y,z,c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X-coordinate \const.
const T& atX(const int x, const int y=0, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atX(): Empty instance.",
cimg_instance);
return _atX(x,y,z,c);
}

const T& _atX(const int x, const int y=0, const int z=0, const int c=0) const {
return (*this)(x<0?0:(x>=width()?width() - 1:x),y,z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X and Y-coordinates.
/**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed both on X and Y-coordinates.
    **/
T& atXY(const int x, const int y, const int z, const int c, const T& out_value) {
return (x<0 || y<0 || x>=width() || y>=height())?(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X and Y coordinates \const.
T atXY(const int x, const int y, const int z, const int c, const T& out_value) const {
return (x<0 || y<0 || x>=width() || y>=height())?out_value:(*this)(x,y,z,c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X and Y-coordinates.
/**
       Similar to atX(int,int,int,int), except that boundary checking is performed both on X and Y-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXY(int,int,int,int).
     **/
T& atXY(const int x, const int y, const int z=0, const int c=0) {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXY(): Empty instance.",
cimg_instance);
return _atXY(x,y,z,c);
}

T& _atXY(const int x, const int y, const int z=0, const int c=0) {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),z,c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X and Y-coordinates \const.
const T& atXY(const int x, const int y, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXY(): Empty instance.",
cimg_instance);
return _atXY(x,y,z,c);
}

const T& _atXY(const int x, const int y, const int z=0, const int c=0) const {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed both on
       X,Y and Z-coordinates.
    **/
T& atXYZ(const int x, const int y, const int z, const int c, const T& out_value) {
return (x<0 || y<0 || z<0 || x>=width() || y>=height() || z>=depth())?
(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions for the X,Y and Z-coordinates \const.
T atXYZ(const int x, const int y, const int z, const int c, const T& out_value) const {
return (x<0 || y<0 || z<0 || x>=width() || y>=height() || z>=depth())?out_value:(*this)(x,y,z,c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to atX(int,int,int,int), except that boundary checking is performed both on X,Y and Z-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXYZ(int,int,int,int).
    **/
T& atXYZ(const int x, const int y, const int z, const int c=0) {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXYZ(): Empty instance.",
cimg_instance);
return _atXYZ(x,y,z,c);
}

T& _atXYZ(const int x, const int y, const int z, const int c=0) {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),
cimg::cut(z,0,depth() - 1),c);
}

//! Access to a pixel value, using Neumann boundary conditions for the X,Y and Z-coordinates \const.
const T& atXYZ(const int x, const int y, const int z, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXYZ(): Empty instance.",
cimg_instance);
return _atXYZ(x,y,z,c);
}

const T& _atXYZ(const int x, const int y, const int z, const int c=0) const {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),
cimg::cut(z,0,depth() - 1),c);
}

//! Access to a pixel value, using Dirichlet boundary conditions.
/**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed on all
       X,Y,Z and C-coordinates.
    **/
T& atXYZC(const int x, const int y, const int z, const int c, const T& out_value) {
return (x<0 || y<0 || z<0 || c<0 || x>=width() || y>=height() || z>=depth() || c>=spectrum())?
(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
}

//! Access to a pixel value, using Dirichlet boundary conditions \const.
T atXYZC(const int x, const int y, const int z, const int c, const T& out_value) const {
return (x<0 || y<0 || z<0 || c<0 || x>=width() || y>=height() || z>=depth() || c>=spectrum())?out_value:
(*this)(x,y,z,c);
}

//! Access to a pixel value, using Neumann boundary conditions.
/**
       Similar to atX(int,int,int,int), except that boundary checking is performed on all X,Y,Z and C-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXYZC(int,int,int,int).
    **/
T& atXYZC(const int x, const int y, const int z, const int c) {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXYZC(): Empty instance.",
cimg_instance);
return _atXYZC(x,y,z,c);
}

T& _atXYZC(const int x, const int y, const int z, const int c) {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),
cimg::cut(z,0,depth() - 1),
cimg::cut(c,0,spectrum() - 1));
}

//! Access to a pixel value, using Neumann boundary conditions \const.
const T& atXYZC(const int x, const int y, const int z, const int c) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"atXYZC(): Empty instance.",
cimg_instance);
return _atXYZC(x,y,z,c);
}

const T& _atXYZC(const int x, const int y, const int z, const int c) const {
return (*this)(cimg::cut(x,0,width() - 1),
cimg::cut(y,0,height() - 1),
cimg::cut(z,0,depth() - 1),
cimg::cut(c,0,spectrum() - 1));
}

//! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X-coordinate.
/**
       Return a linearly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or a specified default value in case of out-of-bounds access along the X-axis.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c fx,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to atX(int,int,int,int,const T), except that the returned pixel value is approximated by
         a linear interpolation along the X-axis, if corresponding coordinates are not integers.
       - The type of the returned pixel value is extended to \c float, if the pixel type \c T is not float-valued.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
Tfloat linear_atX(const float fx, const int y, const int z, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1;
const float
dx = fx - x;
const Tfloat
Ic = (Tfloat)atX(x,y,z,c,out_value), In = (Tfloat)atXY(nx,y,z,c,out_value);
return Ic + dx*(In - Ic);
}

//! Return pixel value, using linear interpolation and Neumann boundary conditions for the X-coordinate.
/**
       Return a linearly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or the value of the nearest pixel location in the image instance in case of out-of-bounds access along
       the X-axis.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to linear_atX(float,int,int,int,const T) const, except that an out-of-bounds access returns
         the value of the nearest pixel in the image instance, regarding the specified X-coordinate.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atX(float,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
Tfloat linear_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"linear_atX(): Empty instance.",
cimg_instance);

return _linear_atX(fx,y,z,c);
}

Tfloat _linear_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
const float
nfx = cimg::cut(fx,0,width() - 1);
const unsigned int
x = (unsigned int)nfx;
const float
dx = nfx - x;
const unsigned int
nx = dx>0?x + 1:x;
const Tfloat
Ic = (Tfloat)(*this)(x,y,z,c), In = (Tfloat)(*this)(nx,y,z,c);
return Ic + dx*(In - Ic);
}

//! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X and Y-coordinates.
/**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved both for X and Y-coordinates.
    **/
Tfloat linear_atXY(const float fx, const float fy, const int z, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1,
y = (int)fy - (fy>=0?0:1), ny = y + 1;
const float
dx = fx - x,
dy = fy - y;
const Tfloat
Icc = (Tfloat)atXY(x,y,z,c,out_value),  Inc = (Tfloat)atXY(nx,y,z,c,out_value),
Icn = (Tfloat)atXY(x,ny,z,c,out_value), Inn = (Tfloat)atXY(nx,ny,z,c,out_value);
return Icc + dx*(Inc - Icc + dy*(Icc + Inn - Icn - Inc)) + dy*(Icn - Icc);
}

//! Return pixel value, using linear interpolation and Neumann boundary conditions for the X and Y-coordinates.
/**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved both for X and Y-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXY(float,float,int,int).
    **/
Tfloat linear_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"linear_atXY(): Empty instance.",
cimg_instance);

return _linear_atXY(fx,fy,z,c);
}

Tfloat _linear_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
const float
nfx = cimg::cut(fx,0,width() - 1),
nfy = cimg::cut(fy,0,height() - 1);
const unsigned int
x = (unsigned int)nfx,
y = (unsigned int)nfy;
const float
dx = nfx - x,
dy = nfy - y;
const unsigned int
nx = dx>0?x + 1:x,
ny = dy>0?y + 1:y;
const Tfloat
Icc = (Tfloat)(*this)(x,y,z,c),  Inc = (Tfloat)(*this)(nx,y,z,c),
Icn = (Tfloat)(*this)(x,ny,z,c), Inn = (Tfloat)(*this)(nx,ny,z,c);
return Icc + dx*(Inc - Icc + dy*(Icc + Inn - Icn - Inc)) + dy*(Icn - Icc);
}

//! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved both for X,Y and Z-coordinates.
    **/
Tfloat linear_atXYZ(const float fx, const float fy, const float fz, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1,
y = (int)fy - (fy>=0?0:1), ny = y + 1,
z = (int)fz - (fz>=0?0:1), nz = z + 1;
const float
dx = fx - x,
dy = fy - y,
dz = fz - z;
const Tfloat
Iccc = (Tfloat)atXYZ(x,y,z,c,out_value), Incc = (Tfloat)atXYZ(nx,y,z,c,out_value),
Icnc = (Tfloat)atXYZ(x,ny,z,c,out_value), Innc = (Tfloat)atXYZ(nx,ny,z,c,out_value),
Iccn = (Tfloat)atXYZ(x,y,nz,c,out_value), Incn = (Tfloat)atXYZ(nx,y,nz,c,out_value),
Icnn = (Tfloat)atXYZ(x,ny,nz,c,out_value), Innn = (Tfloat)atXYZ(nx,ny,nz,c,out_value);
return Iccc +
dx*(Incc - Iccc +
dy*(Iccc + Innc - Icnc - Incc +
dz*(Iccn + Innn + Icnc + Incc - Icnn - Incn - Iccc - Innc)) +
dz*(Iccc + Incn - Iccn - Incc)) +
dy*(Icnc - Iccc +
dz*(Iccc + Icnn - Iccn - Icnc)) +
dz*(Iccn - Iccc);
}

//! Return pixel value, using linear interpolation and Neumann boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved both for X,Y and Z-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXYZ(float,float,float,int).
    **/
Tfloat linear_atXYZ(const float fx, const float fy=0, const float fz=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"linear_atXYZ(): Empty instance.",
cimg_instance);

return _linear_atXYZ(fx,fy,fz,c);
}

Tfloat _linear_atXYZ(const float fx, const float fy=0, const float fz=0, const int c=0) const {
const float
nfx = cimg::cut(fx,0,width() - 1),
nfy = cimg::cut(fy,0,height() - 1),
nfz = cimg::cut(fz,0,depth() - 1);
const unsigned int
x = (unsigned int)nfx,
y = (unsigned int)nfy,
z = (unsigned int)nfz;
const float
dx = nfx - x,
dy = nfy - y,
dz = nfz - z;
const unsigned int
nx = dx>0?x + 1:x,
ny = dy>0?y + 1:y,
nz = dz>0?z + 1:z;
const Tfloat
Iccc = (Tfloat)(*this)(x,y,z,c), Incc = (Tfloat)(*this)(nx,y,z,c),
Icnc = (Tfloat)(*this)(x,ny,z,c), Innc = (Tfloat)(*this)(nx,ny,z,c),
Iccn = (Tfloat)(*this)(x,y,nz,c), Incn = (Tfloat)(*this)(nx,y,nz,c),
Icnn = (Tfloat)(*this)(x,ny,nz,c), Innn = (Tfloat)(*this)(nx,ny,nz,c);
return Iccc +
dx*(Incc - Iccc +
dy*(Iccc + Innc - Icnc - Incc +
dz*(Iccn + Innn + Icnc + Incc - Icnn - Incn - Iccc - Innc)) +
dz*(Iccc + Incn - Iccn - Incc)) +
dy*(Icnc - Iccc +
dz*(Iccc + Icnn - Iccn - Icnc)) +
dz*(Iccn - Iccc);
}

//! Return pixel value, using linear interpolation and Dirichlet boundary conditions for all X,Y,Z,C-coordinates.
/**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved for all X,Y,Z and C-coordinates.
    **/
Tfloat linear_atXYZC(const float fx, const float fy, const float fz, const float fc, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1,
y = (int)fy - (fy>=0?0:1), ny = y + 1,
z = (int)fz - (fz>=0?0:1), nz = z + 1,
c = (int)fc - (fc>=0?0:1), nc = c + 1;
const float
dx = fx - x,
dy = fy - y,
dz = fz - z,
dc = fc - c;
const Tfloat
Icccc = (Tfloat)atXYZC(x,y,z,c,out_value), Inccc = (Tfloat)atXYZC(nx,y,z,c,out_value),
Icncc = (Tfloat)atXYZC(x,ny,z,c,out_value), Inncc = (Tfloat)atXYZC(nx,ny,z,c,out_value),
Iccnc = (Tfloat)atXYZC(x,y,nz,c,out_value), Incnc = (Tfloat)atXYZC(nx,y,nz,c,out_value),
Icnnc = (Tfloat)atXYZC(x,ny,nz,c,out_value), Innnc = (Tfloat)atXYZC(nx,ny,nz,c,out_value),
Icccn = (Tfloat)atXYZC(x,y,z,nc,out_value), Inccn = (Tfloat)atXYZC(nx,y,z,nc,out_value),
Icncn = (Tfloat)atXYZC(x,ny,z,nc,out_value), Inncn = (Tfloat)atXYZC(nx,ny,z,nc,out_value),
Iccnn = (Tfloat)atXYZC(x,y,nz,nc,out_value), Incnn = (Tfloat)atXYZC(nx,y,nz,nc,out_value),
Icnnn = (Tfloat)atXYZC(x,ny,nz,nc,out_value), Innnn = (Tfloat)atXYZC(nx,ny,nz,nc,out_value);
return Icccc +
dx*(Inccc - Icccc +
dy*(Icccc + Inncc - Icncc - Inccc +
dz*(Iccnc + Innnc + Icncc + Inccc - Icnnc - Incnc - Icccc - Inncc +
dc*(Iccnn + Innnn + Icncn + Inccn + Icnnc + Incnc + Icccc + Inncc -
Icnnn - Incnn - Icccn - Inncn - Iccnc - Innnc - Icncc - Inccc)) +
dc*(Icccn + Inncn + Icncc + Inccc - Icncn - Inccn - Icccc - Inncc)) +
dz*(Icccc + Incnc - Iccnc - Inccc +
dc*(Icccn + Incnn + Iccnc + Inccc - Iccnn - Inccn - Icccc - Incnc)) +
dc*(Icccc + Inccn - Inccc - Icccn)) +
dy*(Icncc - Icccc +
dz*(Icccc + Icnnc - Iccnc - Icncc +
dc*(Icccn + Icnnn + Iccnc + Icncc - Iccnn - Icncn - Icccc - Icnnc)) +
dc*(Icccc + Icncn - Icncc - Icccn)) +
dz*(Iccnc - Icccc +
dc*(Icccc + Iccnn - Iccnc - Icccn)) +
dc*(Icccn  -Icccc);
}

//! Return pixel value, using linear interpolation and Neumann boundary conditions for all X,Y,Z and C-coordinates.
/**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved for all X,Y,Z and C-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXYZC(float,float,float,float).
    **/
Tfloat linear_atXYZC(const float fx, const float fy=0, const float fz=0, const float fc=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"linear_atXYZC(): Empty instance.",
cimg_instance);

return _linear_atXYZC(fx,fy,fz,fc);
}

Tfloat _linear_atXYZC(const float fx, const float fy=0, const float fz=0, const float fc=0) const {
const float
nfx = cimg::cut(fx,0,width() - 1),
nfy = cimg::cut(fy,0,height() - 1),
nfz = cimg::cut(fz,0,depth() - 1),
nfc = cimg::cut(fc,0,spectrum() - 1);
const unsigned int
x = (unsigned int)nfx,
y = (unsigned int)nfy,
z = (unsigned int)nfz,
c = (unsigned int)nfc;
const float
dx = nfx - x,
dy = nfy - y,
dz = nfz - z,
dc = nfc - c;
const unsigned int
nx = dx>0?x + 1:x,
ny = dy>0?y + 1:y,
nz = dz>0?z + 1:z,
nc = dc>0?c + 1:c;
const Tfloat
Icccc = (Tfloat)(*this)(x,y,z,c), Inccc = (Tfloat)(*this)(nx,y,z,c),
Icncc = (Tfloat)(*this)(x,ny,z,c), Inncc = (Tfloat)(*this)(nx,ny,z,c),
Iccnc = (Tfloat)(*this)(x,y,nz,c), Incnc = (Tfloat)(*this)(nx,y,nz,c),
Icnnc = (Tfloat)(*this)(x,ny,nz,c), Innnc = (Tfloat)(*this)(nx,ny,nz,c),
Icccn = (Tfloat)(*this)(x,y,z,nc), Inccn = (Tfloat)(*this)(nx,y,z,nc),
Icncn = (Tfloat)(*this)(x,ny,z,nc), Inncn = (Tfloat)(*this)(nx,ny,z,nc),
Iccnn = (Tfloat)(*this)(x,y,nz,nc), Incnn = (Tfloat)(*this)(nx,y,nz,nc),
Icnnn = (Tfloat)(*this)(x,ny,nz,nc), Innnn = (Tfloat)(*this)(nx,ny,nz,nc);
return Icccc +
dx*(Inccc - Icccc +
dy*(Icccc + Inncc - Icncc - Inccc +
dz*(Iccnc + Innnc + Icncc + Inccc - Icnnc - Incnc - Icccc - Inncc +
dc*(Iccnn + Innnn + Icncn + Inccn + Icnnc + Incnc + Icccc + Inncc -
Icnnn - Incnn - Icccn - Inncn - Iccnc - Innnc - Icncc - Inccc)) +
dc*(Icccn + Inncn + Icncc + Inccc - Icncn - Inccn - Icccc - Inncc)) +
dz*(Icccc + Incnc - Iccnc - Inccc +
dc*(Icccn + Incnn + Iccnc + Inccc - Iccnn - Inccn - Icccc - Incnc)) +
dc*(Icccc + Inccn - Inccc - Icccn)) +
dy*(Icncc - Icccc +
dz*(Icccc + Icnnc - Iccnc - Icncc +
dc*(Icccn + Icnnn + Iccnc + Icncc - Iccnn - Icncn - Icccc - Icnnc)) +
dc*(Icccc + Icncn - Icncc - Icccn)) +
dz*(Iccnc - Icccc +
dc*(Icccc + Iccnn - Iccnc - Icccn)) +
dc*(Icccn - Icccc);
}

//! Return pixel value, using cubic interpolation and Dirichlet boundary conditions for the X-coordinate.
/**
       Return a cubicly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or a specified default value in case of out-of-bounds access along the X-axis.
       The cubic interpolation uses Hermite splines.
       \param fx d X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c fx,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to linear_atX(float,int,int,int,const T) const, except that the returned pixel value is
         approximated by a \e cubic interpolation along the X-axis.
       - The type of the returned pixel value is extended to \c float, if the pixel type \c T is not float-valued.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
Tfloat cubic_atX(const float fx, const int y, const int z, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), px = x - 1, nx = x + 1, ax = x + 2;
const float
dx = fx - x;
const Tfloat
Ip = (Tfloat)atX(px,y,z,c,out_value), Ic = (Tfloat)atX(x,y,z,c,out_value),
In = (Tfloat)atX(nx,y,z,c,out_value), Ia = (Tfloat)atX(ax,y,z,c,out_value);
return Ic + 0.5f*(dx*(-Ip + In) + dx*dx*(2*Ip - 5*Ic + 4*In - Ia) + dx*dx*dx*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Dirichlet boundary conditions for the X-coordinate.
/**
       Similar to cubic_atX(float,int,int,int,const T) const, except that the return value is clamped to stay in the
       min/max range of the datatype \c T.
    **/
T cubic_cut_atX(const float fx, const int y, const int z, const int c, const T& out_value) const {
return cimg::type<T>::cut(cubic_atX(fx,y,z,c,out_value));
}

//! Return pixel value, using cubic interpolation and Neumann boundary conditions for the X-coordinate.
/**
       Return a cubicly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or the value of the nearest pixel location in the image instance in case of out-of-bounds access
       along the X-axis. The cubic interpolation uses Hermite splines.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to cubic_atX(float,int,int,int,const T) const, except that the returned pixel value is
         approximated by a cubic interpolation along the X-axis.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _cubic_atX(float,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
Tfloat cubic_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"cubic_atX(): Empty instance.",
cimg_instance);
return _cubic_atX(fx,y,z,c);
}

Tfloat _cubic_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
const float
nfx = cimg::type<float>::is_nan(fx)?0:cimg::cut(fx,0,width() - 1);
const int
x = (int)nfx;
const float
dx = nfx - x;
const int
px = x - 1<0?0:x - 1, nx = dx>0?x + 1:x, ax = x + 2>=width()?width() - 1:x + 2;
const Tfloat
Ip = (Tfloat)(*this)(px,y,z,c), Ic = (Tfloat)(*this)(x,y,z,c),
In = (Tfloat)(*this)(nx,y,z,c), Ia = (Tfloat)(*this)(ax,y,z,c);
return Ic + 0.5f*(dx*(-Ip + In) + dx*dx*(2*Ip - 5*Ic + 4*In - Ia) + dx*dx*dx*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Neumann boundary conditions for the X-coordinate.
/**
       Similar to cubic_atX(float,int,int,int) const, except that the return value is clamped to stay in the
       min/max range of the datatype \c T.
    **/
T cubic_cut_atX(const float fx, const int y, const int z, const int c) const {
return cimg::type<T>::cut(cubic_atX(fx,y,z,c));
}

T _cubic_cut_atX(const float fx, const int y, const int z, const int c) const {
return cimg::type<T>::cut(_cubic_atX(fx,y,z,c));
}

//! Return pixel value, using cubic interpolation and Dirichlet boundary conditions for the X and Y-coordinates.
/**
       Similar to cubic_atX(float,int,int,int,const T) const, except that the cubic interpolation and boundary checking
       are achieved both for X and Y-coordinates.
    **/
Tfloat cubic_atXY(const float fx, const float fy, const int z, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), px = x - 1, nx = x + 1, ax = x + 2,
y = (int)fy - (fy>=0?0:1), py = y - 1, ny = y + 1, ay = y + 2;
const float dx = fx - x, dy = fy - y;
const Tfloat
Ipp = (Tfloat)atXY(px,py,z,c,out_value), Icp = (Tfloat)atXY(x,py,z,c,out_value),
Inp = (Tfloat)atXY(nx,py,z,c,out_value), Iap = (Tfloat)atXY(ax,py,z,c,out_value),
Ip = Icp + 0.5f*(dx*(-Ipp + Inp) + dx*dx*(2*Ipp - 5*Icp + 4*Inp - Iap) + dx*dx*dx*(-Ipp + 3*Icp - 3*Inp + Iap)),
Ipc = (Tfloat)atXY(px,y,z,c,out_value),  Icc = (Tfloat)atXY(x, y,z,c,out_value),
Inc = (Tfloat)atXY(nx,y,z,c,out_value),  Iac = (Tfloat)atXY(ax,y,z,c,out_value),
Ic = Icc + 0.5f*(dx*(-Ipc + Inc) + dx*dx*(2*Ipc - 5*Icc + 4*Inc - Iac) + dx*dx*dx*(-Ipc + 3*Icc - 3*Inc + Iac)),
Ipn = (Tfloat)atXY(px,ny,z,c,out_value), Icn = (Tfloat)atXY(x,ny,z,c,out_value),
Inn = (Tfloat)atXY(nx,ny,z,c,out_value), Ian = (Tfloat)atXY(ax,ny,z,c,out_value),
In = Icn + 0.5f*(dx*(-Ipn + Inn) + dx*dx*(2*Ipn - 5*Icn + 4*Inn - Ian) + dx*dx*dx*(-Ipn + 3*Icn - 3*Inn + Ian)),
Ipa = (Tfloat)atXY(px,ay,z,c,out_value), Ica = (Tfloat)atXY(x,ay,z,c,out_value),
Ina = (Tfloat)atXY(nx,ay,z,c,out_value), Iaa = (Tfloat)atXY(ax,ay,z,c,out_value),
Ia = Ica + 0.5f*(dx*(-Ipa + Ina) + dx*dx*(2*Ipa - 5*Ica + 4*Ina - Iaa) + dx*dx*dx*(-Ipa + 3*Ica - 3*Ina + Iaa));
return Ic + 0.5f*(dy*(-Ip + In) + dy*dy*(2*Ip - 5*Ic + 4*In - Ia) + dy*dy*dy*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Dirichlet boundary conditions for the X,Y-coordinates.
/**
       Similar to cubic_atXY(float,float,int,int,const T) const, except that the return value is clamped to stay in the
       min/max range of the datatype \c T.
    **/
T cubic_cut_atXY(const float fx, const float fy, const int z, const int c, const T& out_value) const {
return cimg::type<T>::cut(cubic_atXY(fx,fy,z,c,out_value));
}

//! Return pixel value, using cubic interpolation and Neumann boundary conditions for the X and Y-coordinates.
/**
       Similar to cubic_atX(float,int,int,int) const, except that the cubic interpolation and boundary checking
       are achieved for both X and Y-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
       \c _cubic_atXY(float,float,int,int).
    **/
Tfloat cubic_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"cubic_atXY(): Empty instance.",
cimg_instance);
return _cubic_atXY(fx,fy,z,c);
}

Tfloat _cubic_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
const float
nfx = cimg::type<float>::is_nan(fx)?0:cimg::cut(fx,0,width() - 1),
nfy = cimg::type<float>::is_nan(fy)?0:cimg::cut(fy,0,height() - 1);
const int x = (int)nfx, y = (int)nfy;
const float dx = nfx - x, dy = nfy - y;
const int
px = x - 1<0?0:x - 1, nx = dx<=0?x:x + 1, ax = x + 2>=width()?width() - 1:x + 2,
py = y - 1<0?0:y - 1, ny = dy<=0?y:y + 1, ay = y + 2>=height()?height() - 1:y + 2;
const Tfloat
Ipp = (Tfloat)(*this)(px,py,z,c), Icp = (Tfloat)(*this)(x,py,z,c), Inp = (Tfloat)(*this)(nx,py,z,c),
Iap = (Tfloat)(*this)(ax,py,z,c),
Ip = Icp + 0.5f*(dx*(-Ipp + Inp) + dx*dx*(2*Ipp - 5*Icp + 4*Inp - Iap) + dx*dx*dx*(-Ipp + 3*Icp - 3*Inp + Iap)),
Ipc = (Tfloat)(*this)(px,y,z,c),  Icc = (Tfloat)(*this)(x, y,z,c), Inc = (Tfloat)(*this)(nx,y,z,c),
Iac = (Tfloat)(*this)(ax,y,z,c),
Ic = Icc + 0.5f*(dx*(-Ipc + Inc) + dx*dx*(2*Ipc - 5*Icc + 4*Inc - Iac) + dx*dx*dx*(-Ipc + 3*Icc - 3*Inc + Iac)),
Ipn = (Tfloat)(*this)(px,ny,z,c), Icn = (Tfloat)(*this)(x,ny,z,c), Inn = (Tfloat)(*this)(nx,ny,z,c),
Ian = (Tfloat)(*this)(ax,ny,z,c),
In = Icn + 0.5f*(dx*(-Ipn + Inn) + dx*dx*(2*Ipn - 5*Icn + 4*Inn - Ian) + dx*dx*dx*(-Ipn + 3*Icn - 3*Inn + Ian)),
Ipa = (Tfloat)(*this)(px,ay,z,c), Ica = (Tfloat)(*this)(x,ay,z,c), Ina = (Tfloat)(*this)(nx,ay,z,c),
Iaa = (Tfloat)(*this)(ax,ay,z,c),
Ia = Ica + 0.5f*(dx*(-Ipa + Ina) + dx*dx*(2*Ipa - 5*Ica + 4*Ina - Iaa) + dx*dx*dx*(-Ipa + 3*Ica - 3*Ina + Iaa));
return Ic + 0.5f*(dy*(-Ip + In) + dy*dy*(2*Ip - 5*Ic + 4*In - Ia) + dy*dy*dy*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Neumann boundary conditions for the X,Y-coordinates.
/**
       Similar to cubic_atXY(float,float,int,int) const, except that the return value is clamped to stay in the
       min/max range of the datatype \c T.
    **/
T cubic_cut_atXY(const float fx, const float fy, const int z, const int c) const {
return cimg::type<T>::cut(cubic_atXY(fx,fy,z,c));
}

T _cubic_cut_atXY(const float fx, const float fy, const int z, const int c) const {
return cimg::type<T>::cut(_cubic_atXY(fx,fy,z,c));
}

//! Return pixel value, using cubic interpolation and Dirichlet boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to cubic_atX(float,int,int,int,const T) const, except that the cubic interpolation and boundary checking
       are achieved both for X,Y and Z-coordinates.
    **/
Tfloat cubic_atXYZ(const float fx, const float fy, const float fz, const int c, const T& out_value) const {
const int
x = (int)fx - (fx>=0?0:1), px = x - 1, nx = x + 1, ax = x + 2,
y = (int)fy - (fy>=0?0:1), py = y - 1, ny = y + 1, ay = y + 2,
z = (int)fz - (fz>=0?0:1), pz = z - 1, nz = z + 1, az = z + 2;
const float dx = fx - x, dy = fy - y, dz = fz - z;
const Tfloat
Ippp = (Tfloat)atXYZ(px,py,pz,c,out_value), Icpp = (Tfloat)atXYZ(x,py,pz,c,out_value),
Inpp = (Tfloat)atXYZ(nx,py,pz,c,out_value), Iapp = (Tfloat)atXYZ(ax,py,pz,c,out_value),
Ipp = Icpp + 0.5f*(dx*(-Ippp + Inpp) + dx*dx*(2*Ippp - 5*Icpp + 4*Inpp - Iapp) +
dx*dx*dx*(-Ippp + 3*Icpp - 3*Inpp + Iapp)),
Ipcp = (Tfloat)atXYZ(px,y,pz,c,out_value),  Iccp = (Tfloat)atXYZ(x, y,pz,c,out_value),
Incp = (Tfloat)atXYZ(nx,y,pz,c,out_value),  Iacp = (Tfloat)atXYZ(ax,y,pz,c,out_value),
Icp = Iccp + 0.5f*(dx*(-Ipcp + Incp) + dx*dx*(2*Ipcp - 5*Iccp + 4*Incp - Iacp) +
dx*dx*dx*(-Ipcp + 3*Iccp - 3*Incp + Iacp)),
Ipnp = (Tfloat)atXYZ(px,ny,pz,c,out_value), Icnp = (Tfloat)atXYZ(x,ny,pz,c,out_value),
Innp = (Tfloat)atXYZ(nx,ny,pz,c,out_value), Ianp = (Tfloat)atXYZ(ax,ny,pz,c,out_value),
Inp = Icnp + 0.5f*(dx*(-Ipnp + Innp) + dx*dx*(2*Ipnp - 5*Icnp + 4*Innp - Ianp) +
dx*dx*dx*(-Ipnp + 3*Icnp - 3*Innp + Ianp)),
Ipap = (Tfloat)atXYZ(px,ay,pz,c,out_value), Icap = (Tfloat)atXYZ(x,ay,pz,c,out_value),
Inap = (Tfloat)atXYZ(nx,ay,pz,c,out_value), Iaap = (Tfloat)atXYZ(ax,ay,pz,c,out_value),
Iap = Icap + 0.5f*(dx*(-Ipap + Inap) + dx*dx*(2*Ipap - 5*Icap + 4*Inap - Iaap) +
dx*dx*dx*(-Ipap + 3*Icap - 3*Inap + Iaap)),
Ip = Icp + 0.5f*(dy*(-Ipp + Inp) + dy*dy*(2*Ipp - 5*Icp + 4*Inp - Iap) +
dy*dy*dy*(-Ipp + 3*Icp - 3*Inp + Iap)),
Ippc = (Tfloat)atXYZ(px,py,z,c,out_value), Icpc = (Tfloat)atXYZ(x,py,z,c,out_value),
Inpc = (Tfloat)atXYZ(nx,py,z,c,out_value), Iapc = (Tfloat)atXYZ(ax,py,z,c,out_value),
Ipc = Icpc + 0.5f*(dx*(-Ippc + Inpc) + dx*dx*(2*Ippc - 5*Icpc + 4*Inpc - Iapc) +
dx*dx*dx*(-Ippc + 3*Icpc - 3*Inpc + Iapc)),
Ipcc = (Tfloat)atXYZ(px,y,z,c,out_value),  Iccc = (Tfloat)atXYZ(x, y,z,c,out_value),
Incc = (Tfloat)atXYZ(nx,y,z,c,out_value),  Iacc = (Tfloat)atXYZ(ax,y,z,c,out_value),
Icc = Iccc + 0.5f*(dx*(-Ipcc + Incc) + dx*dx*(2*Ipcc - 5*Iccc + 4*Incc - Iacc) +
dx*dx*dx*(-Ipcc + 3*Iccc - 3*Incc + Iacc)),
Ipnc = (Tfloat)atXYZ(px,ny,z,c,out_value), Icnc = (Tfloat)atXYZ(x,ny,z,c,out_value),
Innc = (Tfloat)atXYZ(nx,ny,z,c,out_value), Ianc = (Tfloat)atXYZ(ax,ny,z,c,out_value),
Inc = Icnc + 0.5f*(dx*(-Ipnc + Innc) + dx*dx*(2*Ipnc - 5*Icnc + 4*Innc - Ianc) +
dx*dx*dx*(-Ipnc + 3*Icnc - 3*Innc + Ianc)),
Ipac = (Tfloat)atXYZ(px,ay,z,c,out_value), Icac = (Tfloat)atXYZ(x,ay,z,c,out_value),
Inac = (Tfloat)atXYZ(nx,ay,z,c,out_value), Iaac = (Tfloat)atXYZ(ax,ay,z,c,out_value),
Iac = Icac + 0.5f*(dx*(-Ipac + Inac) + dx*dx*(2*Ipac - 5*Icac + 4*Inac - Iaac) +
dx*dx*dx*(-Ipac + 3*Icac - 3*Inac + Iaac)),
Ic = Icc + 0.5f*(dy*(-Ipc + Inc) + dy*dy*(2*Ipc - 5*Icc + 4*Inc - Iac) +
dy*dy*dy*(-Ipc + 3*Icc - 3*Inc + Iac)),
Ippn = (Tfloat)atXYZ(px,py,nz,c,out_value), Icpn = (Tfloat)atXYZ(x,py,nz,c,out_value),
Inpn = (Tfloat)atXYZ(nx,py,nz,c,out_value), Iapn = (Tfloat)atXYZ(ax,py,nz,c,out_value),
Ipn = Icpn + 0.5f*(dx*(-Ippn + Inpn) + dx*dx*(2*Ippn - 5*Icpn + 4*Inpn - Iapn) +
dx*dx*dx*(-Ippn + 3*Icpn - 3*Inpn + Iapn)),
Ipcn = (Tfloat)atXYZ(px,y,nz,c,out_value),  Iccn = (Tfloat)atXYZ(x, y,nz,c,out_value),
Incn = (Tfloat)atXYZ(nx,y,nz,c,out_value),  Iacn = (Tfloat)atXYZ(ax,y,nz,c,out_value),
Icn = Iccn + 0.5f*(dx*(-Ipcn + Incn) + dx*dx*(2*Ipcn - 5*Iccn + 4*Incn - Iacn) +
dx*dx*dx*(-Ipcn + 3*Iccn - 3*Incn + Iacn)),
Ipnn = (Tfloat)atXYZ(px,ny,nz,c,out_value), Icnn = (Tfloat)atXYZ(x,ny,nz,c,out_value),
Innn = (Tfloat)atXYZ(nx,ny,nz,c,out_value), Iann = (Tfloat)atXYZ(ax,ny,nz,c,out_value),
Inn = Icnn + 0.5f*(dx*(-Ipnn + Innn) + dx*dx*(2*Ipnn - 5*Icnn + 4*Innn - Iann) +
dx*dx*dx*(-Ipnn + 3*Icnn - 3*Innn + Iann)),
Ipan = (Tfloat)atXYZ(px,ay,nz,c,out_value), Ican = (Tfloat)atXYZ(x,ay,nz,c,out_value),
Inan = (Tfloat)atXYZ(nx,ay,nz,c,out_value), Iaan = (Tfloat)atXYZ(ax,ay,nz,c,out_value),
Ian = Ican + 0.5f*(dx*(-Ipan + Inan) + dx*dx*(2*Ipan - 5*Ican + 4*Inan - Iaan) +
dx*dx*dx*(-Ipan + 3*Ican - 3*Inan + Iaan)),
In = Icn + 0.5f*(dy*(-Ipn + Inn) + dy*dy*(2*Ipn - 5*Icn + 4*Inn - Ian) +
dy*dy*dy*(-Ipn + 3*Icn - 3*Inn + Ian)),
Ippa = (Tfloat)atXYZ(px,py,az,c,out_value), Icpa = (Tfloat)atXYZ(x,py,az,c,out_value),
Inpa = (Tfloat)atXYZ(nx,py,az,c,out_value), Iapa = (Tfloat)atXYZ(ax,py,az,c,out_value),
Ipa = Icpa + 0.5f*(dx*(-Ippa + Inpa) + dx*dx*(2*Ippa - 5*Icpa + 4*Inpa - Iapa) +
dx*dx*dx*(-Ippa + 3*Icpa - 3*Inpa + Iapa)),
Ipca = (Tfloat)atXYZ(px,y,az,c,out_value),  Icca = (Tfloat)atXYZ(x, y,az,c,out_value),
Inca = (Tfloat)atXYZ(nx,y,az,c,out_value),  Iaca = (Tfloat)atXYZ(ax,y,az,c,out_value),
Ica = Icca + 0.5f*(dx*(-Ipca + Inca) + dx*dx*(2*Ipca - 5*Icca + 4*Inca - Iaca) +
dx*dx*dx*(-Ipca + 3*Icca - 3*Inca + Iaca)),
Ipna = (Tfloat)atXYZ(px,ny,az,c,out_value), Icna = (Tfloat)atXYZ(x,ny,az,c,out_value),
Inna = (Tfloat)atXYZ(nx,ny,az,c,out_value), Iana = (Tfloat)atXYZ(ax,ny,az,c,out_value),
Ina = Icna + 0.5f*(dx*(-Ipna + Inna) + dx*dx*(2*Ipna - 5*Icna + 4*Inna - Iana) +
dx*dx*dx*(-Ipna + 3*Icna - 3*Inna + Iana)),
Ipaa = (Tfloat)atXYZ(px,ay,az,c,out_value), Icaa = (Tfloat)atXYZ(x,ay,az,c,out_value),
Inaa = (Tfloat)atXYZ(nx,ay,az,c,out_value), Iaaa = (Tfloat)atXYZ(ax,ay,az,c,out_value),
Iaa = Icaa + 0.5f*(dx*(-Ipaa + Inaa) + dx*dx*(2*Ipaa - 5*Icaa + 4*Inaa - Iaaa) +
dx*dx*dx*(-Ipaa + 3*Icaa - 3*Inaa + Iaaa)),
Ia = Ica + 0.5f*(dy*(-Ipa + Ina) + dy*dy*(2*Ipa - 5*Ica + 4*Ina - Iaa) +
dy*dy*dy*(-Ipa + 3*Ica - 3*Ina + Iaa));
return Ic + 0.5f*(dz*(-Ip + In) + dz*dz*(2*Ip - 5*Ic + 4*In - Ia) + dz*dz*dz*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Dirichlet boundary conditions for the XYZ-coordinates.
/**
       Similar to cubic_atXYZ(float,float,float,int,const T) const, except that the return value is clamped to stay
       in the min/max range of the datatype \c T.
    **/
T cubic_cut_atXYZ(const float fx, const float fy, const float fz, const int c, const T& out_value) const {
return cimg::type<T>::cut(cubic_atXYZ(fx,fy,fz,c,out_value));
}

//! Return pixel value, using cubic interpolation and Neumann boundary conditions for the X,Y and Z-coordinates.
/**
       Similar to cubic_atX(float,int,int,int) const, except that the cubic interpolation and boundary checking
       are achieved both for X,Y and Z-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _cubic_atXYZ(float,float,float,int).
    **/
Tfloat cubic_atXYZ(const float fx, const float fy, const float fz, const int c=0) const {
if (is_empty())
throw CImgInstanceException(_cimg_instance
"cubic_atXYZ(): Empty instance.",
cimg_instance);
return _cubic_atXYZ(fx,fy,fz,c);
}

Tfloat _cubic_atXYZ(const float fx, const float fy, const float fz, const int c=0) const {
const float
nfx = cimg::type<float>::is_nan(fx)?0:cimg::cut(fx,0,width() - 1),
nfy = cimg::type<float>::is_nan(fy)?0:cimg::cut(fy,0,height() - 1),
nfz = cimg::type<float>::is_nan(fz)?0:cimg::cut(fz,0,depth() - 1);
const int x = (int)nfx, y = (int)nfy, z = (int)nfz;
const float dx = nfx - x, dy = nfy - y, dz = nfz - z;
const int
px = x - 1<0?0:x - 1, nx = dx>0?x + 1:x, ax = x + 2>=width()?width() - 1:x + 2,
py = y - 1<0?0:y - 1, ny = dy>0?y + 1:y, ay = y + 2>=height()?height() - 1:y + 2,
pz = z - 1<0?0:z - 1, nz = dz>0?z + 1:z, az = z + 2>=depth()?depth() - 1:z + 2;
const Tfloat
Ippp = (Tfloat)(*this)(px,py,pz,c), Icpp = (Tfloat)(*this)(x,py,pz,c),
Inpp = (Tfloat)(*this)(nx,py,pz,c), Iapp = (Tfloat)(*this)(ax,py,pz,c),
Ipp = Icpp + 0.5f*(dx*(-Ippp + Inpp) + dx*dx*(2*Ippp - 5*Icpp + 4*Inpp - Iapp) +
dx*dx*dx*(-Ippp + 3*Icpp - 3*Inpp + Iapp)),
Ipcp = (Tfloat)(*this)(px,y,pz,c),  Iccp = (Tfloat)(*this)(x, y,pz,c),
Incp = (Tfloat)(*this)(nx,y,pz,c),  Iacp = (Tfloat)(*this)(ax,y,pz,c),
Icp = Iccp + 0.5f*(dx*(-Ipcp + Incp) + dx*dx*(2*Ipcp - 5*Iccp + 4*Incp - Iacp) +
dx*dx*dx*(-Ipcp + 3*Iccp - 3*Incp + Iacp)),
Ipnp = (Tfloat)(*this)(px,ny,pz,c), Icnp = (Tfloat)(*this)(x,ny,pz,c),
Innp = (Tfloat)(*this)(nx,ny,pz,c), Ianp = (Tfloat)(*this)(ax,ny,pz,c),
Inp = Icnp + 0.5f*(dx*(-Ipnp + Innp) + dx*dx*(2*Ipnp - 5*Icnp + 4*Innp - Ianp) +
dx*dx*dx*(-Ipnp + 3*Icnp - 3*Innp + Ianp)),
Ipap = (Tfloat)(*this)(px,ay,pz,c), Icap = (Tfloat)(*this)(x,ay,pz,c),
Inap = (Tfloat)(*this)(nx,ay,pz,c), Iaap = (Tfloat)(*this)(ax,ay,pz,c),
Iap = Icap + 0.5f*(dx*(-Ipap + Inap) + dx*dx*(2*Ipap - 5*Icap + 4*Inap - Iaap) +
dx*dx*dx*(-Ipap + 3*Icap - 3*Inap + Iaap)),
Ip = Icp + 0.5f*(dy*(-Ipp + Inp) + dy*dy*(2*Ipp - 5*Icp + 4*Inp - Iap) +
dy*dy*dy*(-Ipp + 3*Icp - 3*Inp + Iap)),
Ippc = (Tfloat)(*this)(px,py,z,c), Icpc = (Tfloat)(*this)(x,py,z,c),
Inpc = (Tfloat)(*this)(nx,py,z,c), Iapc = (Tfloat)(*this)(ax,py,z,c),
Ipc = Icpc + 0.5f*(dx*(-Ippc + Inpc) + dx*dx*(2*Ippc - 5*Icpc + 4*Inpc - Iapc) +
dx*dx*dx*(-Ippc + 3*Icpc - 3*Inpc + Iapc)),
Ipcc = (Tfloat)(*this)(px,y,z,c),  Iccc = (Tfloat)(*this)(x, y,z,c),
Incc = (Tfloat)(*this)(nx,y,z,c),  Iacc = (Tfloat)(*this)(ax,y,z,c),
Icc = Iccc + 0.5f*(dx*(-Ipcc + Incc) + dx*dx*(2*Ipcc - 5*Iccc + 4*Incc - Iacc) +
dx*dx*dx*(-Ipcc + 3*Iccc - 3*Incc + Iacc)),
Ipnc = (Tfloat)(*this)(px,ny,z,c), Icnc = (Tfloat)(*this)(x,ny,z,c),
Innc = (Tfloat)(*this)(nx,ny,z,c), Ianc = (Tfloat)(*this)(ax,ny,z,c),
Inc = Icnc + 0.5f*(dx*(-Ipnc + Innc) + dx*dx*(2*Ipnc - 5*Icnc + 4*Innc - Ianc) +
dx*dx*dx*(-Ipnc + 3*Icnc - 3*Innc + Ianc)),
Ipac = (Tfloat)(*this)(px,ay,z,c), Icac = (Tfloat)(*this)(x,ay,z,c),
Inac = (Tfloat)(*this)(nx,ay,z,c), Iaac = (Tfloat)(*this)(ax,ay,z,c),
Iac = Icac + 0.5f*(dx*(-Ipac + Inac) + dx*dx*(2*Ipac - 5*Icac + 4*Inac - Iaac) +
dx*dx*dx*(-Ipac + 3*Icac - 3*Inac + Iaac)),
Ic = Icc + 0.5f*(dy*(-Ipc + Inc) + dy*dy*(2*Ipc - 5*Icc + 4*Inc - Iac) +
dy*dy*dy*(-Ipc + 3*Icc - 3*Inc + Iac)),
Ippn = (Tfloat)(*this)(px,py,nz,c), Icpn = (Tfloat)(*this)(x,py,nz,c),
Inpn = (Tfloat)(*this)(nx,py,nz,c), Iapn = (Tfloat)(*this)(ax,py,nz,c),
Ipn = Icpn + 0.5f*(dx*(-Ippn + Inpn) + dx*dx*(2*Ippn - 5*Icpn + 4*Inpn - Iapn) +
dx*dx*dx*(-Ippn + 3*Icpn - 3*Inpn + Iapn)),
Ipcn = (Tfloat)(*this)(px,y,nz,c),  Iccn = (Tfloat)(*this)(x, y,nz,c),
Incn = (Tfloat)(*this)(nx,y,nz,c),  Iacn = (Tfloat)(*this)(ax,y,nz,c),
Icn = Iccn + 0.5f*(dx*(-Ipcn + Incn) + dx*dx*(2*Ipcn - 5*Iccn + 4*Incn - Iacn) +
dx*dx*dx*(-Ipcn + 3*Iccn - 3*Incn + Iacn)),
Ipnn = (Tfloat)(*this)(px,ny,nz,c), Icnn = (Tfloat)(*this)(x,ny,nz,c),
Innn = (Tfloat)(*this)(nx,ny,nz,c), Iann = (Tfloat)(*this)(ax,ny,nz,c),
Inn = Icnn + 0.5f*(dx*(-Ipnn + Innn) + dx*dx*(2*Ipnn - 5*Icnn + 4*Innn - Iann) +
dx*dx*dx*(-Ipnn + 3*Icnn - 3*Innn + Iann)),
Ipan = (Tfloat)(*this)(px,ay,nz,c), Ican = (Tfloat)(*this)(x,ay,nz,c),
Inan = (Tfloat)(*this)(nx,ay,nz,c), Iaan = (Tfloat)(*this)(ax,ay,nz,c),
Ian = Ican + 0.5f*(dx*(-Ipan + Inan) + dx*dx*(2*Ipan - 5*Ican + 4*Inan - Iaan) +
dx*dx*dx*(-Ipan + 3*Ican - 3*Inan + Iaan)),
In = Icn + 0.5f*(dy*(-Ipn + Inn) + dy*dy*(2*Ipn - 5*Icn + 4*Inn - Ian) +
dy*dy*dy*(-Ipn + 3*Icn - 3*Inn + Ian)),
Ippa = (Tfloat)(*this)(px,py,az,c), Icpa = (Tfloat)(*this)(x,py,az,c),
Inpa = (Tfloat)(*this)(nx,py,az,c), Iapa = (Tfloat)(*this)(ax,py,az,c),
Ipa = Icpa + 0.5f*(dx*(-Ippa + Inpa) + dx*dx*(2*Ippa - 5*Icpa + 4*Inpa - Iapa) +
dx*dx*dx*(-Ippa + 3*Icpa - 3*Inpa + Iapa)),
Ipca = (Tfloat)(*this)(px,y,az,c),  Icca = (Tfloat)(*this)(x, y,az,c),
Inca = (Tfloat)(*this)(nx,y,az,c),  Iaca = (Tfloat)(*this)(ax,y,az,c),
Ica = Icca + 0.5f*(dx*(-Ipca + Inca) + dx*dx*(2*Ipca - 5*Icca + 4*Inca - Iaca) +
dx*dx*dx*(-Ipca + 3*Icca - 3*Inca + Iaca)),
Ipna = (Tfloat)(*this)(px,ny,az,c), Icna = (Tfloat)(*this)(x,ny,az,c),
Inna = (Tfloat)(*this)(nx,ny,az,c), Iana = (Tfloat)(*this)(ax,ny,az,c),
Ina = Icna + 0.5f*(dx*(-Ipna + Inna) + dx*dx*(2*Ipna - 5*Icna + 4*Inna - Iana) +
dx*dx*dx*(-Ipna + 3*Icna - 3*Inna + Iana)),
Ipaa = (Tfloat)(*this)(px,ay,az,c), Icaa = (Tfloat)(*this)(x,ay,az,c),
Inaa = (Tfloat)(*this)(nx,ay,az,c), Iaaa = (Tfloat)(*this)(ax,ay,az,c),
Iaa = Icaa + 0.5f*(dx*(-Ipaa + Inaa) + dx*dx*(2*Ipaa - 5*Icaa + 4*Inaa - Iaaa) +
dx*dx*dx*(-Ipaa + 3*Icaa - 3*Inaa + Iaaa)),
Ia = Ica + 0.5f*(dy*(-Ipa + Ina) + dy*dy*(2*Ipa - 5*Ica + 4*Ina - Iaa) +
dy*dy*dy*(-Ipa + 3*Ica - 3*Ina + Iaa));
return Ic + 0.5f*(dz*(-Ip + In) + dz*dz*(2*Ip - 5*Ic + 4*In - Ia) + dz*dz*dz*(-Ip + 3*Ic - 3*In + Ia));
}

//! Return clamped pixel value, using cubic interpolation and Neumann boundary conditions for the XYZ-coordinates.
/**
       Similar to cubic_atXYZ(float,float,float,int) const, except that the return value is clamped to stay in the
       min/max range of the datatype \c T.
    **/
T cubic_cut_atXYZ(const float fx, const float fy, const float fz, const int c) const {
return cimg::type<T>::cut(cubic_atXYZ(fx,fy,fz,c));
}

T _cubic_cut_atXYZ(const float fx, const float fy, const float fz, const int c) const {
return cimg::type<T>::cut(_cubic_atXYZ(fx,fy,fz,c));
}

//! Set pixel value, using linear interpolation for the X-coordinates.
/**
       Set pixel value at specified coordinates (\c fx,\c y,\c z,\c c) in the image instance, in a way that
       the value is spread amongst several neighbors if the pixel coordinates are float-valued.
       \param value Pixel value to set.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param is_added Tells if the pixel value is added to (\c true), or simply replace (\c false) the current image
         pixel(s).
       \return A reference to the current image instance.
       \note
       - Calling this method with out-of-bounds coordinates does nothing.
    **/
CImg<T>& set_linear_atX(const T& value, const float fx, const int y=0, const int z=0, const int c=0,
const bool is_added=false) {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1;
const float
dx = fx - x;
if (y>=0 && y<height() && z>=0 && z<depth() && c>=0 && c<spectrum()) {
if (x>=0 && x<width()) {
const float w1 = 1 - dx, w2 = is_added?1:(1 - w1);
(*this)(x,y,z,c) = (T)(w1*value + w2*(*this)(x,y,z,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx, w2 = is_added?1:(1 - w1);
(*this)(nx,y,z,c) = (T)(w1*value + w2*(*this)(nx,y,z,c));
}
}
return *this;
}

//! Set pixel value, using linear interpolation for the X and Y-coordinates.
/**
       Similar to set_linear_atX(const T&,float,int,int,int,bool), except that the linear interpolation
       is achieved both for X and Y-coordinates.
    **/
CImg<T>& set_linear_atXY(const T& value, const float fx, const float fy=0, const int z=0, const int c=0,
const bool is_added=false) {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1,
y = (int)fy - (fy>=0?0:1), ny = y + 1;
const float
dx = fx - x,
dy = fy - y;
if (z>=0 && z<depth() && c>=0 && c<spectrum()) {
if (y>=0 && y<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*(1 - dy), w2 = is_added?1:(1 - w1);
(*this)(x,y,z,c) = (T)(w1*value + w2*(*this)(x,y,z,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*(1 - dy), w2 = is_added?1:(1 - w1);
(*this)(nx,y,z,c) = (T)(w1*value + w2*(*this)(nx,y,z,c));
}
}
if (ny>=0 && ny<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*dy, w2 = is_added?1:(1 - w1);
(*this)(x,ny,z,c) = (T)(w1*value + w2*(*this)(x,ny,z,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*dy, w2 = is_added?1:(1 - w1);
(*this)(nx,ny,z,c) = (T)(w1*value + w2*(*this)(nx,ny,z,c));
}
}
}
return *this;
}

//! Set pixel value, using linear interpolation for the X,Y and Z-coordinates.
/**
       Similar to set_linear_atXY(const T&,float,float,int,int,bool), except that the linear interpolation
       is achieved both for X,Y and Z-coordinates.
    **/
CImg<T>& set_linear_atXYZ(const T& value, const float fx, const float fy=0, const float fz=0, const int c=0,
const bool is_added=false) {
const int
x = (int)fx - (fx>=0?0:1), nx = x + 1,
y = (int)fy - (fy>=0?0:1), ny = y + 1,
z = (int)fz - (fz>=0?0:1), nz = z + 1;
const float
dx = fx - x,
dy = fy - y,
dz = fz - z;
if (c>=0 && c<spectrum()) {
if (z>=0 && z<depth()) {
if (y>=0 && y<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*(1 - dy)*(1 - dz), w2 = is_added?1:(1 - w1);
(*this)(x,y,z,c) = (T)(w1*value + w2*(*this)(x,y,z,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*(1 - dy)*(1 - dz), w2 = is_added?1:(1 - w1);
(*this)(nx,y,z,c) = (T)(w1*value + w2*(*this)(nx,y,z,c));
}
}
if (ny>=0 && ny<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*dy*(1 - dz), w2 = is_added?1:(1 - w1);
(*this)(x,ny,z,c) = (T)(w1*value + w2*(*this)(x,ny,z,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*dy*(1 - dz), w2 = is_added?1:(1 - w1);
(*this)(nx,ny,z,c) = (T)(w1*value + w2*(*this)(nx,ny,z,c));
}
}
}
if (nz>=0 && nz<depth()) {
if (y>=0 && y<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*(1 - dy)*dz, w2 = is_added?1:(1 - w1);
(*this)(x,y,nz,c) = (T)(w1*value + w2*(*this)(x,y,nz,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*(1 - dy)*dz, w2 = is_added?1:(1 - w1);
(*this)(nx,y,nz,c) = (T)(w1*value + w2*(*this)(nx,y,nz,c));
}
}
if (ny>=0 && ny<height()) {
if (x>=0 && x<width()) {
const float w1 = (1 - dx)*dy*dz, w2 = is_added?1:(1 - w1);
(*this)(x,ny,nz,c) = (T)(w1*value + w2*(*this)(x,ny,nz,c));
}
if (nx>=0 && nx<width()) {
const float w1 = dx*dy*dz, w2 = is_added?1:(1 - w1);
(*this)(nx,ny,nz,c) = (T)(w1*value + w2*(*this)(nx,ny,nz,c));
}
}
}
}
return *this;
}

//! Return a C-string containing a list of all values of the image instance.
/**
       Return a new \c CImg<char> image whose buffer data() is a \c char* string describing the list of all pixel values
       of the image instance (written in base 10), separated by specified \c separator character.
       \param separator A \c char character which specifies the separator between values in the returned C-string.
       \param max_size Maximum size of the returned image (or \c 0 if no limits are set).
       \param format For float/double-values, tell the printf format used to generate the Ascii representation
         of the numbers (or \c 0 for default representation).
       \note
       - The returned image is never empty.
       - For an empty image instance, the returned string is <tt>""</tt>.
       - If \c max_size is equal to \c 0, there are no limits on the size of the returned string.
       - Otherwise, if the maximum number of string characters is exceeded, the value string is cut off
         and terminated by character \c '\0'. In that case, the returned image size is <tt>max_size + 1</tt>.
    **/
CImg<charT> value_string(const char separator=',', const unsigned int max_size=0,
const char *const format=0) const {
if (is_empty() || max_size==1) return CImg<charT>(1,1,1,1,0);
CImgList<charT> items;
CImg<charT> s_item(256); *s_item = 0;
const T *ptrs = _data;
unsigned int string_size = 0;
const char *const _format = format?format:cimg::type<T>::format();
for (ulongT off = 0, siz = size(); off<siz && (!max_size || string_size<max_size); ++off) {
const unsigned int printed_size = 1U + cimg_snprintf(s_item,s_item._width,_format,
cimg::type<T>::format(*(ptrs++)));
CImg<charT> item(s_item._data,printed_size);
item[printed_size - 1] = separator;
item.move_to(items);
if (max_size) string_size+=printed_size;
}
CImg<charT> res;
(items>'x').move_to(res);
if (max_size && res._width>=max_size) res.crop(0,max_size - 1);
res.back() = 0;
return res;
}

//@}
//-------------------------------------
//
//! \name Instance Checking
//@{
//-------------------------------------

//! Test shared state of the pixel buffer.
/**
       Return \c true if image instance has a shared memory buffer, and \c false otherwise.
       \note
       - A shared image do not own his pixel buffer data() and will not deallocate it on destruction.
       - Most of the time, a \c CImg<T> image instance will \e not be shared.
       - A shared image can only be obtained by a limited set of constructors and methods (see list below).
    **/
bool is_shared() const {
return _is_shared;
}

//! Test if image instance is empty.
/**
       Return \c true, if image instance is empty, i.e. does \e not contain any pixel values, has dimensions
       \c 0 x \c 0 x \c 0 x \c 0 and a pixel buffer pointer set to \c 0 (null pointer), and \c false otherwise.
    **/
bool is_empty() const {
return !(_data && _width && _height && _depth && _spectrum);
}

//! Test if image instance contains a 'inf' value.
/**
       Return \c true, if image instance contains a 'inf' value, and \c false otherwise.
    **/
bool is_inf() const {
if (cimg::type<T>::is_float()) cimg_for(*this,p,T) if (cimg::type<T>::is_inf((float)*p)) return true;
return false;
}

//! Test if image instance contains a NaN value.
/**
       Return \c true, if image instance contains a NaN value, and \c false otherwise.
    **/
bool is_nan() const {
if (cimg::type<T>::is_float()) cimg_for(*this,p,T) if (cimg::type<T>::is_nan((float)*p)) return true;
return false;
}

//! Test if image width is equal to specified value.
bool is_sameX(const unsigned int size_x) const {
return _width==size_x;
}

//! Test if image width is equal to specified value.
template<typename t>
bool is_sameX(const CImg<t>& img) const {
return is_sameX(img._width);
}

//! Test if image width is equal to specified value.
bool is_sameX(const CImgDisplay& disp) const {
return is_sameX(disp._width);
}

//! Test if image height is equal to specified value.
bool is_sameY(const unsigned int size_y) const {
return _height==size_y;
}

//! Test if image height is equal to specified value.
template<typename t>
bool is_sameY(const CImg<t>& img) const {
return is_sameY(img._height);
}

//! Test if image height is equal to specified value.
bool is_sameY(const CImgDisplay& disp) const {
return is_sameY(disp._height);
}

//! Test if image depth is equal to specified value.
bool is_sameZ(const unsigned int size_z) const {
return _depth==size_z;
}

//! Test if image depth is equal to specified value.
template<typename t>
bool is_sameZ(const CImg<t>& img) const {
return is_sameZ(img._depth);
}

//! Test if image spectrum is equal to specified value.
bool is_sameC(const unsigned int size_c) const {
return _spectrum==size_c;
}

//! Test if image spectrum is equal to specified value.
template<typename t>
bool is_sameC(const CImg<t>& img) const {
return is_sameC(img._spectrum);
}

//! Test if image width and height are equal to specified values.
/**
       Test if is_sameX(unsigned int) const and is_sameY(unsigned int) const are both verified.
    **/
bool is_sameXY(const unsigned int size_x, const unsigned int size_y) const {
return _width==size_x && _height==size_y;
}

//! Test if image width and height are the same as that of another image.
/**
       Test if is_sameX(const CImg<t>&) const and is_sameY(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXY(const CImg<t>& img) const {
return is_sameXY(img._width,img._height);
}

//! Test if image width and height are the same as that of an existing display window.
/**
       Test if is_sameX(const CImgDisplay&) const and is_sameY(const CImgDisplay&) const are both verified.
    **/
bool is_sameXY(const CImgDisplay& disp) const {
return is_sameXY(disp._width,disp._height);
}

//! Test if image width and depth are equal to specified values.
/**
       Test if is_sameX(unsigned int) const and is_sameZ(unsigned int) const are both verified.
    **/
bool is_sameXZ(const unsigned int size_x, const unsigned int size_z) const {
return _width==size_x && _depth==size_z;
}

//! Test if image width and depth are the same as that of another image.
/**
       Test if is_sameX(const CImg<t>&) const and is_sameZ(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXZ(const CImg<t>& img) const {
return is_sameXZ(img._width,img._depth);
}

//! Test if image width and spectrum are equal to specified values.
/**
       Test if is_sameX(unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameXC(const unsigned int size_x, const unsigned int size_c) const {
return _width==size_x && _spectrum==size_c;
}

//! Test if image width and spectrum are the same as that of another image.
/**
       Test if is_sameX(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXC(const CImg<t>& img) const {
return is_sameXC(img._width,img._spectrum);
}

//! Test if image height and depth are equal to specified values.
/**
       Test if is_sameY(unsigned int) const and is_sameZ(unsigned int) const are both verified.
    **/
bool is_sameYZ(const unsigned int size_y, const unsigned int size_z) const {
return _height==size_y && _depth==size_z;
}

//! Test if image height and depth are the same as that of another image.
/**
       Test if is_sameY(const CImg<t>&) const and is_sameZ(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameYZ(const CImg<t>& img) const {
return is_sameYZ(img._height,img._depth);
}

//! Test if image height and spectrum are equal to specified values.
/**
       Test if is_sameY(unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameYC(const unsigned int size_y, const unsigned int size_c) const {
return _height==size_y && _spectrum==size_c;
}

//! Test if image height and spectrum are the same as that of another image.
/**
       Test if is_sameY(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameYC(const CImg<t>& img) const {
return is_sameYC(img._height,img._spectrum);
}

//! Test if image depth and spectrum are equal to specified values.
/**
       Test if is_sameZ(unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameZC(const unsigned int size_z, const unsigned int size_c) const {
return _depth==size_z && _spectrum==size_c;
}

//! Test if image depth and spectrum are the same as that of another image.
/**
       Test if is_sameZ(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameZC(const CImg<t>& img) const {
return is_sameZC(img._depth,img._spectrum);
}

//! Test if image width, height and depth are equal to specified values.
/**
       Test if is_sameXY(unsigned int,unsigned int) const and is_sameZ(unsigned int) const are both verified.
    **/
bool is_sameXYZ(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z) const {
return is_sameXY(size_x,size_y) && _depth==size_z;
}

//! Test if image width, height and depth are the same as that of another image.
/**
       Test if is_sameXY(const CImg<t>&) const and is_sameZ(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXYZ(const CImg<t>& img) const {
return is_sameXYZ(img._width,img._height,img._depth);
}

//! Test if image width, height and spectrum are equal to specified values.
/**
       Test if is_sameXY(unsigned int,unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameXYC(const unsigned int size_x, const unsigned int size_y, const unsigned int size_c) const {
return is_sameXY(size_x,size_y) && _spectrum==size_c;
}

//! Test if image width, height and spectrum are the same as that of another image.
/**
       Test if is_sameXY(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXYC(const CImg<t>& img) const {
return is_sameXYC(img._width,img._height,img._spectrum);
}

//! Test if image width, depth and spectrum are equal to specified values.
/**
       Test if is_sameXZ(unsigned int,unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameXZC(const unsigned int size_x, const unsigned int size_z, const unsigned int size_c) const {
return is_sameXZ(size_x,size_z) && _spectrum==size_c;
}

//! Test if image width, depth and spectrum are the same as that of another image.
/**
       Test if is_sameXZ(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXZC(const CImg<t>& img) const {
return is_sameXZC(img._width,img._depth,img._spectrum);
}

//! Test if image height, depth and spectrum are equal to specified values.
/**
       Test if is_sameYZ(unsigned int,unsigned int) const and is_sameC(unsigned int) const are both verified.
    **/
bool is_sameYZC(const unsigned int size_y, const unsigned int size_z, const unsigned int size_c) const {
return is_sameYZ(size_y,size_z) && _spectrum==size_c;
}

//! Test if image height, depth and spectrum are the same as that of another image.
/**
       Test if is_sameYZ(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameYZC(const CImg<t>& img) const {
return is_sameYZC(img._height,img._depth,img._spectrum);
}

//! Test if image width, height, depth and spectrum are equal to specified values.
/**
       Test if is_sameXYZ(unsigned int,unsigned int,unsigned int) const and is_sameC(unsigned int) const are both
       verified.
    **/
bool is_sameXYZC(const unsigned int size_x, const unsigned int size_y,
const unsigned int size_z, const unsigned int size_c) const {
return is_sameXYZ(size_x,size_y,size_z) && _spectrum==size_c;
}

//! Test if image width, height, depth and spectrum are the same as that of another image.
/**
       Test if is_sameXYZ(const CImg<t>&) const and is_sameC(const CImg<t>&) const are both verified.
    **/
template<typename t>
bool is_sameXYZC(const CImg<t>& img) const {
return is_sameXYZC(img._width,img._height,img._depth,img._spectrum);
}

//! Test if specified coordinates are inside image bounds.
/**
       Return \c true if pixel located at (\c x,\c y,\c z,\c c) is inside bounds of the image instance,
       and \c false otherwise.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Return \c true only if all these conditions are verified:
         - The image instance is \e not empty.
         - <tt>0<=x<=\ref width() - 1</tt>.
         - <tt>0<=y<=\ref height() - 1</tt>.
         - <tt>0<=z<=\ref depth() - 1</tt>.
         - <tt>0<=c<=\ref spectrum() - 1</tt>.
    **/
bool containsXYZC(const int x, const int y=0, const int z=0, const int c=0) const {
return !is_empty() && x>=0 && x<width() && y>=0 && y<height() && z>=0 && z<depth() && c>=0 && c<spectrum();
}

//! Test if pixel value is inside image bounds and get its X,Y,Z and C-coordinates.
/**
       Return \c true, if specified reference refers to a pixel value inside bounds of the image instance,
       and \c false otherwise.
       \param pixel Reference to pixel value to test.
       \param[out] x X-coordinate of the pixel value, if test succeeds.
       \param[out] y Y-coordinate of the pixel value, if test succeeds.
       \param[out] z Z-coordinate of the pixel value, if test succeeds.
       \param[out] c C-coordinate of the pixel value, if test succeeds.
       \note
       - Useful to convert an offset to a buffer value into pixel value coordinates:
       \code
       const CImg<float> img(100,100,1,3);      // Construct a 100x100 RGB color image
       const unsigned long offset = 1249;       // Offset to the pixel (49,12,0,0)
       unsigned int x,y,z,c;
       if (img.contains(img[offset],x,y,z,c)) { // Convert offset to (x,y,z,c) coordinates
         std::printf("Offset %u refers to pixel located at (%u,%u,%u,%u).\n",
                     offset,x,y,z,c);
       }
       \endcode
    **/
template<typename t>
bool contains(const T& pixel, t& x, t& y, t& z, t& c) const {
const ulongT wh = (ulongT)_width*_height, whd = wh*_depth, siz = whd*_spectrum;
const T *const ppixel = &pixel;
if (is_empty() || ppixel<_data || ppixel>=_data + siz) return false;
ulongT off = (ulongT)(ppixel - _data);
const ulongT nc = off/whd;
off%=whd;
const ulongT nz = off/wh;
off%=wh;
const ulongT ny = off/_width, nx = off%_width;
x = (t)nx; y = (t)ny; z = (t)nz; c = (t)nc;
return true;
}

//! Test if pixel value is inside image bounds and get its X,Y and Z-coordinates.
/**
       Similar to contains(const T&,t&,t&,t&,t&) const, except that only the X,Y and Z-coordinates are set.
    **/
template<typename t>
bool contains(const T& pixel, t& x, t& y, t& z) const {
const ulongT wh = (ulongT)_width*_height, whd = wh*_depth, siz = whd*_spectrum;
const T *const ppixel = &pixel;
if (is_empty() || ppixel<_data || ppixel>=_data + siz) return false;
ulongT off = ((ulongT)(ppixel - _data))%whd;
const ulongT nz = off/wh;
off%=wh;
const ulongT ny = off/_width, nx = off%_width;
x = (t)nx; y = (t)ny; z = (t)nz;
return true;
}

//! Test if pixel value is inside image bounds and get its X and Y-coordinates.
/**
       Similar to contains(const T&,t&,t&,t&,t&) const, except that only the X and Y-coordinates are set.
    **/
template<typename t>
bool contains(const T& pixel, t& x, t& y) const {
const ulongT wh = (ulongT)_width*_height, siz = wh*_depth*_spectrum;
const T *const ppixel = &pixel;
if (is_empty() || ppixel<_data || ppixel>=_data + siz) return false;
ulongT off = ((unsigned int)(ppixel - _data))%wh;
const ulongT ny = off/_width, nx = off%_width;
x = (t)nx; y = (t)ny;
return true;
}

//! Test if pixel value is inside image bounds and get its X-coordinate.
/**
       Similar to contains(const T&,t&,t&,t&,t&) const, except that only the X-coordinate is set.
    **/
template<typename t>
bool contains(const T& pixel, t& x) const {
const T *const ppixel = &pixel;
if (is_empty() || ppixel<_data || ppixel>=_data + size()) return false;
x = (t)(((ulongT)(ppixel - _data))%_width);
return true;
}

//! Test if pixel value is inside image bounds.
/**
       Similar to contains(const T&,t&,t&,t&,t&) const, except that no pixel coordinates are set.
    **/
bool contains(const T& pixel) const {
const T *const ppixel = &pixel;
return !is_empty() && ppixel>=_data && ppixel<_data + size();
}

//! Test if pixel buffers of instance and input images overlap.
/**
       Return \c true, if pixel buffers attached to image instance and input image \c img overlap,
       and \c false otherwise.
       \param img Input image to compare with.
       \note
       - Buffer overlapping may happen when manipulating \e shared images.
       - If two image buffers overlap, operating on one of the image will probably modify the other one.
       - Most of the time, \c CImg<T> instances are \e non-shared and do not overlap between each others.
       \par Example
       \code
       const CImg<float>
         img1("reference.jpg"),             // Load RGB-color image
         img2 = img1.get_shared_channel(1); // Get shared version of the green channel
       if (img1.is_overlapped(img2)) {      // Test succeeds, 'img1' and 'img2' overlaps
         std::printf("Buffers overlap!\n");
       }
       \endcode
    **/
template<typename t>
bool is_overlapped(const CImg<t>& img) const {
const ulongT csiz = size(), isiz = img.size();
return !((void*)(_data + csiz)<=(void*)img._data || (void*)_data>=(void*)(img._data + isiz));
}

//! Test if the set {\c *this,\c primitives,\c colors,\c opacities} defines a valid 3D object.
/**
       Return \c true is the 3D object represented by the set {\c *this,\c primitives,\c colors,\c opacities} defines a
       valid 3D object, and \c false otherwise. The vertex coordinates are defined by the instance image.
       \param primitives List of primitives of the 3D object.
       \param colors List of colors of the 3D object.
       \param opacities List (or image) of opacities of the 3D object.
       \param full_check Tells if full checking of the 3D object must be performed.
       \param[out] error_message C-string to contain the error message, if the test does not succeed.
       \note
       - Set \c full_checking to \c false to speed-up the 3D object checking. In this case, only the size of
         each 3D object component is checked.
       - Size of the string \c error_message should be at least 128-bytes long, to be able to contain the error message.
    **/
template<typename tp, typename tc, typename to>
bool is_object3d(const CImgList<tp>& primitives,
const CImgList<tc>& colors,
const to& opacities,
const bool full_check=true,
char *const error_message=0) const {
if (error_message) *error_message = 0;

// Check consistency for the particular case of an empty 3D object.
if (is_empty()) {
if (primitives || colors || opacities) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines no vertices but %u primitives, "
"%u colors and %lu opacities",
_width,primitives._width,primitives._width,
colors._width,(unsigned long)opacities.size());
return false;
}
return true;
}

// Check consistency of vertices.
if (_height!=3 || _depth>1 || _spectrum>1) { // Check vertices dimensions
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) has invalid vertex dimensions (%u,%u,%u,%u)",
_width,primitives._width,_width,_height,_depth,_spectrum);
return false;
}
if (colors._width>primitives._width + 1) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines %u colors",
_width,primitives._width,colors._width);
return false;
}
if (opacities.size()>primitives._width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines %lu opacities",
_width,primitives._width,(unsigned long)opacities.size());
return false;
}
if (!full_check) return true;

// Check consistency of primitives.
cimglist_for(primitives,l) {
const CImg<tp>& primitive = primitives[l];
const unsigned int psiz = (unsigned int)primitive.size();
switch (psiz) {
case 1 : { // Point
const unsigned int i0 = (unsigned int)primitive(0);
if (i0>=_width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) refers to invalid vertex index %u in "
"point primitive [%u]",
_width,primitives._width,i0,l);
return false;
}
} break;
case 5 : { // Sphere
const unsigned int
i0 = (unsigned int)primitive(0),
i1 = (unsigned int)primitive(1);
if (i0>=_width || i1>=_width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) refers to invalid vertex indices (%u,%u) in "
"sphere primitive [%u]",
_width,primitives._width,i0,i1,l);
return false;
}
} break;
case 2 : case 6 : { // Segment
const unsigned int
i0 = (unsigned int)primitive(0),
i1 = (unsigned int)primitive(1);
if (i0>=_width || i1>=_width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) refers to invalid vertex indices (%u,%u) in "
"segment primitive [%u]",
_width,primitives._width,i0,i1,l);
return false;
}
} break;
case 3 : case 9 : { // Triangle
const unsigned int
i0 = (unsigned int)primitive(0),
i1 = (unsigned int)primitive(1),
i2 = (unsigned int)primitive(2);
if (i0>=_width || i1>=_width || i2>=_width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) refers to invalid vertex indices (%u,%u,%u) in "
"triangle primitive [%u]",
_width,primitives._width,i0,i1,i2,l);
return false;
}
} break;
case 4 : case 12 : { // Quadrangle
const unsigned int
i0 = (unsigned int)primitive(0),
i1 = (unsigned int)primitive(1),
i2 = (unsigned int)primitive(2),
i3 = (unsigned int)primitive(3);
if (i0>=_width || i1>=_width || i2>=_width || i3>=_width) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) refers to invalid vertex indices (%u,%u,%u,%u) in "
"quadrangle primitive [%u]",
_width,primitives._width,i0,i1,i2,i3,l);
return false;
}
} break;
default :
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines an invalid primitive [%u] of size %u",
_width,primitives._width,l,(unsigned int)psiz);
return false;
}
}

// Check consistency of colors.
cimglist_for(colors,c) {
const CImg<tc>& color = colors[c];
if (!color) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines no color for primitive [%u]",
_width,primitives._width,c);
return false;
}
}

// Check consistency of light texture.
if (colors._width>primitives._width) {
const CImg<tc> &light = colors.back();
if (!light || light._depth>1) {
if (error_message) cimg_sprintf(error_message,
"3D object (%u,%u) defines an invalid light texture (%u,%u,%u,%u)",
_width,primitives._width,light._width,
light._height,light._depth,light._spectrum);
return false;
}
}

return true;
}

//! Test if image instance represents a valid serialization of a 3D object.
/**
       Return \c true if the image instance represents a valid serialization of a 3D object, and \c false otherwise.
       \param full_check Tells if full checking of the instance must be performed.
       \param[out] error_message C-string to contain the error message, if the test does not succeed.
       \note
       - Set \c full_check to \c false to speed-up the 3D object checking. In this case, only the size of
         each 3D object component is checked.
       - Size of the string \c error_message should be at least 128-bytes long, to be able to contain the error message.
    **/
bool is_CImg3d(const bool full_check=true, char *const error_message=0) const {
if (error_message) *error_message = 0;

// Check instance dimension and header.
if (_width!=1 || _height<8 || _depth!=1 || _spectrum!=1) {
if (error_message) cimg_sprintf(error_message,
"CImg3d has invalid dimensions (%u,%u,%u,%u)",
_width,_height,_depth,_spectrum);
return false;
}
const T *ptrs = _data, *const ptre = end();
if (!_is_CImg3d(*(ptrs++),'C') || !_is_CImg3d(*(ptrs++),'I') || !_is_CImg3d(*(ptrs++),'m') ||
!_is_CImg3d(*(ptrs++),'g') || !_is_CImg3d(*(ptrs++),'3') || !_is_CImg3d(*(ptrs++),'d')) {
if (error_message) cimg_sprintf(error_message,
"CImg3d header not found");
return false;
}
const unsigned int
nb_points = cimg::float2uint((float)*(ptrs++)),
nb_primitives = cimg::float2uint((float)*(ptrs++));

// Check consistency of number of vertices / primitives.
if (!full_check) {
const ulongT minimal_size = 8UL + 3*nb_points + 6*nb_primitives;
if (_data + minimal_size>ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) has only %lu values, while at least %lu values were expected",
nb_points,nb_primitives,(unsigned long)size(),(unsigned long)minimal_size);
return false;
}
}

// Check consistency of vertex data.
if (!nb_points) {
if (nb_primitives) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines no vertices but %u primitives",
nb_points,nb_primitives,nb_primitives);
return false;
}
if (ptrs!=ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) is an empty object but contains %u value%s "
"more than expected",
nb_points,nb_primitives,(unsigned int)(ptre - ptrs),(ptre - ptrs)>1?"s":"");
return false;
}
return true;
}
if (ptrs + 3*nb_points>ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines only %u vertices data",
nb_points,nb_primitives,(unsigned int)(ptre - ptrs)/3);
return false;
}
ptrs+=3*nb_points;

// Check consistency of primitive data.
if (ptrs==ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines %u vertices but no primitive",
nb_points,nb_primitives,nb_points);
return false;
}

if (!full_check) return true;

for (unsigned int p = 0; p<nb_primitives; ++p) {
const unsigned int nb_inds = (unsigned int)*(ptrs++);
switch (nb_inds) {
case 1 : { // Point
const unsigned int i0 = cimg::float2uint((float)*(ptrs++));
if (i0>=nb_points) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid vertex index %u in point primitive [%u]",
nb_points,nb_primitives,i0,p);
return false;
}
} break;
case 5 : { // Sphere
const unsigned int
i0 = cimg::float2uint((float)*(ptrs++)),
i1 = cimg::float2uint((float)*(ptrs++));
ptrs+=3;
if (i0>=nb_points || i1>=nb_points) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid vertex indices (%u,%u) in "
"sphere primitive [%u]",
nb_points,nb_primitives,i0,i1,p);
return false;
}
} break;
case 2 : case 6 : { // Segment
const unsigned int
i0 = cimg::float2uint((float)*(ptrs++)),
i1 = cimg::float2uint((float)*(ptrs++));
if (nb_inds==6) ptrs+=4;
if (i0>=nb_points || i1>=nb_points) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid vertex indices (%u,%u) in "
"segment primitive [%u]",
nb_points,nb_primitives,i0,i1,p);
return false;
}
} break;
case 3 : case 9 : { // Triangle
const unsigned int
i0 = cimg::float2uint((float)*(ptrs++)),
i1 = cimg::float2uint((float)*(ptrs++)),
i2 = cimg::float2uint((float)*(ptrs++));
if (nb_inds==9) ptrs+=6;
if (i0>=nb_points || i1>=nb_points || i2>=nb_points) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid vertex indices (%u,%u,%u) in "
"triangle primitive [%u]",
nb_points,nb_primitives,i0,i1,i2,p);
return false;
}
} break;
case 4 : case 12 : { // Quadrangle
const unsigned int
i0 = cimg::float2uint((float)*(ptrs++)),
i1 = cimg::float2uint((float)*(ptrs++)),
i2 = cimg::float2uint((float)*(ptrs++)),
i3 = cimg::float2uint((float)*(ptrs++));
if (nb_inds==12) ptrs+=8;
if (i0>=nb_points || i1>=nb_points || i2>=nb_points || i3>=nb_points) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid vertex indices (%u,%u,%u,%u) in "
"quadrangle primitive [%u]",
nb_points,nb_primitives,i0,i1,i2,i3,p);
return false;
}
} break;
default :
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines an invalid primitive [%u] of size %u",
nb_points,nb_primitives,p,nb_inds);
return false;
}
if (ptrs>ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) has incomplete primitive data for primitive [%u], "
"%u values missing",
nb_points,nb_primitives,p,(unsigned int)(ptrs - ptre));
return false;
}
}

// Check consistency of color data.
if (ptrs==ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines no color/texture data",
nb_points,nb_primitives);
return false;
}
for (unsigned int c = 0; c<nb_primitives; ++c) {
if (*(ptrs++)!=(T)-128) ptrs+=2;
else if ((ptrs+=3)<ptre) {
const unsigned int
w = (unsigned int)*(ptrs - 3),
h = (unsigned int)*(ptrs - 2),
s = (unsigned int)*(ptrs - 1);
if (!h && !s) {
if (w>=c) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid shared sprite/texture index %u "
"for primitive [%u]",
nb_points,nb_primitives,w,c);
return false;
}
} else ptrs+=w*h*s;
}
if (ptrs>ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) has incomplete color/texture data for primitive [%u], "
"%u values missing",
nb_points,nb_primitives,c,(unsigned int)(ptrs - ptre));
return false;
}
}

// Check consistency of opacity data.
if (ptrs==ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) defines no opacity data",
nb_points,nb_primitives);
return false;
}
for (unsigned int o = 0; o<nb_primitives; ++o) {
if (*(ptrs++)==(T)-128 && (ptrs+=3)<ptre) {
const unsigned int
w = (unsigned int)*(ptrs - 3),
h = (unsigned int)*(ptrs - 2),
s = (unsigned int)*(ptrs - 1);
if (!h && !s) {
if (w>=o) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) refers to invalid shared opacity index %u "
"for primitive [%u]",
nb_points,nb_primitives,w,o);
return false;
}
} else ptrs+=w*h*s;
}
if (ptrs>ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) has incomplete opacity data for primitive [%u]",
nb_points,nb_primitives,o);
return false;
}
}

// Check end of data.
if (ptrs<ptre) {
if (error_message) cimg_sprintf(error_message,
"CImg3d (%u,%u) contains %u value%s more than expected",
nb_points,nb_primitives,(unsigned int)(ptre - ptrs),(ptre - ptrs)>1?"s":"");
return false;
}
return true;
}

static bool _is_CImg3d(const T val, const char c) {
return val>=(T)c && val<(T)(c + 1);
}

//@}
//-------------------------------------
//
//! \name Mathematical Functions
//@{
//-------------------------------------

// Define the math formula parser/compiler and expression evaluator.
struct _cimg_math_parser {
CImg<doubleT> mem;
CImg<intT> memtype;
CImgList<ulongT> _code, &code, code_begin, code_end;
CImg<ulongT> opcode;
const CImg<ulongT> *p_code_end, *p_code;
const CImg<ulongT> *const p_break;

CImg<charT> expr, pexpr;
const CImg<T>& imgin;
const CImgList<T>& listin;
CImg<T> &imgout;
CImgList<T>& listout;

CImg<doubleT> _img_stats, &img_stats, constcache_vals;
CImgList<doubleT> _list_stats, &list_stats, _list_median, &list_median;
CImg<uintT> mem_img_stats, constcache_inds;

CImg<uintT> level, variable_pos, reserved_label;
CImgList<charT> variable_def, macro_def, macro_body;
CImgList<boolT> macro_body_is_string;
char *user_macro;

unsigned int mempos, mem_img_median, debug_indent, result_dim, break_type, constcache_size;
bool is_parallelizable, is_fill, need_input_copy;
double *result;
ulongT rng;
const char *const calling_function, *s_op, *ss_op;
typedef double (*mp_func)(_cimg_math_parser&);

#define _cimg_mp_is_constant(arg) (memtype[arg]==1) // Is constant value?
#define _cimg_mp_is_scalar(arg) (memtype[arg]<2) // Is scalar value?
#define _cimg_mp_is_comp(arg) (!memtype[arg]) // Is computation value?
#define _cimg_mp_is_variable(arg) (memtype[arg]==-1) // Is scalar variable?
#define _cimg_mp_is_vector(arg) (memtype[arg]>1) // Is vector?
#define _cimg_mp_size(arg) (_cimg_mp_is_scalar(arg)?0U:(unsigned int)memtype[arg] - 1) // Size (0=scalar, N>0=vectorN)
#define _cimg_mp_calling_function calling_function_s()._data
#define _cimg_mp_op(s) s_op = s; ss_op = ss
#define _cimg_mp_check_type(arg,n_arg,mode,N) check_type(arg,n_arg,mode,N,ss,se,saved_char)
#define _cimg_mp_check_constant(arg,n_arg,mode) check_constant(arg,n_arg,mode,ss,se,saved_char)
#define _cimg_mp_check_matrix_square(arg,n_arg) check_matrix_square(arg,n_arg,ss,se,saved_char)
#define _cimg_mp_check_list(is_out) check_list(is_out,ss,se,saved_char)
#define _cimg_mp_defunc(mp) (*(mp_func)(*(mp).opcode))(mp)
#define _cimg_mp_return(x) { *se = saved_char; s_op = previous_s_op; ss_op = previous_ss_op; return x; }
#define _cimg_mp_return_nan() _cimg_mp_return(_cimg_mp_slot_nan)
#define _cimg_mp_constant(val) _cimg_mp_return(constant((double)(val)))
#define _cimg_mp_scalar0(op) _cimg_mp_return(scalar0(op))
#define _cimg_mp_scalar1(op,i1) _cimg_mp_return(scalar1(op,i1))
#define _cimg_mp_scalar2(op,i1,i2) _cimg_mp_return(scalar2(op,i1,i2))
#define _cimg_mp_scalar3(op,i1,i2,i3) _cimg_mp_return(scalar3(op,i1,i2,i3))
#define _cimg_mp_scalar4(op,i1,i2,i3,i4) _cimg_mp_return(scalar4(op,i1,i2,i3,i4))
#define _cimg_mp_scalar5(op,i1,i2,i3,i4,i5) _cimg_mp_return(scalar5(op,i1,i2,i3,i4,i5))
#define _cimg_mp_scalar6(op,i1,i2,i3,i4,i5,i6) _cimg_mp_return(scalar6(op,i1,i2,i3,i4,i5,i6))
#define _cimg_mp_scalar7(op,i1,i2,i3,i4,i5,i6,i7) _cimg_mp_return(scalar7(op,i1,i2,i3,i4,i5,i6,i7))
#define _cimg_mp_vector1_v(op,i1) _cimg_mp_return(vector1_v(op,i1))
#define _cimg_mp_vector2_sv(op,i1,i2) _cimg_mp_return(vector2_sv(op,i1,i2))
#define _cimg_mp_vector2_vs(op,i1,i2) _cimg_mp_return(vector2_vs(op,i1,i2))
#define _cimg_mp_vector2_vv(op,i1,i2) _cimg_mp_return(vector2_vv(op,i1,i2))
#define _cimg_mp_vector3_vss(op,i1,i2,i3) _cimg_mp_return(vector3_vss(op,i1,i2,i3))

// Constructors / Destructors.
~_cimg_math_parser() {
cimg::srand(rng);
}

_cimg_math_parser(const char *const expression, const char *const funcname=0,
const CImg<T>& img_input=CImg<T>::const_empty(), CImg<T> *const img_output=0,
const CImgList<T> *const list_inputs=0, CImgList<T> *const list_outputs=0,
const bool _is_fill=false):
code(_code),p_break((CImg<ulongT>*)(cimg_ulong)-2),
imgin(img_input),listin(list_inputs?*list_inputs:CImgList<T>::const_empty()),
imgout(img_output?*img_output:CImg<T>::empty()),listout(list_outputs?*list_outputs:CImgList<T>::empty()),
img_stats(_img_stats),list_stats(_list_stats),list_median(_list_median),user_macro(0),
mem_img_median(~0U),debug_indent(0),result_dim(0),break_type(0),constcache_size(0),
is_parallelizable(true),is_fill(_is_fill),need_input_copy(false),
rng((cimg::_rand(),cimg::rng())),calling_function(funcname?funcname:"cimg_math_parser") {

#if cimg_use_openmp!=0
rng+=omp_get_thread_num();
#endif
if (!expression || !*expression)
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: Empty expression.",
pixel_type(),_cimg_mp_calling_function);
const char *_expression = expression;
while (*_expression && (cimg::is_blank(*_expression) || *_expression==';')) ++_expression;
CImg<charT>::string(_expression).move_to(expr);
char *ps = &expr.back() - 1;
while (ps>expr._data && (cimg::is_blank(*ps) || *ps==';')) --ps;
*(++ps) = 0; expr._width = (unsigned int)(ps - expr._data + 1);

// Ease the retrieval of previous non-space characters afterwards.
pexpr.assign(expr._width);
char c, *pe = pexpr._data;
for (ps = expr._data, c = ' '; *ps; ++ps) {
if (!cimg::is_blank(*ps)) c = *ps; else *ps = ' ';
*(pe++) = c;
}
*pe = 0;
level = get_level(expr);

// Init constant values.
#define _cimg_mp_interpolation (reserved_label[29]!=~0U?reserved_label[29]:0)
#define _cimg_mp_boundary (reserved_label[30]!=~0U?reserved_label[30]:0)
#define _cimg_mp_slot_nan 29
#define _cimg_mp_slot_x 30
#define _cimg_mp_slot_y 31
#define _cimg_mp_slot_z 32
#define _cimg_mp_slot_c 33

mem.assign(96);
for (unsigned int i = 0; i<=10; ++i) mem[i] = (double)i; // mem[0-10] = 0...10
for (unsigned int i = 1; i<=5; ++i) mem[i + 10] = -(double)i; // mem[11-15] = -1...-5
mem[16] = 0.5;
mem[17] = 0; // thread_id
mem[18] = (double)imgin._width; // w
mem[19] = (double)imgin._height; // h
mem[20] = (double)imgin._depth; // d
mem[21] = (double)imgin._spectrum; // s
mem[22] = (double)imgin._is_shared; // r
mem[23] = (double)imgin._width*imgin._height; // wh
mem[24] = (double)imgin._width*imgin._height*imgin._depth; // whd
mem[25] = (double)imgin._width*imgin._height*imgin._depth*imgin._spectrum; // whds
mem[26] = (double)listin._width; // l
mem[27] = std::exp(1.); // e
mem[28] = cimg::PI; // pi
mem[_cimg_mp_slot_nan] = cimg::type<double>::nan(); // nan

// Set value property :
// { -2 = other | -1 = variable | 0 = computation value |
//    1 = compile-time constant | N>1 = constant ptr to vector[N-1] }.
memtype.assign(mem._width,1,1,1,0);
for (unsigned int i = 0; i<_cimg_mp_slot_x; ++i) memtype[i] = 1;
memtype[17] = 0;
memtype[_cimg_mp_slot_x] = memtype[_cimg_mp_slot_y] = memtype[_cimg_mp_slot_z] = memtype[_cimg_mp_slot_c] = -2;
mempos = _cimg_mp_slot_c + 1;
variable_pos.assign(8);

reserved_label.assign(128,1,1,1,~0U);
// reserved_label[4-28] are used to store these two-char variables:
// [0] = wh, [1] = whd, [2] = whds, [3] = pi, [4] = im, [5] = iM, [6] = ia, [7] = iv,
// [8] = is, [9] = ip, [10] = ic, [11] = xm, [12] = ym, [13] = zm, [14] = cm, [15] = xM,
// [16] = yM, [17] = zM, [18]=cM, [19]=i0...[28]=i9, [29] = interpolation, [30] = boundary

// Compile expression into a serie of opcodes.
s_op = ""; ss_op = expr._data;
const unsigned int ind_result = compile(expr._data,expr._data + expr._width - 1,0,0,false);
if (!_cimg_mp_is_constant(ind_result)) {
if (_cimg_mp_is_vector(ind_result))
CImg<doubleT>(&mem[ind_result] + 1,_cimg_mp_size(ind_result),1,1,1,true).
fill(cimg::type<double>::nan());
else mem[ind_result] = cimg::type<double>::nan();
}

// Free resources used for compiling expression and prepare evaluation.
result_dim = _cimg_mp_size(ind_result);
if (mem._width>=256 && mem._width - mempos>=mem._width/2) mem.resize(mempos,1,1,1,-1);
result = mem._data + ind_result;
memtype.assign();
constcache_vals.assign();
constcache_inds.assign();
level.assign();
variable_pos.assign();
reserved_label.assign();
expr.assign();
pexpr.assign();
opcode.assign();
opcode._is_shared = true;

// Execute begin() bloc if any specified.
if (code_begin) {
mem[_cimg_mp_slot_x] = mem[_cimg_mp_slot_y] = mem[_cimg_mp_slot_z] = mem[_cimg_mp_slot_c] = 0;
p_code_end = code_begin.end();
for (p_code = code_begin; p_code<p_code_end; ++p_code) {
opcode._data = p_code->_data;
const ulongT target = opcode[1];
mem[target] = _cimg_mp_defunc(*this);
}
}
p_code_end = code.end();
}

_cimg_math_parser():
code(_code),p_code_end(0),p_break((CImg<ulongT>*)(cimg_ulong)-2),
imgin(CImg<T>::const_empty()),listin(CImgList<T>::const_empty()),
imgout(CImg<T>::empty()),listout(CImgList<T>::empty()),
img_stats(_img_stats),list_stats(_list_stats),list_median(_list_median),debug_indent(0),
result_dim(0),break_type(0),constcache_size(0),is_parallelizable(true),is_fill(false),need_input_copy(false),
rng(0),calling_function(0) {
mem.assign(1 + _cimg_mp_slot_c,1,1,1,0); // Allow to skip 'is_empty?' test in operator()()
result = mem._data;
}

_cimg_math_parser(const _cimg_math_parser& mp):
mem(mp.mem),code(mp.code),p_code_end(mp.p_code_end),p_break(mp.p_break),
imgin(mp.imgin),listin(mp.listin),imgout(mp.imgout),listout(mp.listout),img_stats(mp.img_stats),
list_stats(mp.list_stats),list_median(mp.list_median),debug_indent(0),result_dim(mp.result_dim),
break_type(0),constcache_size(0),is_parallelizable(mp.is_parallelizable),is_fill(mp.is_fill),
need_input_copy(mp.need_input_copy), result(mem._data + (mp.result - mp.mem._data)),
rng((cimg::_rand(),cimg::rng())),calling_function(0) {

#if cimg_use_openmp!=0
mem[17] = omp_get_thread_num();
rng+=omp_get_thread_num();
#endif
opcode.assign();
opcode._is_shared = true;
}

// Count parentheses/brackets level of each character of the expression.
CImg<uintT> get_level(CImg<charT>& expr) const {
bool is_escaped = false, next_is_escaped = false;
unsigned int mode = 0, next_mode = 0; // { 0=normal | 1=char-string | 2=vector-string
CImg<uintT> res(expr._width - 1);
unsigned int *pd = res._data;
int level = 0;
for (const char *ps = expr._data; *ps && level>=0; ++ps) {
if (!is_escaped && !next_is_escaped && *ps=='\\') next_is_escaped = true;
if (!is_escaped && *ps=='\'') { // Non-escaped character
if (!mode && ps>expr._data && *(ps - 1)=='[') next_mode = mode = 2; // Start vector-string
else if (mode==2 && *(ps + 1)==']') next_mode = !mode; // End vector-string
else if (mode<2) next_mode = mode?(mode = 0):1; // Start/end char-string
}
*(pd++) = (unsigned int)(mode>=1 || is_escaped?level + (mode==1):
*ps=='(' || *ps=='['?level++:
*ps==')' || *ps==']'?--level:
level);
mode = next_mode;
is_escaped = next_is_escaped;
next_is_escaped = false;
}
if (mode) {
cimg::strellipsize(expr,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: Unterminated string literal, in expression '%s'.",
pixel_type(),_cimg_mp_calling_function,
expr._data);
}
if (level) {
cimg::strellipsize(expr,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: Unbalanced parentheses/brackets, in expression '%s'.",
pixel_type(),_cimg_mp_calling_function,
expr._data);
}
return res;
}

// Tell for each character of an expression if it is inside a string or not.
CImg<boolT> is_inside_string(CImg<charT>& expr) const {
bool is_escaped = false, next_is_escaped = false;
unsigned int mode = 0, next_mode = 0; // { 0=normal | 1=char-string | 2=vector-string
CImg<boolT> res = CImg<charT>::string(expr);
bool *pd = res._data;
for (const char *ps = expr._data; *ps; ++ps) {
if (!next_is_escaped && *ps=='\\') next_is_escaped = true;
if (!is_escaped && *ps=='\'') { // Non-escaped character
if (!mode && ps>expr._data && *(ps - 1)=='[') next_mode = mode = 2; // Start vector-string
else if (mode==2 && *(ps + 1)==']') next_mode = !mode; // End vector-string
else if (mode<2) next_mode = mode?(mode = 0):1; // Start/end char-string
}
*(pd++) = mode>=1 || is_escaped;
mode = next_mode;
is_escaped = next_is_escaped;
next_is_escaped = false;
}
return res;
}

// Compilation procedure.
unsigned int compile(char *ss, char *se, const unsigned int depth, unsigned int *const p_ref,
const bool is_single) {
if (depth>256) {
cimg::strellipsize(expr,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: Call stack overflow (infinite recursion?), "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,
(ss - 4)>expr._data?"...":"",
(ss - 4)>expr._data?ss - 4:expr._data,
se<&expr.back()?"...":"");
}
char c1, c2, c3, c4;

// Simplify expression when possible.
do {
c2 = 0;
if (ss<se) {
while (*ss && (cimg::is_blank(*ss) || *ss==';')) ++ss;
while (se>ss && (cimg::is_blank(c1 = *(se - 1)) || c1==';')) --se;
}
while (*ss=='(' && *(se - 1)==')' && std::strchr(ss,')')==se - 1) {
++ss; --se; c2 = 1;
}
} while (c2 && ss<se);

if (se<=ss || !*ss) {
cimg::strellipsize(expr,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s%s Missing %s, in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,*s_op?":":"",
*s_op=='F'?"argument":"item",
(ss_op - 4)>expr._data?"...":"",
(ss_op - 4)>expr._data?ss_op - 4:expr._data,
ss_op + std::strlen(ss_op)<&expr.back()?"...":"");
}

const char *const previous_s_op = s_op, *const previous_ss_op = ss_op;
const unsigned int depth1 = depth + 1;
unsigned int pos, p1, p2, p3, arg1, arg2, arg3, arg4, arg5, arg6;
char
*const se1 = se - 1, *const se2 = se - 2, *const se3 = se - 3,
*const ss1 = ss + 1, *const ss2 = ss + 2, *const ss3 = ss + 3, *const ss4 = ss + 4,
*const ss5 = ss + 5, *const ss6 = ss + 6, *const ss7 = ss + 7, *const ss8 = ss + 8,
*s, *ps, *ns, *s0, *s1, *s2, *s3, sep = 0, end = 0;
double val = 0, val1, val2;
mp_func op;

// 'p_ref' is a 'unsigned int[7]' used to return a reference to an image or vector value
// linked to the returned memory slot (reference that cannot be determined at compile time).
// p_ref[0] can be { 0 = scalar (unlinked) | 1 = vector value | 2 = image value (offset) |
//                   3 = image value (coordinates) | 4 = image value as a vector (offsets) |
//                   5 = image value as a vector (coordinates) }.
// Depending on p_ref[0], the remaining p_ref[k] have the following meaning:
// When p_ref[0]==0, p_ref is actually unlinked.
// When p_ref[0]==1, p_ref = [ 1, vector_ind, offset ].
// When p_ref[0]==2, p_ref = [ 2, image_ind (or ~0U), is_relative, offset ].
// When p_ref[0]==3, p_ref = [ 3, image_ind (or ~0U), is_relative, x, y, z, c ].
// When p_ref[0]==4, p_ref = [ 4, image_ind (or ~0U), is_relative, offset ].
// When p_ref[0]==5, p_ref = [ 5, image_ind (or ~0U), is_relative, x, y, z ].
if (p_ref) { *p_ref = 0; p_ref[1] = p_ref[2] = p_ref[3] = p_ref[4] = p_ref[5] = p_ref[6] = ~0U; }

const char saved_char = *se; *se = 0;
const unsigned int clevel = level[ss - expr._data], clevel1 = clevel + 1;
bool is_sth, is_relative;
CImg<uintT> ref;
CImg<charT> variable_name;
CImgList<ulongT> l_opcode;

// Look for a single value or a pre-defined variable.
int nb = 0;
s = ss + (*ss=='+' || *ss=='-'?1:0);
if (*s=='i' || *s=='I' || *s=='n' || *s=='N') { // Particular cases : +/-NaN and +/-Inf
is_sth = *ss=='-';
if (!cimg::strcasecmp(s,"inf")) { val = cimg::type<double>::inf(); nb = 1; }
else if (!cimg::strcasecmp(s,"nan")) { val = cimg::type<double>::nan(); nb = 1; }
if (nb==1 && is_sth) val = -val;
} else if (*s=='0' && (s[1]=='x' || s[1]=='X')) { // Hexadecimal number
is_sth = *ss=='-';
if (cimg_sscanf(s + 2,"%x%c",&arg1,&sep)==1) {
nb = 1;
val = (double)arg1;
if (is_sth) val = -val;
}
}
if (!nb) nb = cimg_sscanf(ss,"%lf%c%c",&val,&(sep=0),&(end=0));
if (nb==1) _cimg_mp_constant(val);
if (nb==2 && sep=='%') _cimg_mp_constant(val/100);

if (ss1==se) switch (*ss) { // One-char reserved variable
case 'c' : _cimg_mp_return(reserved_label[(int)'c']!=~0U?reserved_label[(int)'c']:_cimg_mp_slot_c);
case 'd' : _cimg_mp_return(reserved_label[(int)'d']!=~0U?reserved_label[(int)'d']:20);
case 'e' : _cimg_mp_return(reserved_label[(int)'e']!=~0U?reserved_label[(int)'e']:27);
case 'h' : _cimg_mp_return(reserved_label[(int)'h']!=~0U?reserved_label[(int)'h']:19);
case 'l' : _cimg_mp_return(reserved_label[(int)'l']!=~0U?reserved_label[(int)'l']:26);
case 'r' : _cimg_mp_return(reserved_label[(int)'r']!=~0U?reserved_label[(int)'r']:22);
case 's' : _cimg_mp_return(reserved_label[(int)'s']!=~0U?reserved_label[(int)'s']:21);
case 't' : _cimg_mp_return(reserved_label[(int)'t']!=~0U?reserved_label[(int)'t']:17);
case 'w' : _cimg_mp_return(reserved_label[(int)'w']!=~0U?reserved_label[(int)'w']:18);
case 'x' : _cimg_mp_return(reserved_label[(int)'x']!=~0U?reserved_label[(int)'x']:_cimg_mp_slot_x);
case 'y' : _cimg_mp_return(reserved_label[(int)'y']!=~0U?reserved_label[(int)'y']:_cimg_mp_slot_y);
case 'z' : _cimg_mp_return(reserved_label[(int)'z']!=~0U?reserved_label[(int)'z']:_cimg_mp_slot_z);
case 'u' :
if (reserved_label[(int)'u']!=~0U) _cimg_mp_return(reserved_label[(int)'u']);
_cimg_mp_scalar2(mp_u,0,1);
case 'g' :
if (reserved_label[(int)'g']!=~0U) _cimg_mp_return(reserved_label[(int)'g']);
_cimg_mp_scalar0(mp_g);
case 'i' :
if (reserved_label[(int)'i']!=~0U) _cimg_mp_return(reserved_label[(int)'i']);
_cimg_mp_scalar0(mp_i);
case 'I' :
_cimg_mp_op("Variable 'I'");
if (reserved_label[(int)'I']!=~0U) _cimg_mp_return(reserved_label[(int)'I']);
if (!imgin._spectrum) _cimg_mp_return(0);
need_input_copy = true;
pos = vector(imgin._spectrum);
CImg<ulongT>::vector((ulongT)mp_Joff,pos,0,0,imgin._spectrum).move_to(code);
_cimg_mp_return(pos);
case 'R' :
if (reserved_label[(int)'R']!=~0U) _cimg_mp_return(reserved_label[(int)'R']);
need_input_copy = true;
_cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,0,0,0);
case 'G' :
if (reserved_label[(int)'G']!=~0U) _cimg_mp_return(reserved_label[(int)'G']);
need_input_copy = true;
_cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,1,0,0);
case 'B' :
if (reserved_label[(int)'B']!=~0U) _cimg_mp_return(reserved_label[(int)'B']);
need_input_copy = true;
_cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,2,0,0);
case 'A' :
if (reserved_label[(int)'A']!=~0U) _cimg_mp_return(reserved_label[(int)'A']);
need_input_copy = true;
_cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,3,0,0);
}
else if (ss2==se) { // Two-chars reserved variable
arg1 = arg2 = ~0U;
if (*ss=='w' && *ss1=='h') // wh
_cimg_mp_return(reserved_label[0]!=~0U?reserved_label[0]:23);
if (*ss=='p' && *ss1=='i') // pi
_cimg_mp_return(reserved_label[3]!=~0U?reserved_label[3]:28);
if (*ss=='i') {
if (*ss1>='0' && *ss1<='9') { // i0...i9
pos = 19 + *ss1 - '0';
if (reserved_label[pos]!=~0U) _cimg_mp_return(reserved_label[pos]);
need_input_copy = true;
_cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,pos - 19,0,0);
}
switch (*ss1) {
case 'm' : arg1 = 4; arg2 = 0; break; // im
case 'M' : arg1 = 5; arg2 = 1; break; // iM
case 'a' : arg1 = 6; arg2 = 2; break; // ia
case 'v' : arg1 = 7; arg2 = 3; break; // iv
case 's' : arg1 = 8; arg2 = 12; break; // is
case 'p' : arg1 = 9; arg2 = 13; break; // ip
case 'c' : // ic
if (reserved_label[10]!=~0U) _cimg_mp_return(reserved_label[10]);
if (mem_img_median==~0U) mem_img_median = imgin?constant(imgin.median()):0;
_cimg_mp_return(mem_img_median);
break;
}
}
else if (*ss1=='m') switch (*ss) {
case 'x' : arg1 = 11; arg2 = 4; break; // xm
case 'y' : arg1 = 12; arg2 = 5; break; // ym
case 'z' : arg1 = 13; arg2 = 6; break; // zm
case 'c' : arg1 = 14; arg2 = 7; break; // cm
}
else if (*ss1=='M') switch (*ss) {
case 'x' : arg1 = 15; arg2 = 8; break; // xM
case 'y' : arg1 = 16; arg2 = 9; break; // yM
case 'z' : arg1 = 17; arg2 = 10; break; // zM
case 'c' : arg1 = 18; arg2 = 11; break; // cM
}
if (arg1!=~0U) {
if (reserved_label[arg1]!=~0U) _cimg_mp_return(reserved_label[arg1]);
if (!img_stats) {
img_stats.assign(1,14,1,1,0).fill(imgin.get_stats(),false);
mem_img_stats.assign(1,14,1,1,~0U);
}
if (mem_img_stats[arg2]==~0U) mem_img_stats[arg2] = constant(img_stats[arg2]);
_cimg_mp_return(mem_img_stats[arg2]);
}
} else if (ss3==se) { // Three-chars reserved variable
if (*ss=='w' && *ss1=='h' && *ss2=='d') // whd
_cimg_mp_return(reserved_label[1]!=~0U?reserved_label[1]:24);
} else if (ss4==se) { // Four-chars reserved variable
if (*ss=='w' && *ss1=='h' && *ss2=='d' && *ss3=='s') // whds
_cimg_mp_return(reserved_label[2]!=~0U?reserved_label[2]:25);
}

pos = ~0U;
is_sth = false;
for (s0 = ss, s = ss1; s<se1; ++s)
if (*s==';' && level[s - expr._data]==clevel) { // Separator ';'
arg1 = code_end._width;
arg2 = compile(s0,s++,depth,0,is_single);
if (code_end._width==arg1) pos = arg2; // makes 'end()' return void
is_sth = true;
while (*s && (cimg::is_blank(*s) || *s==';')) ++s;
s0 = s;
}
if (is_sth) {
arg1 = code_end._width;
arg2 = compile(s0,se,depth,p_ref,is_single);
if (code_end._width==arg1) pos = arg2; // makes 'end()' return void
_cimg_mp_return(pos);
}

// Declare / assign variable, vector value or image value.
for (s = ss1, ps = ss, ns = ss2; s<se1; ++s, ++ps, ++ns)
if (*s=='=' && *ns!='=' && *ps!='=' && *ps!='>' && *ps!='<' && *ps!='!' &&
*ps!='+' && *ps!='-' && *ps!='*' && *ps!='/' && *ps!='%' &&
*ps!='>' && *ps!='<' && *ps!='&' && *ps!='|' && *ps!='^' &&
level[s - expr._data]==clevel) {
variable_name.assign(ss,(unsigned int)(s + 1 - ss)).back() = 0;
cimg::strpare(variable_name,false,true);
const unsigned int l_variable_name = (unsigned int)std::strlen(variable_name);
char *const ve1 = ss + l_variable_name - 1;
_cimg_mp_op("Operator '='");

// Assign image value (direct).
if (l_variable_name>2 && (*ss=='i' || *ss=='j' || *ss=='I' || *ss=='J') && (*ss1=='(' || *ss1=='[') &&
(reserved_label[(int)*ss]==~0U || *ss1=='(' || !_cimg_mp_is_vector(reserved_label[(int)*ss]))) {
is_relative = *ss=='j' || *ss=='J';

if (*ss1=='[' && *ve1==']') { // i/j/I/J[_#ind,offset] = value
if (!is_single) is_parallelizable = false;
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<ve1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
_cimg_mp_check_list(true);
} else { p1 = ~0U; s0 = ss2; }
arg1 = compile(s0,ve1,depth1,0,is_single); // Offset
_cimg_mp_check_type(arg1,0,1,0);
arg2 = compile(s + 1,se,depth1,0,is_single); // Value to assign
if (_cimg_mp_is_vector(arg2)) {
p2 = ~0U; // 'p2' must be the dimension of the vector-valued operand if any
if (p1==~0U) p2 = imgin._spectrum;
else if (_cimg_mp_is_constant(p1)) {
p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
p2 = listin[p3]._spectrum;
}
if (!p2) _cimg_mp_return(0);
} else p2 = 0;
_cimg_mp_check_type(arg2,2,*ss>='i'?1:3,p2);

if (p_ref) {
*p_ref = _cimg_mp_is_vector(arg2)?4:2;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
if (_cimg_mp_is_vector(arg2))
set_variable_vector(arg2); // Prevent from being used in further optimization
else if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
}


if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg2);
if (*ss>='i')
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
arg2,p1,arg1).move_to(code);
else if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_s:mp_list_set_Ioff_s),
arg2,p1,arg1).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
arg2,p1,arg1,_cimg_mp_size(arg2)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg2);
if (*ss>='i')
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
arg2,arg1).move_to(code);
else if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_s:mp_set_Ioff_s),
arg2,arg1).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
arg2,arg1,_cimg_mp_size(arg2)).move_to(code);
}
_cimg_mp_return(arg2);
}

if (*ss1=='(' && *ve1==')') { // i/j/I/J(_#ind,_x,_y,_z,_c) = value
if (!is_single) is_parallelizable = false;
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<ve1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
_cimg_mp_check_list(true);
} else { p1 = ~0U; s0 = ss2; }
arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
arg4 = is_relative?0U:(unsigned int)_cimg_mp_slot_c;
arg5 = compile(s + 1,se,depth1,0,is_single); // Value to assign
if (s0<ve1) { // X or [ X,_Y,_Z,_C ]
s1 = s0; while (s1<ve1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(s0,s1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) { // Coordinates specified as a vector
p2 = _cimg_mp_size(arg1); // Vector size
++arg1;
if (p2>1) {
arg2 = arg1 + 1;
if (p2>2) {
arg3 = arg2 + 1;
if (p2>3) arg4 = arg3 + 1;
}
}
} else if (s1<ve1) { // Y
s2 = ++s1; while (s2<ve1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1,s2,depth1,0,is_single);
if (s2<ve1) { // Z
s3 = ++s2; while (s3<ve1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg3 = compile(s2,s3,depth1,0,is_single);
if (s3<ve1) arg4 = compile(++s3,ve1,depth1,0,is_single); // C
}
}
}

if (_cimg_mp_is_vector(arg5)) {
p2 = ~0U; // 'p2' must be the dimension of the vector-valued operand if any
if (p1==~0U) p2 = imgin._spectrum;
else if (_cimg_mp_is_constant(p1)) {
p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
p2 = listin[p3]._spectrum;
}
if (!p2) _cimg_mp_return(0);
} else p2 = 0;
_cimg_mp_check_type(arg5,2,*ss>='i'?1:3,p2);

if (p_ref) {
*p_ref = _cimg_mp_is_vector(arg5)?5:3;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
p_ref[4] = arg2;
p_ref[5] = arg3;
p_ref[6] = arg4;
if (_cimg_mp_is_vector(arg5))
set_variable_vector(arg5); // Prevent from being used in further optimization
else if (_cimg_mp_is_comp(arg5)) memtype[arg5] = -2;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
if (_cimg_mp_is_comp(arg4)) memtype[arg4] = -2;
}
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg5);
if (*ss>='i')
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
arg5,p1,arg1,arg2,arg3,arg4).move_to(code);
else if (_cimg_mp_is_scalar(arg5))
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_s:mp_list_set_Ixyz_s),
arg5,p1,arg1,arg2,arg3).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
arg5,p1,arg1,arg2,arg3,_cimg_mp_size(arg5)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg5);
if (*ss>='i')
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
arg5,arg1,arg2,arg3,arg4).move_to(code);
else if (_cimg_mp_is_scalar(arg5))
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_s:mp_set_Ixyz_s),
arg5,arg1,arg2,arg3).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
arg5,arg1,arg2,arg3,_cimg_mp_size(arg5)).move_to(code);
}
_cimg_mp_return(arg5);
}
}

// Assign vector value (direct).
if (l_variable_name>3 && *ve1==']' && *ss!='[') {
s0 = ve1; while (s0>ss && (*s0!='[' || level[s0 - expr._data]!=clevel)) --s0;
is_sth = true; // is_valid_variable_name?
if (*ss>='0' && *ss<='9') is_sth = false;
else for (ns = ss; ns<s0; ++ns)
if (!is_varchar(*ns)) { is_sth = false; break; }
if (is_sth && s0>ss) {
variable_name[s0 - ss] = 0; // Remove brackets in variable name
arg1 = ~0U; // Vector slot
arg2 = compile(++s0,ve1,depth1,0,is_single); // Index
arg3 = compile(s + 1,se,depth1,0,is_single); // Value to assign
_cimg_mp_check_type(arg3,2,1,0);

if (variable_name[1]) { // Multi-char variable
cimglist_for(variable_def,i) if (!std::strcmp(variable_name,variable_def[i])) {
arg1 = variable_pos[i]; break;
}
} else arg1 = reserved_label[(int)*variable_name]; // Single-char variable
if (arg1==~0U) compile(ss,s0 - 1,depth1,0,is_single); // Variable does not exist -> error
else { // Variable already exists
if (_cimg_mp_is_scalar(arg1)) compile(ss,s,depth1,0,is_single); // Variable is not a vector -> error
if (_cimg_mp_is_constant(arg2)) { // Constant index -> return corresponding variable slot directly
nb = (int)mem[arg2];
if (nb>=0 && nb<(int)_cimg_mp_size(arg1)) {
arg1+=nb + 1;
CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg3).move_to(code);
_cimg_mp_return(arg1);
}
compile(ss,s,depth1,0,is_single); // Out-of-bounds reference -> error
}

// Case of non-constant index -> return assigned value + linked reference
if (p_ref) {
*p_ref = 1;
p_ref[1] = arg1;
p_ref[2] = arg2;
if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2; // Prevent from being used in further optimization
if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
}
CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg3,arg1,(ulongT)_cimg_mp_size(arg1),
arg2,arg3).
move_to(code);
_cimg_mp_return(arg3);
}
}
}

// Assign user-defined macro.
if (l_variable_name>2 && *ve1==')' && *ss!='(') {
s0 = ve1; while (s0>ss && *s0!='(') --s0;
is_sth = std::strncmp(variable_name,"debug(",6) &&
std::strncmp(variable_name,"print(",6); // is_valid_function_name?
if (*ss>='0' && *ss<='9') is_sth = false;
else for (ns = ss; ns<s0; ++ns)
if (!is_varchar(*ns)) { is_sth = false; break; }

if (is_sth && s0>ss) { // Looks like a valid function declaration
s0 = variable_name._data + (s0 - ss);
*s0 = 0;
s1 = variable_name._data + l_variable_name - 1; // Pointer to closing parenthesis
CImg<charT>(variable_name._data,(unsigned int)(s0 - variable_name._data + 1)).move_to(macro_def,0);
++s; while (*s && cimg::is_blank(*s)) ++s;
CImg<charT>(s,(unsigned int)(se - s + 1)).move_to(macro_body,0);

p1 = 1; // Index of current parsed argument
for (s = s0 + 1; s<=s1; ++p1, s = ns + 1) { // Parse function arguments
if (p1>24) {
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Too much specified arguments (>24) in macro "
"definition '%s()', in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
while (*s && cimg::is_blank(*s)) ++s;
if (*s==')' && p1==1) break; // Function has no arguments

s2 = s; // Start of the argument name
is_sth = true; // is_valid_argument_name?
if (*s>='0' && *s<='9') is_sth = false;
else for (ns = s; ns<s1 && *ns!=',' && !cimg::is_blank(*ns); ++ns)
if (!is_varchar(*ns)) { is_sth = false; break; }
s3 = ns; // End of the argument name
while (*ns && cimg::is_blank(*ns)) ++ns;
if (!is_sth || s2==s3 || (*ns!=',' && ns!=s1)) {
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: %s name specified for argument %u when defining "
"macro '%s()', in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
is_sth?"Empty":"Invalid",p1,
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
if (ns==s1 || *ns==',') { // New argument found
*s3 = 0;
p2 = (unsigned int)(s3 - s2); // Argument length
for (ps = std::strstr(macro_body[0],s2); ps; ps = std::strstr(ps,s2)) { // Replace by arg number
if (!((ps>macro_body[0]._data && is_varchar(*(ps - 1))) ||
(ps + p2<macro_body[0].end() && is_varchar(*(ps + p2))))) {
if (ps>macro_body[0]._data && *(ps - 1)=='#') { // Remove pre-number sign
*(ps - 1) = (char)p1;
if (ps + p2<macro_body[0].end() && *(ps + p2)=='#') { // Has pre & post number signs
std::memmove(ps,ps + p2 + 1,macro_body[0].end() - ps - p2 - 1);
macro_body[0]._width-=p2 + 1;
} else { // Has pre number sign only
std::memmove(ps,ps + p2,macro_body[0].end() - ps - p2);
macro_body[0]._width-=p2;
}
} else if (ps + p2<macro_body[0].end() && *(ps + p2)=='#') { // Remove post-number sign
*(ps++) = (char)p1;
std::memmove(ps,ps + p2,macro_body[0].end() - ps - p2);
macro_body[0]._width-=p2;
} else { // Not near a number sign
if (p2<3) {
ps-=(ulongT)macro_body[0]._data;
macro_body[0].resize(macro_body[0]._width - p2 + 3,1,1,1,0);
ps+=(ulongT)macro_body[0]._data;
} else macro_body[0]._width-=p2 - 3;
std::memmove(ps + 3,ps + p2,macro_body[0].end() - ps - 3);
*(ps++) = '(';
*(ps++) = (char)p1;
*(ps++) = ')';
}
} else ++ps;
}
}
}

// Store number of arguments.
macro_def[0].resize(macro_def[0]._width + 1,1,1,1,0).back() = (char)(p1 - 1);

// Detect parts of function body inside a string.
is_inside_string(macro_body[0]).move_to(macro_body_is_string,0);
_cimg_mp_return_nan();
}
}

// Check if the variable name could be valid. If not, this is probably an lvalue assignment.
is_sth = true; // is_valid_variable_name?
const bool is_const = l_variable_name>6 && !std::strncmp(variable_name,"const ",6);

s0 = variable_name._data;
if (is_const) {
s0+=6; while (cimg::is_blank(*s0)) ++s0;
variable_name.resize(variable_name.end() - s0,1,1,1,0,0,1);
}

if (*variable_name>='0' && *variable_name<='9') is_sth = false;
else for (ns = variable_name._data; *ns; ++ns)
if (!is_varchar(*ns)) { is_sth = false; break; }

// Assign variable (direct).
if (is_sth) {
arg3 = variable_name[1]?~0U:*variable_name; // One-char variable
if (variable_name[1] && !variable_name[2]) { // Two-chars variable
c1 = variable_name[0];
c2 = variable_name[1];
if (c1=='w' && c2=='h') arg3 = 0; // wh
else if (c1=='p' && c2=='i') arg3 = 3; // pi
else if (c1=='i') {
if (c2>='0' && c2<='9') arg3 = 19 + c2 - '0'; // i0...i9
else if (c2=='m') arg3 = 4; // im
else if (c2=='M') arg3 = 5; // iM
else if (c2=='a') arg3 = 6; // ia
else if (c2=='v') arg3 = 7; // iv
else if (c2=='s') arg3 = 8; // is
else if (c2=='p') arg3 = 9; // ip
else if (c2=='c') arg3 = 10; // ic
} else if (c2=='m') {
if (c1=='x') arg3 = 11; // xm
else if (c1=='y') arg3 = 12; // ym
else if (c1=='z') arg3 = 13; // zm
else if (c1=='c') arg3 = 14; // cm
} else if (c2=='M') {
if (c1=='x') arg3 = 15; // xM
else if (c1=='y') arg3 = 16; // yM
else if (c1=='z') arg3 = 17; // zM
else if (c1=='c') arg3 = 18; // cM
}
} else if (variable_name[1] && variable_name[2] && !variable_name[3]) { // Three-chars variable
c1 = variable_name[0];
c2 = variable_name[1];
c3 = variable_name[2];
if (c1=='w' && c2=='h' && c3=='d') arg3 = 1; // whd
} else if (variable_name[1] && variable_name[2] && variable_name[3] &&
!variable_name[4]) { // Four-chars variable
c1 = variable_name[0];
c2 = variable_name[1];
c3 = variable_name[2];
c4 = variable_name[3];
if (c1=='w' && c2=='h' && c3=='d' && c4=='s') arg3 = 2; // whds
} else if (!std::strcmp(variable_name,"interpolation")) arg3 = 29; // interpolation
else if (!std::strcmp(variable_name,"boundary")) arg3 = 30; // boundary

arg1 = ~0U;
arg2 = compile(s + 1,se,depth1,0,is_single);
if (is_const) _cimg_mp_check_constant(arg2,2,0);

if (arg3!=~0U) // One-char variable, or variable in reserved_labels
arg1 = reserved_label[arg3];
else // Multi-char variable name : check for existing variable with same name
cimglist_for(variable_def,i)
if (!std::strcmp(variable_name,variable_def[i])) { arg1 = variable_pos[i]; break; }

if (arg1==~0U) { // Create new variable
if (_cimg_mp_is_vector(arg2)) { // Vector variable
arg1 = is_comp_vector(arg2)?arg2:vector_copy(arg2);
set_variable_vector(arg1);
} else { // Scalar variable
if (is_const) arg1 = arg2;
else {
arg1 = _cimg_mp_is_comp(arg2)?arg2:scalar1(mp_copy,arg2);
memtype[arg1] = -1;
}
}

if (arg3!=~0U) reserved_label[arg3] = arg1;
else {
if (variable_def._width>=variable_pos._width) variable_pos.resize(-200,1,1,1,0);
variable_pos[variable_def._width] = arg1;
variable_name.move_to(variable_def);
}

} else { // Variable already exists -> assign a new value
if (is_const || _cimg_mp_is_constant(arg1)) {
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Invalid assignment of %sconst variable '%s'%s, "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
_cimg_mp_is_constant(arg1)?"already-defined ":"non-",
variable_name._data,
!_cimg_mp_is_constant(arg1) && is_const?" as a new const variable":"",
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
_cimg_mp_check_type(arg2,2,_cimg_mp_is_vector(arg1)?3:1,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1)) { // Vector
if (_cimg_mp_is_vector(arg2)) // From vector
CImg<ulongT>::vector((ulongT)mp_vector_copy,arg1,arg2,(ulongT)_cimg_mp_size(arg1)).
move_to(code);
else // From scalar
CImg<ulongT>::vector((ulongT)mp_vector_init,arg1,1,(ulongT)_cimg_mp_size(arg1),arg2).
move_to(code);
} else // Scalar
CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg2).move_to(code);
}
_cimg_mp_return(arg1);
}

// Assign lvalue (variable name was not valid for a direct assignment).
arg1 = ~0U;
is_sth = (bool)std::strchr(variable_name,'?'); // Contains_ternary_operator?
if (is_sth) break; // Do nothing and make ternary operator prioritary over assignment

if (l_variable_name>2 && (std::strchr(variable_name,'(') || std::strchr(variable_name,'['))) {
ref.assign(7);
arg1 = compile(ss,s,depth1,ref,is_single); // Lvalue slot
arg2 = compile(s + 1,se,depth1,0,is_single); // Value to assign

if (*ref==1) { // Vector value (scalar): V[k] = scalar
_cimg_mp_check_type(arg2,2,1,0);
arg3 = ref[1]; // Vector slot
arg4 = ref[2]; // Index
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg2,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg2).
move_to(code);
_cimg_mp_return(arg2);
}

if (*ref==2) { // Image value (scalar): i/j[_#ind,off] = scalar
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,1,0);
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg2);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
arg2,p1,arg3).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg2);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
arg2,arg3).move_to(code);
}
_cimg_mp_return(arg2);
}

if (*ref==3) { // Image value (scalar): i/j(_#ind,_x,_y,_z,_c) = scalar
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,1,0);
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
arg6 = ref[6]; // C
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg2);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
arg2,p1,arg3,arg4,arg5,arg6).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg2);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
arg2,arg3,arg4,arg5,arg6).move_to(code);
}
_cimg_mp_return(arg2);
}

if (*ref==4) { // Image value (vector): I/J[_#ind,off] = value
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg2);
if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_s:mp_list_set_Ioff_s),
arg2,p1,arg3).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
arg2,p1,arg3,_cimg_mp_size(arg2)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg2);
if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_s:mp_set_Ioff_s),
arg2,arg3).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
arg2,arg3,_cimg_mp_size(arg2)).move_to(code);
}
_cimg_mp_return(arg2);
}

if (*ref==5) { // Image value (vector): I/J(_#ind,_x,_y,_z,_c) = value
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg2);
if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_s:mp_list_set_Ixyz_s),
arg2,p1,arg3,arg4,arg5).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
arg2,p1,arg3,arg4,arg5,_cimg_mp_size(arg2)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg2);
if (_cimg_mp_is_scalar(arg2))
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_s:mp_set_Ixyz_s),
arg2,arg3,arg4,arg5).move_to(code);
else
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
arg2,arg3,arg4,arg5,_cimg_mp_size(arg2)).move_to(code);
}
_cimg_mp_return(arg2);
}

if (_cimg_mp_is_vector(arg1)) { // Vector variable: V = value
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg2)) // From vector
CImg<ulongT>::vector((ulongT)mp_vector_copy,arg1,arg2,(ulongT)_cimg_mp_size(arg1)).
move_to(code);
else // From scalar
CImg<ulongT>::vector((ulongT)mp_vector_init,arg1,1,(ulongT)_cimg_mp_size(arg1),arg2).
move_to(code);
_cimg_mp_return(arg1);
}

if (_cimg_mp_is_variable(arg1)) { // Scalar variable: s = scalar
_cimg_mp_check_type(arg2,2,1,0);
CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg2).move_to(code);
_cimg_mp_return(arg1);
}
}

// No assignment expressions match -> error
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Invalid %slvalue '%s', "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
arg1!=~0U && _cimg_mp_is_constant(arg1)?"const ":"",
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}

// Apply unary/binary/ternary operators. The operator precedences should be the same as in C++.
for (s = se2, ps = se3, ns = ps - 1; s>ss1; --s, --ps, --ns) // Here, ns = ps - 1
if (*s=='=' && (*ps=='*' || *ps=='/' || *ps=='^') && *ns==*ps &&
level[s - expr._data]==clevel) { // Self-operators for complex numbers only (**=,//=,^^=)
_cimg_mp_op(*ps=='*'?"Operator '**='":*ps=='/'?"Operator '//='":"Operator '^^='");

ref.assign(7);
arg1 = compile(ss,ns,depth1,ref,is_single); // Vector slot
arg2 = compile(s + 1,se,depth1,0,is_single); // Right operand
_cimg_mp_check_type(arg1,1,2,2);
_cimg_mp_check_type(arg2,2,3,2);
if (_cimg_mp_is_vector(arg2)) { // Complex **= complex
if (*ps=='*')
CImg<ulongT>::vector((ulongT)mp_complex_mul,arg1,arg1,arg2).move_to(code);
else if (*ps=='/')
CImg<ulongT>::vector((ulongT)mp_complex_div_vv,arg1,arg1,arg2).move_to(code);
else
CImg<ulongT>::vector((ulongT)mp_complex_pow_vv,arg1,arg1,arg2).move_to(code);
} else { // Complex **= scalar
if (*ps=='*') {
if (arg2==1) _cimg_mp_return(arg1);
self_vector_s(arg1,mp_self_mul,arg2);
} else if (*ps=='/') {
if (arg2==1) _cimg_mp_return(arg1);
self_vector_s(arg1,mp_self_div,arg2);
} else {
if (arg2==1) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)mp_complex_pow_vs,arg1,arg1,arg2).move_to(code);
}
}

// Write computed value back in image if necessary.
if (*ref==4) { // Image value (vector): I/J[_#ind,off] **= value
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
}

} else if (*ref==5) { // Image value (vector): I/J(_#ind,_x,_y,_z,_c) **= value
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
}
}

_cimg_mp_return(arg1);
}

for (s = se2, ps = se3, ns = ps - 1; s>ss1; --s, --ps, --ns) // Here, ns = ps - 1
if (*s=='=' && (*ps=='+' || *ps=='-' || *ps=='*' || *ps=='/' || *ps=='%' ||
*ps=='&' || *ps=='^' || *ps=='|' ||
(*ps=='>' && *ns=='>') || (*ps=='<' && *ns=='<')) &&
level[s - expr._data]==clevel) { // Self-operators (+=,-=,*=,/=,%=,>>=,<<=,&=,^=,|=)
switch (*ps) {
case '+' : op = mp_self_add; _cimg_mp_op("Operator '+='"); break;
case '-' : op = mp_self_sub; _cimg_mp_op("Operator '-='"); break;
case '*' : op = mp_self_mul; _cimg_mp_op("Operator '*='"); break;
case '/' : op = mp_self_div; _cimg_mp_op("Operator '/='"); break;
case '%' : op = mp_self_modulo; _cimg_mp_op("Operator '%='"); break;
case '<' : op = mp_self_bitwise_left_shift; _cimg_mp_op("Operator '<<='"); break;
case '>' : op = mp_self_bitwise_right_shift; _cimg_mp_op("Operator '>>='"); break;
case '&' : op = mp_self_bitwise_and; _cimg_mp_op("Operator '&='"); break;
case '|' : op = mp_self_bitwise_or; _cimg_mp_op("Operator '|='"); break;
default : op = mp_self_pow; _cimg_mp_op("Operator '^='"); break;
}
s1 = *ps=='>' || *ps=='<'?ns:ps;

ref.assign(7);
arg1 = compile(ss,s1,depth1,ref,is_single); // Variable slot
arg2 = compile(s + 1,se,depth1,0,is_single); // Value to apply

// Check for particular case to be simplified.
if ((op==mp_self_add || op==mp_self_sub) && !arg2) _cimg_mp_return(arg1);
if ((op==mp_self_mul || op==mp_self_div) && arg2==1) _cimg_mp_return(arg1);

// Apply operator on a copy to prevent modifying a constant or a variable.
if (*ref && (_cimg_mp_is_constant(arg1) || _cimg_mp_is_vector(arg1) || _cimg_mp_is_variable(arg1))) {
if (_cimg_mp_is_vector(arg1)) arg1 = vector_copy(arg1);
else arg1 = scalar1(mp_copy,arg1);
}

if (*ref==1) { // Vector value (scalar): V[k] += scalar
_cimg_mp_check_type(arg2,2,1,0);
arg3 = ref[1]; // Vector slot
arg4 = ref[2]; // Index
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg1,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg1).
move_to(code);
_cimg_mp_return(arg1);
}

if (*ref==2) { // Image value (scalar): i/j[_#ind,off] += scalar
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,1,0);
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
arg1,p1,arg3).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
arg1,arg3).move_to(code);
}
_cimg_mp_return(arg1);
}

if (*ref==3) { // Image value (scalar): i/j(_#ind,_x,_y,_z,_c) += scalar
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,1,0);
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
arg6 = ref[6]; // C
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
arg1,p1,arg3,arg4,arg5,arg6).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
arg1,arg3,arg4,arg5,arg6).move_to(code);
}
_cimg_mp_return(arg1);
}

if (*ref==4) { // Image value (vector): I/J[_#ind,off] += value
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (_cimg_mp_is_scalar(arg2)) self_vector_s(arg1,op,arg2); else self_vector_v(arg1,op,arg2);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
}
_cimg_mp_return(arg1);
}

if (*ref==5) { // Image value (vector): I/J(_#ind,_x,_y,_z,_c) += value
if (!is_single) is_parallelizable = false;
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
if (_cimg_mp_is_scalar(arg2)) self_vector_s(arg1,op,arg2); else self_vector_v(arg1,op,arg2);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(arg1);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
}
_cimg_mp_return(arg1);
}

if (_cimg_mp_is_vector(arg1)) { // Vector variable: V += value
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg2)) self_vector_v(arg1,op,arg2); // Vector += vector
else self_vector_s(arg1,op,arg2); // Vector += scalar
_cimg_mp_return(arg1);
}

if (_cimg_mp_is_variable(arg1)) { // Scalar variable: s += scalar
_cimg_mp_check_type(arg2,2,1,0);
CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
_cimg_mp_return(arg1);
}

variable_name.assign(ss,(unsigned int)(s - ss)).back() = 0;
cimg::strpare(variable_name,false,true);
*se = saved_char;
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Invalid %slvalue '%s', "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
_cimg_mp_is_constant(arg1)?"const ":"",
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}

for (s = ss1; s<se1; ++s)
if (*s=='?' && level[s - expr._data]==clevel) { // Ternary operator 'cond?expr1:expr2'
_cimg_mp_op("Operator '?:'");
s1 = s + 1; while (s1<se1 && (*s1!=':' || level[s1 - expr._data]!=clevel)) ++s1;
arg1 = compile(ss,s,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,1,0);
if (_cimg_mp_is_constant(arg1)) {
if ((bool)mem[arg1]) return compile(s + 1,*s1!=':'?se:s1,depth1,0,is_single);
else return *s1!=':'?0:compile(++s1,se,depth1,0,is_single);
}
p2 = code._width;
arg2 = compile(s + 1,*s1!=':'?se:s1,depth1,0,is_single);
p3 = code._width;
arg3 = *s1==':'?compile(++s1,se,depth1,0,is_single):
_cimg_mp_is_vector(arg2)?vector(_cimg_mp_size(arg2),0):0;
_cimg_mp_check_type(arg3,3,_cimg_mp_is_vector(arg2)?2:1,_cimg_mp_size(arg2));
arg4 = _cimg_mp_size(arg2);
if (arg4) pos = vector(arg4); else pos = scalar();
CImg<ulongT>::vector((ulongT)mp_if,pos,arg1,arg2,arg3,
p3 - p2,code._width - p3,arg4).move_to(code,p2);
_cimg_mp_return(pos);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='|' && *ns=='|' && level[s - expr._data]==clevel) { // Logical or ('||')
_cimg_mp_op("Operator '||'");
arg1 = compile(ss,s,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,1,0);
if (arg1>0 && arg1<=16) _cimg_mp_return(1);
p2 = code._width;
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,1,0);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant(mem[arg1] || mem[arg2]);
if (!arg1) _cimg_mp_return(arg2);
pos = scalar();
CImg<ulongT>::vector((ulongT)mp_logical_or,pos,arg1,arg2,code._width - p2).
move_to(code,p2);
_cimg_mp_return(pos);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='&' && *ns=='&' && level[s - expr._data]==clevel) { // Logical and ('&&')
_cimg_mp_op("Operator '&&'");
arg1 = compile(ss,s,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,1,0);
if (!arg1) _cimg_mp_return(0);
p2 = code._width;
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,1,0);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant(mem[arg1] && mem[arg2]);
if (arg1>0 && arg1<=16) _cimg_mp_return(arg2);
pos = scalar();
CImg<ulongT>::vector((ulongT)mp_logical_and,pos,arg1,arg2,code._width - p2).
move_to(code,p2);
_cimg_mp_return(pos);
}

for (s = se2; s>ss; --s)
if (*s=='|' && level[s - expr._data]==clevel) { // Bitwise or ('|')
_cimg_mp_op("Operator '|'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_bitwise_or,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
if (!arg2) _cimg_mp_return(arg1);
_cimg_mp_vector2_vs(mp_bitwise_or,arg1,arg2);
}
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
if (!arg1) _cimg_mp_return(arg2);
_cimg_mp_vector2_sv(mp_bitwise_or,arg1,arg2);
}
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant((longT)mem[arg1] | (longT)mem[arg2]);
if (!arg2) _cimg_mp_return(arg1);
if (!arg1) _cimg_mp_return(arg2);
_cimg_mp_scalar2(mp_bitwise_or,arg1,arg2);
}

for (s = se2; s>ss; --s)
if (*s=='&' && level[s - expr._data]==clevel) { // Bitwise and ('&')
_cimg_mp_op("Operator '&'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_bitwise_and,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_bitwise_and,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_bitwise_and,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant((longT)mem[arg1] & (longT)mem[arg2]);
if (!arg1 || !arg2) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_bitwise_and,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='!' && *ns=='=' && level[s - expr._data]==clevel) { // Not equal to ('!=')
_cimg_mp_op("Operator '!='");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
if (arg1==arg2) _cimg_mp_return(0);
p1 = _cimg_mp_size(arg1);
p2 = _cimg_mp_size(arg2);
if (p1 || p2) {
if (p1 && p2 && p1!=p2) _cimg_mp_return(1);
pos = scalar();
CImg<ulongT>::vector((ulongT)mp_vector_neq,pos,arg1,p1,arg2,p2,11,1).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]!=mem[arg2]);
_cimg_mp_scalar2(mp_neq,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='=' && *ns=='=' && level[s - expr._data]==clevel) { // Equal to ('==')
_cimg_mp_op("Operator '=='");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
if (arg1==arg2) _cimg_mp_return(1);
p1 = _cimg_mp_size(arg1);
p2 = _cimg_mp_size(arg2);
if (p1 || p2) {
if (p1 && p2 && p1!=p2) _cimg_mp_return(0);
pos = scalar();
CImg<ulongT>::vector((ulongT)mp_vector_eq,pos,arg1,p1,arg2,p2,11,1).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]==mem[arg2]);
_cimg_mp_scalar2(mp_eq,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='<' && *ns=='=' && level[s - expr._data]==clevel) { // Less or equal than ('<=')
_cimg_mp_op("Operator '<='");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_lte,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_lte,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_lte,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]<=mem[arg2]);
if (arg1==arg2) _cimg_mp_return(1);
_cimg_mp_scalar2(mp_lte,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='>' && *ns=='=' && level[s - expr._data]==clevel) { // Greater or equal than ('>=')
_cimg_mp_op("Operator '>='");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_gte,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_gte,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_gte,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]>=mem[arg2]);
if (arg1==arg2) _cimg_mp_return(1);
_cimg_mp_scalar2(mp_gte,arg1,arg2);
}

for (s = se2, ns = se1, ps = se3; s>ss; --s, --ns, --ps)
if (*s=='<' && *ns!='<' && *ps!='<' && level[s - expr._data]==clevel) { // Less than ('<')
_cimg_mp_op("Operator '<'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_lt,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_lt,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_lt,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]<mem[arg2]);
if (arg1==arg2) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_lt,arg1,arg2);
}

for (s = se2, ns = se1, ps = se3; s>ss; --s, --ns, --ps)
if (*s=='>' && *ns!='>' && *ps!='>' && level[s - expr._data]==clevel) { // Greather than ('>')
_cimg_mp_op("Operator '>'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_gt,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_gt,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_gt,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]>mem[arg2]);
if (arg1==arg2) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_gt,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='<' && *ns=='<' && level[s - expr._data]==clevel) { // Left bit shift ('<<')
_cimg_mp_op("Operator '<<'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2))
_cimg_mp_vector2_vv(mp_bitwise_left_shift,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
if (!arg2) _cimg_mp_return(arg1);
_cimg_mp_vector2_vs(mp_bitwise_left_shift,arg1,arg2);
}
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2))
_cimg_mp_vector2_sv(mp_bitwise_left_shift,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant((longT)mem[arg1]<<(unsigned int)mem[arg2]);
if (!arg1) _cimg_mp_return(0);
if (!arg2) _cimg_mp_return(arg1);
_cimg_mp_scalar2(mp_bitwise_left_shift,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='>' && *ns=='>' && level[s - expr._data]==clevel) { // Right bit shift ('>>')
_cimg_mp_op("Operator '>>'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2))
_cimg_mp_vector2_vv(mp_bitwise_right_shift,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
if (!arg2) _cimg_mp_return(arg1);
_cimg_mp_vector2_vs(mp_bitwise_right_shift,arg1,arg2);
}
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2))
_cimg_mp_vector2_sv(mp_bitwise_right_shift,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant((longT)mem[arg1]>>(unsigned int)mem[arg2]);
if (!arg1) _cimg_mp_return(0);
if (!arg2) _cimg_mp_return(arg1);
_cimg_mp_scalar2(mp_bitwise_right_shift,arg1,arg2);
}

for (ns = se1, s = se2, ps = pexpr._data + (se3 - expr._data); s>ss; --ns, --s, --ps)
if (*s=='+' && (*ns!='+' || ns!=se1) && *ps!='-' && *ps!='+' && *ps!='*' && *ps!='/' && *ps!='%' &&
*ps!='&' && *ps!='|' && *ps!='^' && *ps!='!' && *ps!='~' && *ps!='#' &&
(*ps!='e' || !(ps - pexpr._data>ss - expr._data && (*(ps - 1)=='.' || (*(ps - 1)>='0' &&
*(ps - 1)<='9')))) &&
level[s - expr._data]==clevel) { // Addition ('+')
_cimg_mp_op("Operator '+'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (!arg2) _cimg_mp_return(arg1);
if (!arg1) _cimg_mp_return(arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_add,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_add,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_add,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1] + mem[arg2]);
if (code) { // Try to spot linear case 'a*b + c'
CImg<ulongT> &pop = code.back();
if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
arg3 = (unsigned int)pop[1];
arg4 = (unsigned int)pop[2];
arg5 = (unsigned int)pop[3];
code.remove();
CImg<ulongT>::vector((ulongT)mp_linear_add,arg3,arg4,arg5,arg3==arg2?arg1:arg2).move_to(code);
_cimg_mp_return(arg3);
}
}
if (arg2==1) _cimg_mp_scalar1(mp_increment,arg1);
if (arg1==1) _cimg_mp_scalar1(mp_increment,arg2);
_cimg_mp_scalar2(mp_add,arg1,arg2);
}

for (ns = se1, s = se2, ps = pexpr._data + (se3 - expr._data); s>ss; --ns, --s, --ps)
if (*s=='-' && (*ns!='-' || ns!=se1) && *ps!='-' && *ps!='+' && *ps!='*' && *ps!='/' && *ps!='%' &&
*ps!='&' && *ps!='|' && *ps!='^' && *ps!='!' && *ps!='~' && *ps!='#' &&
(*ps!='e' || !(ps - pexpr._data>ss - expr._data && (*(ps - 1)=='.' || (*(ps - 1)>='0' &&
*(ps - 1)<='9')))) &&
level[s - expr._data]==clevel) { // Subtraction ('-')
_cimg_mp_op("Operator '-'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (!arg2) _cimg_mp_return(arg1);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_sub,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_sub,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
if (!arg1) _cimg_mp_vector1_v(mp_minus,arg2);
_cimg_mp_vector2_sv(mp_sub,arg1,arg2);
}
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1] - mem[arg2]);
if (!arg1) _cimg_mp_scalar1(mp_minus,arg2);
if (code) { // Try to spot linear cases 'a*b - c' and 'c - a*b'
CImg<ulongT> &pop = code.back();
if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
arg3 = (unsigned int)pop[1];
arg4 = (unsigned int)pop[2];
arg5 = (unsigned int)pop[3];
code.remove();
CImg<ulongT>::vector((ulongT)(arg3==arg1?mp_linear_sub_left:mp_linear_sub_right),
arg3,arg4,arg5,arg3==arg1?arg2:arg1).move_to(code);
_cimg_mp_return(arg3);
}
}
if (arg2==1) _cimg_mp_scalar1(mp_decrement,arg1);
_cimg_mp_scalar2(mp_sub,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='*' && *ns=='*' && level[s - expr._data]==clevel) { // Complex multiplication ('**')
_cimg_mp_op("Operator '**'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,3,2);
_cimg_mp_check_type(arg2,2,3,2);
if (arg2==1) _cimg_mp_return(arg1);
if (arg1==1) _cimg_mp_return(arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_mul,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_mul,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_mul,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]*mem[arg2]);
if (!arg1 || !arg2) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_mul,arg1,arg2);
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='/' && *ns=='/' && level[s - expr._data]==clevel) { // Complex division ('//')
_cimg_mp_op("Operator '//'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,3,2);
_cimg_mp_check_type(arg2,2,3,2);
if (arg2==1) _cimg_mp_return(arg1);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_div_vv,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_div_sv,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]/mem[arg2]);
if (!arg1) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_div,arg1,arg2);
}

for (s = se2; s>ss; --s) if (*s=='*' && level[s - expr._data]==clevel) { // Multiplication ('*')
_cimg_mp_op("Operator '*'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
p2 = _cimg_mp_size(arg2);
if (p2>0 && _cimg_mp_size(arg1)==p2*p2) { // Particular case of matrix multiplication
pos = vector(p2);
CImg<ulongT>::vector((ulongT)mp_matrix_mul,pos,arg1,arg2,p2,p2,1).move_to(code);
_cimg_mp_return(pos);
}
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (arg2==1) _cimg_mp_return(arg1);
if (arg1==1) _cimg_mp_return(arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_mul,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_mul,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_mul,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]*mem[arg2]);

if (code) { // Try to spot double multiplication 'a*b*c'
CImg<ulongT> &pop = code.back();
if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
arg3 = (unsigned int)pop[1];
arg4 = (unsigned int)pop[2];
arg5 = (unsigned int)pop[3];
code.remove();
CImg<ulongT>::vector((ulongT)mp_mul2,arg3,arg4,arg5,arg3==arg2?arg1:arg2).move_to(code);
_cimg_mp_return(arg3);
}
}
if (!arg1 || !arg2) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_mul,arg1,arg2);
}

for (s = se2; s>ss; --s) if (*s=='/' && level[s - expr._data]==clevel) { // Division ('/')
_cimg_mp_op("Operator '/'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (arg2==1) _cimg_mp_return(arg1);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_div,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_div,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]/mem[arg2]);
if (!arg1) _cimg_mp_return(0);
_cimg_mp_scalar2(mp_div,arg1,arg2);
}

for (s = se2, ns = se1; s>ss; --s, --ns)
if (*s=='%' && *ns!='^' && level[s - expr._data]==clevel) { // Modulo ('%')
_cimg_mp_op("Operator '%'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_modulo,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_modulo,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_modulo,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant(cimg::mod(mem[arg1],mem[arg2]));
_cimg_mp_scalar2(mp_modulo,arg1,arg2);
}

if (se1>ss) {
if (*ss=='+' && (*ss1!='+' || (ss2<se && *ss2>='0' && *ss2<='9'))) { // Unary plus ('+')
_cimg_mp_op("Operator '+'");
_cimg_mp_return(compile(ss1,se,depth1,0,is_single));
}

if (*ss=='-' && (*ss1!='-' || (ss2<se && *ss2>='0' && *ss2<='9'))) { // Unary minus ('-')
_cimg_mp_op("Operator '-'");
arg1 = compile(ss1,se,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_minus,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(-mem[arg1]);
_cimg_mp_scalar1(mp_minus,arg1);
}

if (*ss=='!') { // Logical not ('!')
_cimg_mp_op("Operator '!'");
if (*ss1=='!') { // '!!expr' optimized as 'bool(expr)'
arg1 = compile(ss2,se,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bool,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant((bool)mem[arg1]);
_cimg_mp_scalar1(mp_bool,arg1);
}
arg1 = compile(ss1,se,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_logical_not,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(!mem[arg1]);
_cimg_mp_scalar1(mp_logical_not,arg1);
}

if (*ss=='~') { // Bitwise not ('~')
_cimg_mp_op("Operator '~'");
arg1 = compile(ss1,se,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bitwise_not,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(~(unsigned int)mem[arg1]);
_cimg_mp_scalar1(mp_bitwise_not,arg1);
}
}

for (s = se3, ns = se2; s>ss; --s, --ns)
if (*s=='^' && *ns=='^' && level[s - expr._data]==clevel) { // Complex power ('^^')
_cimg_mp_op("Operator '^^'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 2,se,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,3,2);
_cimg_mp_check_type(arg2,2,3,2);
if (arg2==1) _cimg_mp_return(arg1);
pos = vector(2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
CImg<ulongT>::vector((ulongT)mp_complex_pow_vv,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
CImg<ulongT>::vector((ulongT)mp_complex_pow_vs,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
CImg<ulongT>::vector((ulongT)mp_complex_pow_sv,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}
CImg<ulongT>::vector((ulongT)mp_complex_pow_ss,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}

for (s = se2; s>ss; --s)
if (*s=='^' && level[s - expr._data]==clevel) { // Power ('^')
_cimg_mp_op("Operator '^'");
arg1 = compile(ss,s,depth1,0,is_single);
arg2 = compile(s + 1,se,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (arg2==1) _cimg_mp_return(arg1);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_pow,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_pow,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_pow,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant(std::pow(mem[arg1],mem[arg2]));
switch (arg2) {
case 0 : _cimg_mp_return(1);
case 2 : _cimg_mp_scalar1(mp_sqr,arg1);
case 3 : _cimg_mp_scalar1(mp_pow3,arg1);
case 4 : _cimg_mp_scalar1(mp_pow4,arg1);
default :
if (_cimg_mp_is_constant(arg2)) {
if (mem[arg2]==0.5) { _cimg_mp_scalar1(mp_sqrt,arg1); }
else if (mem[arg2]==0.25) { _cimg_mp_scalar1(mp_pow0_25,arg1); }
}
_cimg_mp_scalar2(mp_pow,arg1,arg2);
}
}

// Percentage computation.
if (*se1=='%') {
arg1 = compile(ss,se1,depth1,0,is_single);
arg2 = _cimg_mp_is_constant(arg1)?0:constant(100);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(mem[arg1]/100);
_cimg_mp_scalar2(mp_div,arg1,arg2);
}

is_sth = ss1<se1 && (*ss=='+' || *ss=='-') && *ss1==*ss; // is pre-?
if (is_sth || (se2>ss && (*se1=='+' || *se1=='-') && *se2==*se1)) { // Pre/post-decrement and increment
if ((is_sth && *ss=='+') || (!is_sth && *se1=='+')) {
_cimg_mp_op("Operator '++'");
op = mp_self_increment;
} else {
_cimg_mp_op("Operator '--'");
op = mp_self_decrement;
}
ref.assign(7);
arg1 = is_sth?compile(ss2,se,depth1,ref,is_single):
compile(ss,se2,depth1,ref,is_single); // Variable slot

// Apply operator on a copy to prevent modifying a constant or a variable.
if (*ref && (_cimg_mp_is_constant(arg1) || _cimg_mp_is_vector(arg1) || _cimg_mp_is_variable(arg1))) {
if (_cimg_mp_is_vector(arg1)) arg1 = vector_copy(arg1);
else arg1 = scalar1(mp_copy,arg1);
}

if (is_sth) pos = arg1; // Determine return index, depending on pre/post action
else {
if (_cimg_mp_is_vector(arg1)) pos = vector_copy(arg1);
else pos = scalar1(mp_copy,arg1);
}

if (*ref==1) { // Vector value (scalar): V[k]++
arg3 = ref[1]; // Vector slot
arg4 = ref[2]; // Index
if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1,1).move_to(code);
CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg1,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg1).
move_to(code);
_cimg_mp_return(pos);
}

if (*ref==2) { // Image value (scalar): i/j[_#ind,off]++
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
arg1,p1,arg3).move_to(code);
} else {
if (!imgout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
arg1,arg3).move_to(code);
}
_cimg_mp_return(pos);
}

if (*ref==3) { // Image value (scalar): i/j(_#ind,_x,_y,_z,_c)++
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
arg6 = ref[6]; // C
if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
arg1,p1,arg3,arg4,arg5,arg6).move_to(code);
} else {
if (!imgout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
arg1,arg3,arg4,arg5,arg6).move_to(code);
}
_cimg_mp_return(pos);
}

if (*ref==4) { // Image value (vector): I/J[_#ind,off]++
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // Offset
if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
}
_cimg_mp_return(pos);
}

if (*ref==5) { // Image value (vector): I/J(_#ind,_x,_y,_z,_c)++
if (!is_single) is_parallelizable = false;
p1 = ref[1]; // Index
is_relative = (bool)ref[2];
arg3 = ref[3]; // X
arg4 = ref[4]; // Y
arg5 = ref[5]; // Z
if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
if (p1!=~0U) {
if (!listout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
} else {
if (!imgout) _cimg_mp_return(pos);
CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
}
_cimg_mp_return(pos);
}

if (_cimg_mp_is_vector(arg1)) { // Vector variable: V++
self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
_cimg_mp_return(pos);
}

if (_cimg_mp_is_variable(arg1)) { // Scalar variable: s++
CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
_cimg_mp_return(pos);
}

if (is_sth) variable_name.assign(ss2,(unsigned int)(se - ss1));
else variable_name.assign(ss,(unsigned int)(se1 - ss));
variable_name.back() = 0;
cimg::strpare(variable_name,false,true);
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Invalid %slvalue '%s', "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
_cimg_mp_is_constant(arg1)?"const ":"",
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}

// Array-like access to vectors and  image values 'i/j/I/J[_#ind,offset,_boundary]' and 'vector[offset]'.
if (*se1==']' && *ss!='[') {
_cimg_mp_op("Value accessor '[]'");
is_relative = *ss=='j' || *ss=='J';
s0 = s1 = std::strchr(ss,'['); if (s0) { do { --s1; } while (cimg::is_blank(*s1)); cimg::swap(*s0,*++s1); }

if ((*ss=='I' || *ss=='J') && *ss1=='[' &&
(reserved_label[(int)*ss]==~0U ||
!_cimg_mp_is_vector(reserved_label[(int)*ss]))) { // Image value as a vector
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
_cimg_mp_check_list(false);
} else { p1 = ~0U; s0 = ss2; }
s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
p2 = 1 + (p1!=~0U);
arg1 = compile(s0,s1,depth1,0,is_single); // Offset
_cimg_mp_check_type(arg1,p2,1,0);
arg2 = ~0U;
if (s1<se1) {
arg2 = compile(++s1,se1,depth1,0,is_single); // Boundary
_cimg_mp_check_type(arg2,p2 + 1,1,0);
}
if (p_ref && arg2==~0U) {
*p_ref = 4;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2; // Prevent from being used in further optimization
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
}
p2 = ~0U; // 'p2' must be the dimension of the vector-valued operand if any
if (p1==~0U) p2 = imgin._spectrum;
else if (_cimg_mp_is_constant(p1)) {
p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
p2 = listin[p3]._spectrum;
}
if (!p2) _cimg_mp_return(0);
pos = vector(p2);
if (p1!=~0U) {
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_Joff:mp_list_Ioff),
pos,p1,arg1,arg2==~0U?_cimg_mp_boundary:arg2,p2).move_to(code);
} else {
need_input_copy = true;
CImg<ulongT>::vector((ulongT)(is_relative?mp_Joff:mp_Ioff),
pos,arg1,arg2==~0U?_cimg_mp_boundary:arg2,p2).move_to(code);
}
_cimg_mp_return(pos);
}

if ((*ss=='i' || *ss=='j') && *ss1=='[' &&
(reserved_label[(int)*ss]==~0U ||
!_cimg_mp_is_vector(reserved_label[(int)*ss]))) { // Image value as a scalar
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
} else { p1 = ~0U; s0 = ss2; }
s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(s0,s1,depth1,0,is_single); // Offset
arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):~0U; // Boundary
if (p_ref && arg2==~0U) {
*p_ref = 2;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2; // Prevent from being used in further optimization
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
}
if (p1!=~0U) {
if (!listin) _cimg_mp_return(0);
pos = scalar3(is_relative?mp_list_joff:mp_list_ioff,p1,arg1,arg2==~0U?_cimg_mp_boundary:arg2);
} else {
if (!imgin) _cimg_mp_return(0);
need_input_copy = true;
pos = scalar2(is_relative?mp_joff:mp_ioff,arg1,arg2==~0U?_cimg_mp_boundary:arg2);
}
memtype[pos] = -2; // Prevent from being used in further optimization
_cimg_mp_return(pos);
}

s0 = se1; while (s0>ss && (*s0!='[' || level[s0 - expr._data]!=clevel)) --s0;
if (s0>ss) { // Vector value
arg1 = compile(ss,s0,depth1,0,is_single);
if (_cimg_mp_is_scalar(arg1)) {
variable_name.assign(ss,(unsigned int)(s0 - ss + 1)).back() = 0;
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Array brackets used on non-vector variable '%s', "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
variable_name._data,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");

}
s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;

if (s1<se1) { // Two or three arguments -> sub-vector extraction
p1 = _cimg_mp_size(arg1);
arg2 = compile(++s0,s1,depth1,0,is_single); // Starting index
s0 = ++s1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
arg3 = compile(s1,s0,depth1,0,is_single); // Length
arg4 = s0<se1?compile(++s0,se1,depth1,0,is_single):1; // Step
_cimg_mp_check_constant(arg3,2,3);
arg3 = (unsigned int)mem[arg3];
pos = vector(arg3);
CImg<ulongT>::vector((ulongT)mp_vector_crop,pos,arg1,p1,arg2,arg3,arg4).move_to(code);
_cimg_mp_return(pos);
}

// One argument -> vector value reference
arg2 = compile(++s0,se1,depth1,0,is_single);
if (_cimg_mp_is_constant(arg2)) { // Constant index
nb = (int)mem[arg2];
if (nb>=0 && nb<(int)_cimg_mp_size(arg1)) _cimg_mp_return(arg1 + 1 + nb);
variable_name.assign(ss,(unsigned int)(s0 - ss)).back() = 0;
*se = saved_char;
cimg::strellipsize(variable_name,64);
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: Out-of-bounds reference '%s[%d]' "
"(vector '%s' has dimension %u), "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,
variable_name._data,nb,
variable_name._data,_cimg_mp_size(arg1),
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
if (p_ref) {
*p_ref = 1;
p_ref[1] = arg1;
p_ref[2] = arg2;
if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2; // Prevent from being used in further optimization
}
pos = scalar3(mp_vector_off,arg1,_cimg_mp_size(arg1),arg2);
memtype[pos] = -2; // Prevent from being used in further optimization
_cimg_mp_return(pos);
}
}

// Look for a function call, an access to image value, or a parenthesis.
if (*se1==')') {
if (*ss=='(') _cimg_mp_return(compile(ss1,se1,depth1,p_ref,is_single)); // Simple parentheses
_cimg_mp_op("Value accessor '()'");
is_relative = *ss=='j' || *ss=='J';
s0 = s1 = std::strchr(ss,'('); if (s0) { do { --s1; } while (cimg::is_blank(*s1)); cimg::swap(*s0,*++s1); }

// I/J(_#ind,_x,_y,_z,_interpolation,_boundary_conditions)
if ((*ss=='I' || *ss=='J') && *ss1=='(') { // Image value as scalar
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
_cimg_mp_check_list(false);
} else { p1 = ~0U; s0 = ss2; }
arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
arg4 = arg5 = ~0U;
if (s0<se1) {
s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(s0,s1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) { // Coordinates specified as a vector
p2 = _cimg_mp_size(arg1);
++arg1;
if (p2>1) {
arg2 = arg1 + 1;
if (p2>2) arg3 = arg2 + 1;
}
if (s1<se1) {
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg4 = compile(s1,s2,depth1,0,is_single);
arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
}
} else if (s1<se1) {
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1,s2,depth1,0,is_single);
if (s2<se1) {
s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg3 = compile(s2,s3,depth1,0,is_single);
if (s3<se1) {
s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg4 = compile(s3,s2,depth1,0,is_single);
arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
}
}
}
}
if (p_ref && arg4==~0U && arg5==~0U) {
*p_ref = 5;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
p_ref[4] = arg2;
p_ref[5] = arg3;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2; // Prevent from being used in further optimization
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
}
p2 = ~0U; // 'p2' must be the dimension of the vector-valued operand if any
if (p1==~0U) p2 = imgin._spectrum;
else if (_cimg_mp_is_constant(p1)) {
p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
p2 = listin[p3]._spectrum;
}
if (!p2) _cimg_mp_return(0);
pos = vector(p2);
if (p1!=~0U)
CImg<ulongT>::vector((ulongT)(is_relative?mp_list_Jxyz:mp_list_Ixyz),
pos,p1,arg1,arg2,arg3,
arg4==~0U?_cimg_mp_interpolation:arg4,
arg5==~0U?_cimg_mp_boundary:arg5,p2).move_to(code);
else {
need_input_copy = true;
CImg<ulongT>::vector((ulongT)(is_relative?mp_Jxyz:mp_Ixyz),
pos,arg1,arg2,arg3,
arg4==~0U?_cimg_mp_interpolation:arg4,
arg5==~0U?_cimg_mp_boundary:arg5,p2).move_to(code);
}
_cimg_mp_return(pos);
}

// i/j(_#ind,_x,_y,_z,_c,_interpolation,_boundary_conditions)
if ((*ss=='i' || *ss=='j') && *ss1=='(') { // Image value as scalar
if (*ss2=='#') { // Index specified
s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss3,s0++,depth1,0,is_single);
} else { p1 = ~0U; s0 = ss2; }
arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
arg4 = is_relative?0U:(unsigned int)_cimg_mp_slot_c;
arg5 = arg6 = ~0U;
if (s0<se1) {
s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(s0,s1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) { // Coordinates specified as a vector
p2 = _cimg_mp_size(arg1);
++arg1;
if (p2>1) {
arg2 = arg1 + 1;
if (p2>2) {
arg3 = arg2 + 1;
if (p2>3) arg4 = arg3 + 1;
}
}
if (s1<se1) {
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg5 = compile(s1,s2,depth1,0,is_single);
arg6 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
}
} else if (s1<se1) {
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1,s2,depth1,0,is_single);
if (s2<se1) {
s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg3 = compile(s2,s3,depth1,0,is_single);
if (s3<se1) {
s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg4 = compile(s3,s2,depth1,0,is_single);
if (s2<se1) {
s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg5 = compile(s2,s3,depth1,0,is_single);
arg6 = s3<se1?compile(++s3,se1,depth1,0,is_single):~0U;
}
}
}
}
}
if (p_ref && arg5==~0U && arg6==~0U) {
*p_ref = 3;
p_ref[1] = p1;
p_ref[2] = (unsigned int)is_relative;
p_ref[3] = arg1;
p_ref[4] = arg2;
p_ref[5] = arg3;
p_ref[6] = arg4;
if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2; // Prevent from being used in further optimization
if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
if (_cimg_mp_is_comp(arg4)) memtype[arg4] = -2;
}

if (p1!=~0U) {
if (!listin) _cimg_mp_return(0);
pos = scalar7(is_relative?mp_list_jxyzc:mp_list_ixyzc,
p1,arg1,arg2,arg3,arg4,
arg5==~0U?_cimg_mp_interpolation:arg5,
arg6==~0U?_cimg_mp_boundary:arg6);
} else {
if (!imgin) _cimg_mp_return(0);
need_input_copy = true;
pos = scalar6(is_relative?mp_jxyzc:mp_ixyzc,
arg1,arg2,arg3,arg4,
arg5==~0U?_cimg_mp_interpolation:arg5,
arg6==~0U?_cimg_mp_boundary:arg6);
}
memtype[pos] = -2; // Prevent from being used in further optimization
_cimg_mp_return(pos);
}

// Mathematical functions.
switch (*ss) {

case '_' :
if (*ss1=='(') // Skip arguments
_cimg_mp_return_nan();
break;

case 'a' :
if (!std::strncmp(ss,"abs(",4)) { // Absolute value
_cimg_mp_op("Function 'abs()'");
arg1 = compile(ss4,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_abs,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::abs(mem[arg1]));
_cimg_mp_scalar1(mp_abs,arg1);
}

if (!std::strncmp(ss,"acos(",5)) { // Arccos
_cimg_mp_op("Function 'acos()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_acos,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::acos(mem[arg1]));
_cimg_mp_scalar1(mp_acos,arg1);
}

if (!std::strncmp(ss,"acosh(",6)) { // Hyperbolic arccosine
_cimg_mp_op("Function 'acosh()'");
arg1 = compile(ss6,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_acosh,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::acosh(mem[arg1]));
_cimg_mp_scalar1(mp_acosh,arg1);
}

if (!std::strncmp(ss,"asinh(",6)) { // Hyperbolic arcsine
_cimg_mp_op("Function 'asinh()'");
arg1 = compile(ss6,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_asinh,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::asinh(mem[arg1]));
_cimg_mp_scalar1(mp_asinh,arg1);
}

if (!std::strncmp(ss,"atanh(",6)) { // Hyperbolic arctangent
_cimg_mp_op("Function 'atanh()'");
arg1 = compile(ss6,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_atanh,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::atanh(mem[arg1]));
_cimg_mp_scalar1(mp_atanh,arg1);
}

if (!std::strncmp(ss,"arg(",4)) { // Nth argument
_cimg_mp_op("Function 'arg()'");
s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(ss4,s1,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,1,0);
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1,s2,depth1,0,is_single);
p2 = _cimg_mp_size(arg2);
p3 = 3;
CImg<ulongT>::vector((ulongT)mp_arg,0,0,p2,arg1,arg2).move_to(l_opcode);
for (s = ++s2; s<se; ++s) {
ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
(*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
arg3 = compile(s,ns,depth1,0,is_single);
_cimg_mp_check_type(arg3,p3,p2?2:1,p2);
CImg<ulongT>::vector(arg3).move_to(l_opcode);
++p3;
s = ns;
}
(l_opcode>'y').move_to(opcode);
opcode[2] = opcode._height;
if (_cimg_mp_is_constant(arg1)) {
p3-=1; // Number of args
arg1 = (unsigned int)(mem[arg1]<0?mem[arg1] + p3:mem[arg1]);
if (arg1<p3) _cimg_mp_return(opcode[4 + arg1]);
if (p2) {
pos = vector(p2);
std::memset(&mem[pos] + 1,0,p2*sizeof(double));
_cimg_mp_return(pos);
} else _cimg_mp_return(0);
}
pos = opcode[1] = p2?vector(p2):scalar();
opcode.move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"asin(",5)) { // Arcsin
_cimg_mp_op("Function 'asin()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_asin,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::asin(mem[arg1]));
_cimg_mp_scalar1(mp_asin,arg1);
}

if (!std::strncmp(ss,"atan(",5)) { // Arctan
_cimg_mp_op("Function 'atan()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_atan,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::atan(mem[arg1]));
_cimg_mp_scalar1(mp_atan,arg1);
}

if (!std::strncmp(ss,"atan2(",6)) { // Arctan2
_cimg_mp_op("Function 'atan2()'");
s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(ss6,s1,depth1,0,is_single);
arg2 = compile(++s1,se1,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_atan2,arg1,arg2);
if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_atan2,arg1,arg2);
if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_atan2,arg1,arg2);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
_cimg_mp_constant(std::atan2(mem[arg1],mem[arg2]));
_cimg_mp_scalar2(mp_atan2,arg1,arg2);
}
break;

case 'b' :
if (!std::strncmp(ss,"break(",6)) { // Complex absolute value
if (pexpr[se2 - expr._data]=='(') { // no arguments?
CImg<ulongT>::vector((ulongT)mp_break,_cimg_mp_slot_nan).move_to(code);
_cimg_mp_return_nan();
}
}

if (!std::strncmp(ss,"breakpoint(",11)) { // Break point (for abort test)
_cimg_mp_op("Function 'breakpoint()'");
if (pexpr[se2 - expr._data]=='(') { // no arguments?
CImg<ulongT>::vector((ulongT)mp_breakpoint,_cimg_mp_slot_nan).move_to(code);
_cimg_mp_return_nan();
}
}

if (!std::strncmp(ss,"bool(",5)) { // Boolean cast
_cimg_mp_op("Function 'bool()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bool,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant((bool)mem[arg1]);
_cimg_mp_scalar1(mp_bool,arg1);
}

if (!std::strncmp(ss,"begin(",6)) { // Begin
_cimg_mp_op("Function 'begin()'");
code.swap(code_begin);
arg1 = compile(ss6,se1,depth1,p_ref,true);
code.swap(code_begin);
_cimg_mp_return(arg1);
}
break;

case 'c' :
if (!std::strncmp(ss,"cabs(",5)) { // Complex absolute value
_cimg_mp_op("Function 'cabs()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,0,2,2);
_cimg_mp_scalar2(mp_complex_abs,arg1 + 1,arg1 + 2);
}

if (!std::strncmp(ss,"carg(",5)) { // Complex argument
_cimg_mp_op("Function 'carg()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,0,2,2);
_cimg_mp_scalar2(mp_atan2,arg1 + 2,arg1 + 1);
}

if (!std::strncmp(ss,"cats(",5)) { // Concatenate strings
_cimg_mp_op("Function 'cats()'");
CImg<ulongT>::vector((ulongT)mp_cats,0,0,0).move_to(l_opcode);
arg1 = 0;
for (s = ss5; s<se; ++s) {
ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
(*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
arg1 = compile(s,ns,depth1,0,is_single);
CImg<ulongT>::vector(arg1,_cimg_mp_size(arg1)).move_to(l_opcode);
s = ns;
}
_cimg_mp_check_constant(arg1,1,3); // Last argument = output vector size
l_opcode.remove();
(l_opcode>'y').move_to(opcode);
p1 = (unsigned int)mem[arg1];
pos = vector(p1);
opcode[1] = pos;
opcode[2] = p1;
opcode[3] = opcode._height;
opcode.move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"cbrt(",5)) { // Cubic root
_cimg_mp_op("Function 'cbrt()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cbrt,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::cbrt(mem[arg1]));
_cimg_mp_scalar1(mp_cbrt,arg1);
}

if (!std::strncmp(ss,"cconj(",6)) { // Complex conjugate
_cimg_mp_op("Function 'cconj()'");
arg1 = compile(ss6,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,0,2,2);
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_conj,pos,arg1).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"ceil(",5)) { // Ceil
_cimg_mp_op("Function 'ceil()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_ceil,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::ceil(mem[arg1]));
_cimg_mp_scalar1(mp_ceil,arg1);
}

if (!std::strncmp(ss,"cexp(",5)) { // Complex exponential
_cimg_mp_op("Function 'cexp()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,0,2,2);
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_exp,pos,arg1).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"clog(",5)) { // Complex logarithm
_cimg_mp_op("Function 'clog()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,0,2,2);
pos = vector(2);
CImg<ulongT>::vector((ulongT)mp_complex_log,pos,arg1).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"continue(",9)) { // Complex absolute value
if (pexpr[se2 - expr._data]=='(') { // no arguments?
CImg<ulongT>::vector((ulongT)mp_continue,_cimg_mp_slot_nan).move_to(code);
_cimg_mp_return_nan();
}
}

if (!std::strncmp(ss,"copy(",5)) { // Memory copy
_cimg_mp_op("Function 'copy()'");
ref.assign(14);
s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = p1 = compile(ss5,s1,depth1,ref,is_single);
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1,s2,depth1,ref._data + 7,is_single);
arg3 = arg4 = arg5 = ~0U; arg6 = 1;
if (s2<se1) {
s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg3 = compile(s2,s3,depth1,0,is_single);
if (s3<se1) {
s1 = ++s3; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg4 = compile(s3,s1,depth1,0,is_single);
if (s1<se1) {
s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg5 = compile(s1,s2,depth1,0,is_single);
arg6 = s2<se1?compile(++s2,se1,depth1,0,is_single):1;
}
}
}
if (_cimg_mp_is_vector(arg1)) {
if (!ref[0]) ++arg1;
else if (ref[0]>=4 && arg4==~0U) arg4 = scalar1(mp_image_whd,ref[1]);
}
if (_cimg_mp_is_vector(arg2)) {
if (arg3==~0U) arg3 = constant(_cimg_mp_size(arg2));
if (!ref[7]) ++arg2;
if (ref[7]>=4 && arg5==~0U) arg5 = scalar1(mp_image_whd,ref[8]);
}
if (arg3==~0U) arg3 = 1;
if (arg4==~0U) arg4 = 1;
if (arg5==~0U) arg5 = 1;
_cimg_mp_check_type(arg3,3,1,0);
_cimg_mp_check_type(arg4,4,1,0);
_cimg_mp_check_type(arg5,5,1,0);
_cimg_mp_check_type(arg6,5,1,0);
CImg<ulongT>(1,22).move_to(code);
code.back().get_shared_rows(0,7).fill((ulongT)mp_memcopy,p1,arg1,arg2,arg3,arg4,arg5,arg6);
code.back().get_shared_rows(8,21).fill(ref);
_cimg_mp_return(p1);
}

if (!std::strncmp(ss,"cos(",4)) { // Cosine
_cimg_mp_op("Function 'cos()'");
arg1 = compile(ss4,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cos,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::cos(mem[arg1]));
_cimg_mp_scalar1(mp_cos,arg1);
}

if (!std::strncmp(ss,"cosh(",5)) { // Hyperbolic cosine
_cimg_mp_op("Function 'cosh()'");
arg1 = compile(ss5,se1,depth1,0,is_single);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cosh,arg1);
if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::cosh(mem[arg1]));
_cimg_mp_scalar1(mp_cosh,arg1);
}

if (!std::strncmp(ss,"critical(",9)) { // Critical section (single thread at a time)
_cimg_mp_op("Function 'critical()'");
p1 = code._width;
arg1 = compile(ss + 9,se1,depth1,p_ref,true);
CImg<ulongT>::vector((ulongT)mp_critical,arg1,code._width - p1).move_to(code,p1);
_cimg_mp_return(arg1);
}

if (!std::strncmp(ss,"crop(",5)) { // Image crop
_cimg_mp_op("Function 'crop()'");
if (*ss5=='#') { // Index specified
s0 = ss6; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
p1 = compile(ss6,s0++,depth1,0,is_single);
_cimg_mp_check_list(false);
} else { p1 = ~0U; s0 = ss5; need_input_copy = true; }
pos = 0;
is_sth = false; // Coordinates specified as a vector?
if (s0<se1) for (s = s0; s<se; ++s, ++pos) {
ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
(*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
arg1 = compile(s,ns,depth1,0,is_single);
if (!pos && _cimg_mp_is_vector(arg1)) { // Coordinates specified as a vector
opcode = CImg<ulongT>::sequence(_cimg_mp_size(arg1),arg1 + 1,
arg1 + (ulongT)_cimg_mp_size(arg1));
opcode.resize(1,std::min(opcode._height,4U),1,1,0).move_to(l_opcode);
is_sth = true;
} else {
_cimg_mp_check_type(arg1,pos + 1,1,0);
CImg<ulongT>::vector(arg1).move_to(l_opcode);
}
s = ns;
}
(l_opcode>'y').move_to(opcode);

arg1 = 0; arg2 = (p1!=~0U);
switch (opcode._height) {
case 0 : case 1 :
CImg<ulongT>::vector(0,0,0,0,~0U,~0U,~0U,~0U,0).move_to(opcode);
break;
case 2 :
CImg<ulongT>::vector(*opcode,0,0,0,opcode[1],~0U,~0U,~0U,_cimg_mp_boundary).move_to(opcode);
arg1 = arg2 + 2;
break;
case 3 :
CImg<ulongT>::vector(*opcode,0,0,0,opcode[1],~0U,~0U,~0U,opcode[2]).move_to(opcode);
arg1 = arg2 + 2;
break;
case 4 :
CImg<ulongT>::vector(*opcode,opcode[1],0,0,opcode[2],opcode[3],~0U,~0U,_cimg_mp_boundary).
move_to(opcode);
arg1 = arg2 + (is_sth?2:3);
break;
case 5 :
CImg<ulongT>::vector(*opcode,opcode[1],0,0,opcode[2],opcode[3],~0U,~0U,opcode[4]).
move_to(opcode);
arg1 = arg2 + (is_sth?2:3);
break;
case 6 :
CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],0,opcode[3],opcode[4],opcode[5],~0U,
_cimg_mp_boundary).move_to(opcode);
arg1 = arg2 + (is_sth?2:4);
break;
case 7 :
CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],0,opcode[3],opcode[4],opcode[5],~0U,
opcode[6]).move_to(opcode);
arg1 = arg2 + (is_sth?2:4);
break;
case 8 :
CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],opcode[3],opcode[4],opcode[5],opcode[6],
opcode[7],_cimg_mp_boundary).move_to(opcode);
arg1 = arg2 + (is_sth?2:5);
break;
case 9 :
arg1 = arg2 + (is_sth?2:5);
break;
default : // Error -> too much arguments
*se = saved_char;
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Too much arguments specified, "
"in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}

_cimg_mp_check_type((unsigned int)*opcode,arg2 + 1,1,0);
_cimg_mp_check_type((unsigned int)opcode[1],arg2 + 1 + (is_sth?0:1),1,0);
_cimg_mp_check_type((unsigned int)opcode[2],arg2 + 1 + (is_sth?0:2),1,0);
_cimg_mp_check_type((unsigned int)opcode[3],arg2 + 1 + (is_sth?0:3),1,0);
if (opcode[4]!=(ulongT)~0U) {
_cimg_mp_check_constant((unsigned int)opcode[4],arg1,3);
opcode[4] = (ulongT)mem[opcode[4]];
}
if (opcode[5]!=(ulongT)~0U) {
_cimg_mp_check_constant((unsigned int)opcode[5],arg1 + 1,3);
opcode[5] = (ulongT)mem[opcode[5]];
}
if (opcode[6]!=(ulongT)~0U) {
_cimg_mp_check_constant((unsigned int)opcode[6],arg1 + 2,3);
opcode[6] = (ulongT)mem[opcode[6]];
}
if (opcode[7]!=(ulongT)~0U) {
_cimg_mp_check_constant((unsigned int)opcode[7],arg1 + 3,3);
opcode[7] = (ulongT)mem[opcode[7]];
}
_cimg_mp_check_type((unsigned int)opcode[8],arg1 + 4,1,0);

if (opcode[4]==(ulongT)~0U || opcode[5]==(ulongT)~0U ||
opcode[6]==(ulongT)~0U || opcode[7]==(ulongT)~0U) {
if (p1!=~0U) {
_cimg_mp_check_constant(p1,1,1);
p1 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
}
const CImg<T> &img = p1!=~0U?listin[p1]:imgin;
if (!img) {
*se = saved_char;
s0 = ss - 4>expr._data?ss - 4:expr._data;
cimg::strellipsize(s0,64);
throw CImgArgumentException("[" cimg_appname "_math_parser] "
"CImg<%s>::%s: %s: Cannot crop empty image when "
"some xyzc-coordinates are unspecified, in expression '%s%s%s'.",
pixel_type(),_cimg_mp_calling_function,s_op,
s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
if (opcode[4]==(ulongT)~0U) opcode[4] = (ulongT)img._width;
if (opcode[5]==(ulongT)~0U) opcode[5] = (ulongT)img._height;
if (opcode[6]==(ulongT)~0U) opcode[6] = (ulongT)img._depth;
if (opcode[7]==(ulongT)~0U) opcode[7] = (ulongT)img._spectrum;
}

pos = vector((unsigned int)(opcode[4]*opcode[5]*opcode[6]*opcode[7]));
CImg<ulongT>::vector((ulongT)mp_crop,
pos,p1,
*opcode,opcode[1],opcode[2],opcode[3],
opcode[4],opcode[5],opcode[6],opcode[7],
opcode[8]).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"cross(",6)) { // Cross product
_cimg_mp_op("Function 'cross()'");
s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(ss6,s1,depth1,0,is_single);
arg2 = compile(++s1,se1,depth1,0,is_single);
_cimg_mp_check_type(arg1,1,2,3);
_cimg_mp_check_type(arg2,2,2,3);
pos = vector(3);
CImg<ulongT>::vector((ulongT)mp_cross,pos,arg1,arg2).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"cut(",4)) { // Cut
_cimg_mp_op("Function 'cut()'");
s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(ss4,s1,depth1,0,is_single);
s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(++s1,s2,depth1,0,is_single);
arg3 = compile(++s2,se1,depth1,0,is_single);
_cimg_mp_check_type(arg2,2,1,0);
_cimg_mp_check_type(arg3,3,1,0);
if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector3_vss(mp_cut,arg1,arg2,arg3);
if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2) && _cimg_mp_is_constant(arg3)) {
val = mem[arg1];
val1 = mem[arg2];
val2 = mem[arg3];
_cimg_mp_constant(val<val1?val1:val>val2?val2:val);
}
_cimg_mp_scalar3(mp_cut,arg1,arg2,arg3);
}
break;

case 'd' :
if (*ss1=='(') { // Image depth
_cimg_mp_op("Function 'd()'");
if (*ss2=='#') { // Index specified
p1 = compile(ss3,se1,depth1,0,is_single);
_cimg_mp_check_list(false);
} else { if (ss2!=se1) break; p1 = ~0U; }
pos = scalar();
CImg<ulongT>::vector((ulongT)mp_image_d,pos,p1).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"date(",5)) { // Current date or file date
_cimg_mp_op("Function 'date()'");
s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = ss5!=se1?compile(ss5,s1,depth1,0,is_single):~0U;
arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):~0U;
if (arg2!=~0U) _cimg_mp_check_type(arg2,1,2,0);
pos = arg1==~0U || _cimg_mp_is_vector(arg1)?vector(arg1==~0U?7:_cimg_mp_size(arg1)):scalar();
CImg<ulongT>::vector((ulongT)mp_date,pos,_cimg_mp_size(pos),
arg1,arg1==~0U?~0U:_cimg_mp_size(arg1),
arg2,arg2==~0U?~0U:_cimg_mp_size(arg2)).move_to(code);
_cimg_mp_return(pos);
}

if (!std::strncmp(ss,"debug(",6)) { // Print debug info
_cimg_mp_op("Function 'debug()'");
p1 = code._width;
arg1 = compile(ss6,se1,depth1,p_ref,is_single);
*se1 = 0;
variable_name.assign(CImg<charT>::string(ss6,true,true).unroll('y'),true);
cimg::strpare(variable_name,false,true);
((CImg<ulongT>::vector((ulongT)mp_debug,arg1,0,code._width - p1),
variable_name)>'y').move_to(opcode);
opcode[2] = opcode._height;
opcode.move_to(code,p1);
*se1 = ')';
_cimg_mp_return(arg1);
}

if (!std::strncmp(ss,"display(",8)) { // Display memory, vector or image
_cimg_mp_op("Function 'display()'");
if (pexpr[se2 - expr._data]=='(') { // no arguments?
CImg<ulongT>::vector((ulongT)mp_display_memory,_cimg_mp_slot_nan).move_to(code);
_cimg_mp_return_nan();
}
if (*ss8!='#') { // Vector
s1 = ss8; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
arg1 = compile(ss8,s1,depth1,0,is_single);
arg2 = 0; arg3 = arg4 = arg5 = 1;
if (s1<se1) {
s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg2 = compile(s1 + 1,s2,depth1,0,is_single);
if (s2<se1) {
s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
arg3 = compile(s2,s3,depth1,0,is_single);
if (s3<se1) {
s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
arg4 = compile(s3,s2,depth1,0,is_single);
arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):0;
}
}
}
_cimg_mp_check_type(arg2,2,1,0);
_cimg_mp_check_type(arg3,3,1,0);
_cimg_mp_check_type(arg4,4,1,0);
_cimg_mp_check_type(arg5,5,1,0);

c1 = *s1; *s1 = 0;
variable_name.assign(CImg<charT>::string(ss8,true,true).unroll('y'),true);
cimg::strpare(variable_name,false,true);
if (_cimg_mp_is_vector(arg1))
((CImg<ulongT>::vector((ulongT)mp_vector_print,arg1,0,(ulongT)_cimg_mp_size(arg1),0),
variable_name)>'y').move_to(opcode);
else
((CImg<ulongT>::vector((ulongT)mp_print,arg1,0,0),
variable_name)>'y').move_to(opcode);
opcode[2] = opcode._height;
opcode.move_to(code);

((CImg<ulongT>::vector((ulongT)mp_display,arg1,0,(ulongT)_cimg_mp_size(arg1),
arg2,arg3,arg4,arg5),
variable_name)>'y').move_to(opcode);
opcode[2] = opcode._height;
opcode.move_to(code);
*s1 = c1;
_cimg_mp_return(arg1);

} else { // Image
p1 = compile(ss8 + 1,se1,depth1,0,is_single);
_cimg_mp_check_list(true);
CImg<ulongT>::vector((ulongT)mp_image_display,_cimg_mp_slot_nan,p1).move_to(code);
_cimg_mp_return_nan();
}
}

if (!std::strncmp(ss,"det(",4)) { // Matrix determinant
_cimg_mp_op("Function 'det()'");
arg1 = compile(ss4,se1,depth1,0,is_single);
_cimg_mp_check_matrix_square(arg1,1);
p1 = (unsigned int)cimg::round(std::sqrt((float)_cimg_mp_size(arg1)));
_cimg_mp_scalar2(mp_det,arg1,p1);
}

if (!std::strncmp(ss,"diag(",5)) { // Diagonal matrix
_cimg_mp_op("Function 'diag()'");
CImg<ulongT>::vector((ulongT)mp_diag,0,0).move_to(l_opcode);
for (s = ss5; s<se; ++s) {
ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
(*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
arg2 = compile(s,ns,depth1,