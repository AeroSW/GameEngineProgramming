/home/uge/Documents/Projects/Class/4903_GE/ogre_src_v1-8-1/bin/OgreXMLConverter ./XML-Files/$1.mesh.xml
/home/uge/Documents/Projects/Class/4903_GE/ogre_src_v1-8-1/bin/OgreMeshUpgrader ./XML-Files/$1.mesh
mv ./XML-Files/$1.mesh ./Mesh-Files/
mv ./OgreMeshUpgrade.log ./$1MeshUpgrade.log
mv ./$1MeshUpgrade.log ./Log-Files/
mv ./OgreXMLConverter.log ./$1XMLConverter.log
mv ./$1XMLConverter.log ./Log-Files/
