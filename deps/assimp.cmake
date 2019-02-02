include_guard_x()

set(ASSIMP_DIR ${CMAKE_SOURCE_DIR}/deps/assimp)

set(ASSIMP_VERSION_MAJOR 4)
set(ASSIMP_VERSION_MINOR 1)
set(ASSIMP_VERSION_PATCH 0)
set(ASSIMP_VERSION ${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH})
set(ASSIMP_SOVERSION 4)
set(PROJECT_VERSION "${ASSIMP_VERSION}")

IF (NOT GIT_COMMIT_HASH)
    set(GIT_COMMIT_HASH 0)
ENDIF (NOT GIT_COMMIT_HASH)

set(IRRXML_DIR ${ASSIMP_DIR}/contrib/irrXML)

add_library(IrrXML STATIC
        ${IRRXML_DIR}/CXMLReaderImpl.h
        ${IRRXML_DIR}/heapsort.h
        ${IRRXML_DIR}/irrArray.h
        ${IRRXML_DIR}/irrString.h
        ${IRRXML_DIR}/irrTypes.h
        ${IRRXML_DIR}/irrXML.cpp
        ${IRRXML_DIR}/irrXML.h)

target_include_directories(IrrXML PUBLIC ${IRRXML_DIR})

configure_file(
        ${ASSIMP_DIR}/revision.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/revision.h
)

configure_file(
        ${ASSIMP_DIR}/include/assimp/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/assimp/config.h
)

set(HEADER_PATH ${ASSIMP_DIR}/include/assimp)

set(COMPILER_HEADERS
        ${HEADER_PATH}/Compiler/pushpack1.h
        ${HEADER_PATH}/Compiler/poppack1.h
        ${HEADER_PATH}/Compiler/pstdint.h
        )

set(PUBLIC_HEADERS
        ${HEADER_PATH}/anim.h
        ${HEADER_PATH}/ai_assert.h
        ${HEADER_PATH}/camera.h
        ${HEADER_PATH}/color4.h
        ${HEADER_PATH}/color4.inl
        ${CMAKE_CURRENT_BINARY_DIR}/include/assimp/config.h
        ${HEADER_PATH}/defs.h
        ${HEADER_PATH}/Defines.h
        ${HEADER_PATH}/cfileio.h
        ${HEADER_PATH}/light.h
        ${HEADER_PATH}/material.h
        ${HEADER_PATH}/material.inl
        ${HEADER_PATH}/matrix3x3.h
        ${HEADER_PATH}/matrix3x3.inl
        ${HEADER_PATH}/matrix4x4.h
        ${HEADER_PATH}/matrix4x4.inl
        ${HEADER_PATH}/mesh.h
        ${HEADER_PATH}/postprocess.h
        ${HEADER_PATH}/quaternion.h
        ${HEADER_PATH}/quaternion.inl
        ${HEADER_PATH}/scene.h
        ${HEADER_PATH}/metadata.h
        ${HEADER_PATH}/texture.h
        ${HEADER_PATH}/types.h
        ${HEADER_PATH}/vector2.h
        ${HEADER_PATH}/vector2.inl
        ${HEADER_PATH}/vector3.h
        ${HEADER_PATH}/vector3.inl
        ${HEADER_PATH}/version.h
        ${HEADER_PATH}/cimport.h
        ${HEADER_PATH}/importerdesc.h
        ${HEADER_PATH}/Importer.hpp
        ${HEADER_PATH}/DefaultLogger.hpp
        ${HEADER_PATH}/ProgressHandler.hpp
        ${HEADER_PATH}/IOStream.hpp
        ${HEADER_PATH}/IOSystem.hpp
        ${HEADER_PATH}/Logger.hpp
        ${HEADER_PATH}/LogStream.hpp
        ${HEADER_PATH}/NullLogger.hpp
        ${HEADER_PATH}/cexport.h
        ${HEADER_PATH}/Exporter.hpp
        ${HEADER_PATH}/DefaultIOStream.h
        ${HEADER_PATH}/DefaultIOSystem.h
        ${HEADER_PATH}/SceneCombiner.h
        )

set(Core_SRCS
        ${ASSIMP_DIR}/code/Assimp.cpp
        )

set(Logging_SRCS
        ${HEADER_PATH}/DefaultLogger.hpp
        ${HEADER_PATH}/LogStream.hpp
        ${HEADER_PATH}/Logger.hpp
        ${HEADER_PATH}/NullLogger.hpp
        ${ASSIMP_DIR}/code/Win32DebugLogStream.h
        ${ASSIMP_DIR}/code/DefaultLogger.cpp
        ${ASSIMP_DIR}/code/FileLogStream.h
        ${ASSIMP_DIR}/code/StdOStreamLogStream.h
        )

set(Common_SRCS
        ${ASSIMP_DIR}/code/fast_atof.h
        ${ASSIMP_DIR}/code/qnan.h
        ${ASSIMP_DIR}/code/BaseImporter.cpp
        ${ASSIMP_DIR}/code/BaseImporter.h
        ${ASSIMP_DIR}/code/BaseProcess.cpp
        ${ASSIMP_DIR}/code/BaseProcess.h
        ${ASSIMP_DIR}/code/Importer.h
        ${ASSIMP_DIR}/code/ScenePrivate.h
        ${ASSIMP_DIR}/code/PostStepRegistry.cpp
        ${ASSIMP_DIR}/code/ImporterRegistry.cpp
        ${ASSIMP_DIR}/code/ByteSwapper.h
        ${ASSIMP_DIR}/code/DefaultProgressHandler.h
        ${ASSIMP_DIR}/code/DefaultIOStream.cpp
        ${ASSIMP_DIR}/code/DefaultIOSystem.cpp
        ${ASSIMP_DIR}/code/CInterfaceIOWrapper.cpp
        ${ASSIMP_DIR}/code/CInterfaceIOWrapper.h
        ${ASSIMP_DIR}/code/Hash.h
        ${ASSIMP_DIR}/code/Importer.cpp
        ${ASSIMP_DIR}/code/IFF.h
        ${ASSIMP_DIR}/code/MemoryIOWrapper.h
        ${ASSIMP_DIR}/code/ParsingUtils.h
        ${ASSIMP_DIR}/code/StreamReader.h
        ${ASSIMP_DIR}/code/StreamWriter.h
        ${ASSIMP_DIR}/code/StringComparison.h
        ${ASSIMP_DIR}/code/StringUtils.h
        ${ASSIMP_DIR}/code/SGSpatialSort.cpp
        ${ASSIMP_DIR}/code/SGSpatialSort.h
        ${ASSIMP_DIR}/code/VertexTriangleAdjacency.cpp
        ${ASSIMP_DIR}/code/VertexTriangleAdjacency.h
        ${ASSIMP_DIR}/code/GenericProperty.h
        ${ASSIMP_DIR}/code/SpatialSort.cpp
        ${ASSIMP_DIR}/code/SpatialSort.h
        ${ASSIMP_DIR}/code/SceneCombiner.cpp
        ${ASSIMP_DIR}/code/ScenePreprocessor.cpp
        ${ASSIMP_DIR}/code/ScenePreprocessor.h
        ${ASSIMP_DIR}/code/SkeletonMeshBuilder.cpp
        ${ASSIMP_DIR}/code/SkeletonMeshBuilder.h
        ${ASSIMP_DIR}/code/SplitByBoneCountProcess.cpp
        ${ASSIMP_DIR}/code/SplitByBoneCountProcess.h
        ${ASSIMP_DIR}/code/ScaleProcess.cpp
        ${ASSIMP_DIR}/code/ScaleProcess.h
        ${ASSIMP_DIR}/code/SmoothingGroups.h
        ${ASSIMP_DIR}/code/StandardShapes.cpp
        ${ASSIMP_DIR}/code/StandardShapes.h
        ${ASSIMP_DIR}/code/TargetAnimation.cpp
        ${ASSIMP_DIR}/code/TargetAnimation.h
        ${ASSIMP_DIR}/code/RemoveComments.cpp
        ${ASSIMP_DIR}/code/RemoveComments.h
        ${ASSIMP_DIR}/code/Subdivision.cpp
        ${ASSIMP_DIR}/code/Subdivision.h
        ${ASSIMP_DIR}/code/scene.cpp
        ${ASSIMP_DIR}/code/Vertex.h
        ${ASSIMP_DIR}/code/LineSplitter.h
        ${ASSIMP_DIR}/code/TinyFormatter.h
        ${ASSIMP_DIR}/code/Profiler.h
        ${ASSIMP_DIR}/code/LogAux.h
        ${ASSIMP_DIR}/code/Bitmap.cpp
        ${ASSIMP_DIR}/code/Bitmap.h
        ${ASSIMP_DIR}/code/XMLTools.h
        ${ASSIMP_DIR}/code/Version.cpp
        ${ASSIMP_DIR}/code/IOStreamBuffer.h
        ${ASSIMP_DIR}/code/CreateAnimMesh.h
        ${ASSIMP_DIR}/code/CreateAnimMesh.cpp
        )

set(Step_SRCS
        ${ASSIMP_DIR}/code/StepExporter.h
        ${ASSIMP_DIR}/code/StepExporter.cpp
        )

set(MaterialSystem_SRCS
        ${ASSIMP_DIR}/code/MaterialSystem.cpp
        ${ASSIMP_DIR}/code/MaterialSystem.h
        )

set(Exporter_SRCS
        ${ASSIMP_DIR}/code/Exporter.cpp
        ${ASSIMP_DIR}/code/AssimpCExport.cpp
        ${ASSIMP_DIR}/code/BlobIOSystem.h
        )

set(PostProcessing_SRCS
        ${ASSIMP_DIR}/code/CalcTangentsProcess.cpp
        ${ASSIMP_DIR}/code/CalcTangentsProcess.h
        ${ASSIMP_DIR}/code/ComputeUVMappingProcess.cpp
        ${ASSIMP_DIR}/code/ComputeUVMappingProcess.h
        ${ASSIMP_DIR}/code/ConvertToLHProcess.cpp
        ${ASSIMP_DIR}/code/ConvertToLHProcess.h
        ${ASSIMP_DIR}/code/FindDegenerates.cpp
        ${ASSIMP_DIR}/code/FindDegenerates.h
        ${ASSIMP_DIR}/code/FindInstancesProcess.cpp
        ${ASSIMP_DIR}/code/FindInstancesProcess.h
        ${ASSIMP_DIR}/code/FindInvalidDataProcess.cpp
        ${ASSIMP_DIR}/code/FindInvalidDataProcess.h
        ${ASSIMP_DIR}/code/FixNormalsStep.cpp
        ${ASSIMP_DIR}/code/FixNormalsStep.h
        ${ASSIMP_DIR}/code/GenFaceNormalsProcess.cpp
        ${ASSIMP_DIR}/code/GenFaceNormalsProcess.h
        ${ASSIMP_DIR}/code/GenVertexNormalsProcess.cpp
        ${ASSIMP_DIR}/code/GenVertexNormalsProcess.h
        ${ASSIMP_DIR}/code/PretransformVertices.cpp
        ${ASSIMP_DIR}/code/PretransformVertices.h
        ${ASSIMP_DIR}/code/ImproveCacheLocality.cpp
        ${ASSIMP_DIR}/code/ImproveCacheLocality.h
        ${ASSIMP_DIR}/code/JoinVerticesProcess.cpp
        ${ASSIMP_DIR}/code/JoinVerticesProcess.h
        ${ASSIMP_DIR}/code/LimitBoneWeightsProcess.cpp
        ${ASSIMP_DIR}/code/LimitBoneWeightsProcess.h
        ${ASSIMP_DIR}/code/RemoveRedundantMaterials.cpp
        ${ASSIMP_DIR}/code/RemoveRedundantMaterials.h
        ${ASSIMP_DIR}/code/RemoveVCProcess.cpp
        ${ASSIMP_DIR}/code/RemoveVCProcess.h
        ${ASSIMP_DIR}/code/SortByPTypeProcess.cpp
        ${ASSIMP_DIR}/code/SortByPTypeProcess.h
        ${ASSIMP_DIR}/code/SplitLargeMeshes.cpp
        ${ASSIMP_DIR}/code/SplitLargeMeshes.h
        ${ASSIMP_DIR}/code/TextureTransform.cpp
        ${ASSIMP_DIR}/code/TextureTransform.h
        ${ASSIMP_DIR}/code/TriangulateProcess.cpp
        ${ASSIMP_DIR}/code/TriangulateProcess.h
        ${ASSIMP_DIR}/code/ValidateDataStructure.cpp
        ${ASSIMP_DIR}/code/ValidateDataStructure.h
        ${ASSIMP_DIR}/code/OptimizeGraph.cpp
        ${ASSIMP_DIR}/code/OptimizeGraph.h
        ${ASSIMP_DIR}/code/OptimizeMeshes.cpp
        ${ASSIMP_DIR}/code/OptimizeMeshes.h
        ${ASSIMP_DIR}/code/DeboneProcess.cpp
        ${ASSIMP_DIR}/code/DeboneProcess.h
        ${ASSIMP_DIR}/code/ProcessHelper.h
        ${ASSIMP_DIR}/code/ProcessHelper.cpp
        ${ASSIMP_DIR}/code/PolyTools.h
        ${ASSIMP_DIR}/code/MakeVerboseFormat.cpp
        ${ASSIMP_DIR}/code/MakeVerboseFormat.h
        )

macro(ADD_ASSIMP_IMPORTER name)
    message(STATUS "ENABLING importer ${name}")
    LIST(APPEND ASSIMP_LOADER_SRCS ${ARGN})
endmacro()

ADD_ASSIMP_IMPORTER(OBJ
        ${ASSIMP_DIR}/code/ObjFileData.h
        ${ASSIMP_DIR}/code/ObjFileImporter.cpp
        ${ASSIMP_DIR}/code/ObjFileImporter.h
        ${ASSIMP_DIR}/code/ObjFileMtlImporter.cpp
        ${ASSIMP_DIR}/code/ObjFileMtlImporter.h
        ${ASSIMP_DIR}/code/ObjFileParser.cpp
        ${ASSIMP_DIR}/code/ObjFileParser.h
        ${ASSIMP_DIR}/code/ObjTools.h
        ${ASSIMP_DIR}/code/ObjExporter.h
        ${ASSIMP_DIR}/code/ObjExporter.cpp
        )

add_library(assimp STATIC
        # Assimp Files
        ${Core_SRCS}
        ${Common_SRCS}
        ${Logging_SRCS}
        ${Exporter_SRCS}
        ${PostProcessing_SRCS}
        ${MaterialSystem_SRCS}
        ${Step_SRCS}

        # Model Support
        ${ASSIMP_LOADER_SRCS}

        # Third-party libraries
        #        ${IrrXML_SRCS}
        #        ${unzip_compile_SRCS}
        #        ${Poly2Tri_SRCS}
        #        ${Clipper_SRCS}
        #        ${openddl_parser_SRCS}
        #        ${open3dgc_SRCS}
        #        ${ziplib_SRCS}
        # Necessary to show the headers in the project when using the VC++ generator:

        ${PUBLIC_HEADERS}
        ${COMPILER_HEADERS}
        )

target_compile_definitions(assimp PRIVATE
        ASSIMP_BUILD_NO_X_IMPORTER
        #        ASSIMP_BUILD_NO_OBJ_IMPORTER
        ASSIMP_BUILD_NO_AMF_IMPORTER
        ASSIMP_BUILD_NO_3DS_IMPORTER
        ASSIMP_BUILD_NO_MD3_IMPORTER
        ASSIMP_BUILD_NO_MD2_IMPORTER
        ASSIMP_BUILD_NO_PLY_IMPORTER
        ASSIMP_BUILD_NO_MDL_IMPORTER
        ASSIMP_BUILD_NO_ASE_IMPORTER
        ASSIMP_BUILD_NO_3DS_IMPORTER
        ASSIMP_BUILD_NO_HMP_IMPORTER
        ASSIMP_BUILD_NO_SMD_IMPORTER
        ASSIMP_BUILD_NO_MDC_IMPORTER
        ASSIMP_BUILD_NO_MD5_IMPORTER
        ASSIMP_BUILD_NO_STL_IMPORTER
        ASSIMP_BUILD_NO_LWO_IMPORTER
        ASSIMP_BUILD_NO_DXF_IMPORTER
        ASSIMP_BUILD_NO_NFF_IMPORTER
        ASSIMP_BUILD_NO_RAW_IMPORTER
        ASSIMP_BUILD_NO_SIB_IMPORTER
        ASSIMP_BUILD_NO_OFF_IMPORTER
        ASSIMP_BUILD_NO_AC_IMPORTER
        ASSIMP_BUILD_NO_BVH_IMPORTER
        ASSIMP_BUILD_NO_IRRMESH_IMPORTER
        ASSIMP_BUILD_NO_IRR_IMPORTER
        ASSIMP_BUILD_NO_Q3D_IMPORTER
        ASSIMP_BUILD_NO_B3D_IMPORTER
        ASSIMP_BUILD_NO_COLLADA_IMPORTER
        ASSIMP_BUILD_NO_TERRAGEN_IMPORTER
        ASSIMP_BUILD_NO_CSM_IMPORTER
        ASSIMP_BUILD_NO_3D_IMPORTER
        ASSIMP_BUILD_NO_LWS_IMPORTER
        ASSIMP_BUILD_NO_OGRE_IMPORTER
        ASSIMP_BUILD_NO_OPENGEX_IMPORTER
        ASSIMP_BUILD_NO_MS3D_IMPORTER
        ASSIMP_BUILD_NO_COB_IMPORTER
        ASSIMP_BUILD_NO_BLEND_IMPORTER
        ASSIMP_BUILD_NO_Q3BSP_IMPORTER
        ASSIMP_BUILD_NO_NDO_IMPORTER
        ASSIMP_BUILD_NO_IFC_IMPORTER
        ASSIMP_BUILD_NO_XGL_IMPORTER
        ASSIMP_BUILD_NO_FBX_IMPORTER
        ASSIMP_BUILD_NO_ASSBIN_IMPORTER
        ASSIMP_BUILD_NO_GLTF_IMPORTER
        ASSIMP_BUILD_NO_C4D_IMPORTER
        ASSIMP_BUILD_NO_3MF_IMPORTER
        ASSIMP_BUILD_NO_X3D_IMPORTER
        ASSIMP_BUILD_NO_MMD_IMPORTER
        )


target_include_directories(assimp
        PRIVATE ${ASSIMP_DIR}
        PRIVATE ${ASSIMP_DIR}/code
        PRIVATE ${ASSIMP_DIR}/include
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

target_include_directories(assimp
        SYSTEM INTERFACE ${ASSIMP_DIR}/code
        SYSTEM INTERFACE ${ASSIMP_DIR}/include
        )

target_link_libraries(assimp PUBLIC IrrXML)