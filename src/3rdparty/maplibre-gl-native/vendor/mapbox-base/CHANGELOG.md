# MapLibre Base

## v2.1.0

### ð«ï¸ Features and Improvements
Update [args](https://github.com/Taywee/args)Â from 6.2.3 to 6.4.1
Update [rapidjson](https://github.com/Tencent/rapidjson)Â from (28 Jun 2019 -Â [d87b698d](https://github.com/Tencent/rapidjson/commit/d87b698d)) to (20 Jun 2022 -Â [27c3a8d](https://github.com/Tencent/rapidjson/commit/27c3a8d))

## v2.0.0

### ð«ï¸ Other
- [base] New fork maintained by MapLibre
- [base] Replace Travis with Github Actions

## v1.9.1

### ð«ï¸ Other
 - [deps] Update ghc::filesystem to v1.5.10

## v1.9.0

### ð«ï¸ Other
 - [deps] Update ghc::filesystem to v1.5.6

## v1.8.1

### ð«ï¸ Other
 - [deps] Update geojson-vt-cpp to v6.6.5

## v1.8.0

### ð«ï¸ Other
 - [deps] Update supercluster.hpp to v0.5.0

## v1.7.0

### ð«ï¸ Other
 - [deps] Bump supercluster.hpp to v0.4.0

## v1.6.1

### ð«ï¸ Other
 - [base] jni.hpp @ 57ca9ed4bbeb22ed8d20a55063dcaa217ba47f42

## v1.6.0

### ð«ï¸ Other
 - [base] Update geojson.hpp to v5.1.0
 - [base] Update geojson-vt-cpp to v6.6.4
 - [ci] Rename master branch to main
 - [weak] Introduce WeakPtrFactory::invalidateWeakPtrs()
 - [weak] Fix possible WeakPtr locks after WeakPtrFactory gets invalid.

## v1.5.0

### ð«ï¸ Other
 - [base] Update geojson.hpp to v0.5.0

## v1.4.0

### â¨ New features
- [extras] Bump googletest to 1.10.0
    - Better gmock syntax.

### â ï¸ Breaking changes
- [base] expected-lite @ v0.4.0

### ð«ï¸ Other
- [doc] Add documentation for `mapbox::base::Value`

## v1.3.0

### â¨ New features
- [base] Add platform definitions

### â ï¸ Breaking changes
- [base] jni.hpp @ e2bbae090005ac1ce2a88c51c0cff2d22d957545

### ð«ï¸ Other
- [build] Update LICENSE.thirdparty

## v1.2.1

### ð«ï¸ Other
- Add `MAPBOX_BASE_BUILD_TESTING` option for overriding building tests when building outside of mapbox-base project.

## v1.2.0

### â¨ New features
- Update minimist dependency to v1.2.5
- [base] Added GeoJSON VT and ShelfPack

### â ï¸ Breaking changes
- Move mapbox-base-owned libraries to a single folder
- [base] cheap-ruler-cpp @ 746044cfbb7d254f1d67929eb564a0dcaaa39cc1
- [base] jni.hpp @ 385dede669c843144b9ad68bbb7af3989d76104e
- [base] geometry.hpp @ a5571a3ace5853e0d1e8d5fbdc87163c824ebeb7

### ð«ï¸ Other
- Use googletest framework

## v1.1.0

### â¨ New features
Extras:
- extras/args @ 6.2.2-9-g401663c
- extras/expected-lite @ v0.3.0-6-g6fad61b
- extras/filesystem @ v1.2.4-7-g135015f
- extras/kdbush.hpp @ v0.1.3-1-ge1e847b
- extras/rapidjson @ v1.1.0-490-gd87b698d

New libraries:
- mapbox/io
- mapbox/typewrapper
- mapbox/value
- mapbox/weak

### â ï¸ Breaking changes
- mapbox/geojson.hpp @ v0.4.3
- mapbox/geometry.hpp @ v1.0.0-8-gb3f4bd4
- mapbox/jni.hpp @ v4.0.1
- mapbox/optional @ f6249e7f
- mapbox/supercluster.hpp @ v0.3.2-1-g03c026c
- mapbox/variant @ v1.1.6

## v1.0.0

### â¨ New features
- geometry.hpp @ v1.0.0
- variant @ v1.1.6
