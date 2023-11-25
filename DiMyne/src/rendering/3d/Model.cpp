#include "Model.h"

Model::Model(const char *path, Color tint)
{
    loadModel(path);
    this->tint = tint;
};

void Model::draw()
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(MyneGlobals::depthShader);
    }
}

void Model::loadModel(std::string path)
{
    objl::Loader Loader;

    bool loaded = Loader.LoadFile(path);

    if (loaded)
    {
        // Go through each loaded mesh and out its contents
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
        {
            std::vector<Vertex3D> vertices;

            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            // Go through each vertex and print its number,
            //  position, normal, and texture coordinate
            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                Vertex3D vertex;
                glm::vec3 pos(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
                glm::vec3 normal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
                glm::vec2 texCoords(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y);
                
                //set position
                vertex.x = pos.x;
                vertex.y = pos.y;
                vertex.z = pos.z;
                
                //set normal values
                vertex.normalX = normal.x;
                vertex.normalY = normal.y;
                vertex.normalZ = normal.z;

                //set uv texture coordinate values
                vertex.u = texCoords.x;
                vertex.v = texCoords.y;

                vertices.push_back(vertex);
            }

            std::vector<unsigned int> indices;

            // Go through every 3rd index and print the
            //	triangle that these indices represent
            for (int j = 0; j < curMesh.Indices.size(); j++)
            {
                indices.push_back(curMesh.Indices[j]);
            }

            std::vector<Texture> textures;

            //Diffuse tex map
            if(curMesh.MeshMaterial.map_Kd != ""){
                Texture tex = Texture(curMesh.MeshMaterial.map_Ka.c_str());
                tex.texType = Texture::TexType::DIFFUSE;
                textures.push_back(tex);
            }

            //specular tex map
            if(curMesh.MeshMaterial.map_Ks != ""){
                Texture tex = Texture(curMesh.MeshMaterial.map_Ks.c_str());
                tex.texType = Texture::TexType::SPECULAR;
                textures.push_back(tex);
            }

            //normal tex map
            if(curMesh.MeshMaterial.map_bump != ""){
                Texture tex = Texture(curMesh.MeshMaterial.map_bump.c_str());
                tex.texType = Texture::TexType::NORMAL;
                textures.push_back(tex);
            }

            // file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
            // file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
            // file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
            // file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
            // file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
            // file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
            // file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
            // file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
            // file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

            meshes.push_back(Mesh(vertices, indices, textures));
        }
    }
    else
    {
        std::printf("[DiMyne] OBJ file failed to load!\n");
    }
}

void Model::rotate(float angle, glm::vec3 axis){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].rotate(angle, axis);
    }
}

void Model::scale(glm::vec3 scale){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].scale(scale);
    }
}

void Model::translate(glm::vec3 translation){
    for(int i = 0; i < meshes.size(); i++){
        meshes[i].translate(translation);
    }
}