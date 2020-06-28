
genrule(
  name = "generate",
  srcs = ["include/create.sh"],
  outs = ["include/app.h"],
  cmd = """
  EXEC=$(location include/create.sh)
  OUT=$(location include/app.h)
  sh $$EXEC $@ #same with sh $$EXEC $$OUT
  """
)

cc_binary(
    name = "app",
    srcs = ["app.cc"],
    deps = [":header"]
)

cc_library(
  name = "header",
  hdrs = ["include/app.h"]
)

