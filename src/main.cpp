// #include "src/Cell.h"
// #include "src/Edge.h"
// #include "src/Vertex.h"
// #include "src/Face.h"
#include "src/Mesh.h"
#include <iostream>



int main(int argc, char const *argv[])
{
    Mesh * mesh=new Mesh();
    //mesh->create_mesh("../data/Hex.lyq");

    //输出所有点：
    for(auto it=mesh->vertices()->begin();it!=mesh->vertices()->end();++it){
        std::cout<<(*it)->idx()<<" ("<<(*it)->x()<<","<<(*it)->y()<<","<<(*it)->z()<<")"<<std::endl;
    }

    for(auto it=mesh->faces()->begin();it!=mesh->faces()->end();++it){
        std::cout<<(*it)->idx()<<" "<<(*it)->boundary()<< std::endl;
    }

    
    
    return 0;
}
