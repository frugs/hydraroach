cc_library(
    name = "replay",
    srcs = [
        "find_replay.cpp",
        "find_replay.hpp",
        "hash_replay.cpp",
        "hash_replay.hpp",
    ],
    deps = [
        "@boost//:filesystem",
        "@picosha2//:picosha2",
    ],
    visibility = ["//visibility:public"],
)