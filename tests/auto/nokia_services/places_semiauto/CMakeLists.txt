qt_internal_add_test(tst_nokia_places
    SOURCES
        ../../placemanager_utils/placemanager_utils.h
        ../../placemanager_utils/placemanager_utils.cpp
        tst_places.cpp
    LIBRARIES
        Qt::Core
        Qt::Location
        Qt::Positioning
)
