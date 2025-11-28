# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Définition du projet
project(GrowAZ VERSION 1.0 LANGUAGES CXX)

# Spécifier la norme C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure le module pour télécharger du contenu externe
include(FetchContent)

# Indiquer à CMake où trouver nos modules de recherche personnalisés
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Essayer de trouver Raylib sur le système (sans afficher d'erreur s'il n'est pas trouvé)
find_package(Raylib QUIET)

# Si Raylib n'est pas trouvé, le télécharger et le compiler
if(NOT Raylib_FOUND)
    message(STATUS "Raylib non trouvée. Téléchargement depuis GitHub...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0 # On utilise une version stable de Raylib
    )
    # Désactiver la compilation des exemples de Raylib pour accélérer le processus
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
else()
    message(STATUS "Raylib trouvée sur le système : ${RAYLIB_LIBRARIES}")
endif()

# Créer l'exécutable à partir de main.cpp
add_executable(GrowAZ src/main.cpp)

# Lier la bibliothèque Raylib à notre exécutable.
# Cela fonctionne que Raylib ait été trouvée localement ou téléchargée,
# car dans les deux cas, une cible nommée "raylib" est disponible.
target_link_libraries(GrowAZ PRIVATE raylib)
