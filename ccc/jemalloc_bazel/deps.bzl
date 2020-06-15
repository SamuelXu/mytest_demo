load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def load_deps():
  http_archive(
    name = "com_github_jemalloc",
    build_file = "@//third_party/jemalloc:jemalloc.BUILD",
    strip_prefix = "jemalloc-5.2.1",
    sha256 = "461eee78a32a51b639ef82ca192b98c64a6a4d7f4be0642f3fc5a23992138fd5",
    urls = [
    "https://github.com/jemalloc/jemalloc/archive/5.2.1.zip"
    ],
  )
