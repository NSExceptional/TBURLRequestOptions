// swift-tools-version:5.0

import PackageDescription

let package = Package(
    name: "TBURLRequestOptions",
    products: [
        .library(
            name: "TBURLRequestOptions",
            targets: ["TBURLRequestOptions"]
        ),
    ],
    targets: [
        .target(
            name: "TBURLRequestOptions",
            dependencies: [],
            path: "TBURLRequestOptions/Classes",
            publicHeadersPath: ""
        )
    ]
)
