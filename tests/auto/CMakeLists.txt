# Generated from auto.pro.

# TODO: enable location tests later!
if(TARGET Qt::Location)
     add_subdirectory(geotestplugin)
     add_subdirectory(qplace)
     add_subdirectory(qplaceattribute)
     add_subdirectory(qplacecategory)
     add_subdirectory(qplacecontactdetail)
     add_subdirectory(qplacecontentrequest)
     add_subdirectory(qplacedetailsreply)
     add_subdirectory(qplacematchreply)
     add_subdirectory(qplacematchrequest)
     add_subdirectory(qplaceratings)
     add_subdirectory(qplaceresult)
     add_subdirectory(qproposedsearchresult)
     add_subdirectory(qplacereply)
     add_subdirectory(qplacesearchrequest)
     add_subdirectory(qplacesupplier)
     add_subdirectory(qplacesearchresult)
     add_subdirectory(qplacesearchreply)
     add_subdirectory(qplacesearchsuggestionreply)
     add_subdirectory(qplaceuser)
     add_subdirectory(qgeocodingmanagerplugins)
     add_subdirectory(qgeocameracapabilities)
     add_subdirectory(qgeocameradata)
     add_subdirectory(qgeocodereply)
     add_subdirectory(qgeomaneuver)
     add_subdirectory(qgeotiledmapscene)
     add_subdirectory(qgeoroute)
     add_subdirectory(qgeoroutereply)
     add_subdirectory(qgeorouterequest)
     add_subdirectory(qgeoroutesegment)
     add_subdirectory(qgeoroutingmanagerplugins)
     add_subdirectory(qgeotilespec)
     add_subdirectory(qgeoroutexmlparser)
     add_subdirectory(maptype)
     add_subdirectory(qgeocameratiles)
endif()
if(TARGET Qt::Location AND NOT ANDROID)
     add_subdirectory(qgeojson)
     if(QT_FEATURE_geoservices_nokia)
          add_subdirectory(qplacemanager_nokia)
     endif()
     add_subdirectory(placesplugin_unsupported)
     #     add_subdirectory(cmake)
     if(QT6_IS_SHARED_LIBS_BUILD)
          add_subdirectory(qplacemanager)
          add_subdirectory(qplacemanager_unsupported)
          add_subdirectory(qmlinterface)
          add_subdirectory(qgeoserviceprovider)
          add_subdirectory(qgeoroutingmanager)
          add_subdirectory(qgeocodingmanager)
          add_subdirectory(qgeotiledmap)
     endif()
     if(QT_FEATURE_geoservices_nokia)
          add_subdirectory(nokia_services)
     endif()
endif()

if (TARGET Qt::Location AND TARGET Qt::Quick AND QT6_IS_SHARED_LIBS_BUILD)
     if (NOT ANDROID)
          add_subdirectory(declarative_mappolyline)
          add_subdirectory(declarative_location_core)
          add_subdirectory(declarativetestplugin)
          add_subdirectory(declarative_ui)
     endif()
endif()
