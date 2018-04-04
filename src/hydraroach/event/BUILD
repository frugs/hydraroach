cc_library(
    name = "event",
    srcs = [
        "event_queue.cpp",
        "event_queue.hpp",
        "event.cpp",
        "event.hpp",
        "event_handler.hpp",
    ],
    deps = [
        "@concurrentqueue//:concurrentqueue",
        "@boost//:variant",
    ],
    visibility = ["//visibility:public"],
)