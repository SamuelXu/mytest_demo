licenses(["notice"])

load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
package(
  default_visibility = ["//visibility:public"],
)

filegroup(
  name = "all",
  srcs = glob(["**"]),
  visibility = ["//visibility:public"]
)

configure_make(
  name = "libjemalloc",
  autogen = True,
  configure_in_place = True,
  configure_options = [
  "--enable-shared=no",
  "--with-jemalloc-prefix=je_",
  ],
  lib_source = "@com_github_jemalloc//:all",
  linkopts = [
  "-lpthread",
  "-ldl",
  ],
  static_libraries = [
  "libjemalloc.a",
  ],
)
