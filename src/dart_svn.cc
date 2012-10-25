#include <string.h>
#include <stdio.h>
#include "dart_api.h"

#include "svn_version.h"

#ifdef _WIN32
#define snprintf _snprintf
#endif

#define DART_ARG(name, i) Dart_Handle name = Dart_GetNativeArgument(arguments, i);
#define DART_ARGS_0() Dart_EnterScope(); /*{printf("Entering %s\n", __FUNCTION__);}*/
#define DART_ARGS_1(arg0) DART_ARGS_0() DART_ARG(arg0, 0)
#define DART_ARGS_2(arg0, arg1) DART_ARGS_1(arg0); DART_ARG(arg1, 1)
#define DART_ARGS_3(arg0, arg1, arg2) DART_ARGS_2(arg0, arg1); DART_ARG(arg2, 2)
#define DART_ARGS_4(arg0, arg1, arg2, arg3) DART_ARGS_3(arg0, arg1, arg2); DART_ARG(arg3, 3)

#define DART_FUNCTION(name) static void name(Dart_NativeArguments arguments)
#define DART_RETURN(expr) {Dart_SetReturnValue(arguments, expr); Dart_ExitScope(); return;}
#define DART_RESOLVE(func, args) if (!strcmp(#func, cname) && argc == args) { return func; }

Dart_NativeFunction ResolveName(Dart_Handle name, int argc);

static Dart_Handle library;

DART_EXPORT Dart_Handle dart_svn_Init(Dart_Handle parent_library) {
  if (Dart_IsError(parent_library)) { return parent_library; }

  Dart_Handle result_code = Dart_SetNativeResolver(parent_library, ResolveName);
  if (Dart_IsError(result_code)) return result_code;

  library = Dart_NewPersistentHandle(parent_library);
  return parent_library;
}

void Throw(const char* message) {
  Dart_Handle messageHandle = Dart_NewString(message);
  Dart_Handle exceptionClass = Dart_GetClass(library, Dart_NewString("SvnException"));
  Dart_ThrowException(Dart_New(exceptionClass, Dart_NewString("_internal"), 1, &messageHandle));
}

Dart_Handle CheckDartError(Dart_Handle result) {
  if (Dart_IsError(result)) Throw(Dart_GetError(result));
  return result;
}

DART_FUNCTION(Version) {
  DART_ARGS_0();
  char ver[128];
  snprintf(ver, sizeof(ver), "%u.%u.%u", SVN_VER_MAJOR, SVN_VER_MINOR, SVN_VER_PATCH);
  DART_RETURN(Dart_NewString(ver));
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc) {
  assert(Dart_IsString8(name));
  const char* cname;
  Dart_Handle check_error = Dart_StringToCString(name, &cname);
  if (Dart_IsError(check_error)) Dart_PropagateError(check_error);

  DART_RESOLVE(Version, 0);
  return NULL;
}