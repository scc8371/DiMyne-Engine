#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(Shader* shader){
    this->shader = shader;
    old = std::vector<size_t>();
    queue = std::vector<QueueEntry>();
    VBOs = std::vector<GLuint>();
}

void SpriteBatch::draw(Texture texture, Rectangle source, Rectangle destination, Color color){
    if(queue.size() == 0){
        QueueEntry temp = QueueEntry(texture, shader);
        temp.add(source, destination, color);
        queue.push_back(temp);
    }
    else if(queue.back().texture.id() == texture.id() && shader->ID == queue.back().shader->ID){
        queue.back().add(source, destination, color);
    }
    else{
        QueueEntry temp = QueueEntry(texture, shader);
        temp.add(source, destination, color);
        queue.push_back(temp);
    }
}

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat u, GLfloat v, Color color){
    this->x = x;
    this->y = y;
    this->u = u;
    this->v = v;

    GLfloat* colors = color.toFloats();
    this->r = colors[0];
    this->g = colors[1];
    this->b = colors[2];
    this->a = colors[3];

    delete[] colors;
    colors = nullptr;
}

void SpriteBatch::render(){
    int oSize = old.size();
    int qSize = queue.size();

    //update old
    for(int i = 0; i < qSize; i++){
        if(i > oSize - 1){
            queue[i].isUpdated = true;
            continue;
        }
        //check if the queue entry is updated
        if(old[i] != getHash(queue[i])){
            queue[i].isUpdated = true;
            continue;
        }
        //not updated because the hash is the same
        queue[i].isUpdated = false;
    }

    //update VBOs
    while(!(VBOs.size() == queue.size())){
        if(VBOs.size() > queue.size()){
            //delete buffers of VBO at the back
            glDeleteBuffers(1, &VBOs.back());
            VBOs.pop_back();
        }
        else{
            //create new buffer
            GLuint temp;
            glGenBuffers(1, &temp);
            VBOs.push_back(temp);
        }
    }

    //clear old VBOs
    old.clear();

    //render queue
    for(int i = 0; i < qSize; i++){
        queue[i].shader->use();
        queue[i].texture.bind();
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

        if(queue[i].isUpdated){
            glBufferData(GL_ARRAY_BUFFER, (queue[i].quads.size() + 1) 
                * sizeof(Vertex), &queue[i].quads[0], GL_DYNAMIC_DRAW);
        }

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        //unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, queue[i].quads.size());

        old.push_back(getHash(queue[i]));
        queue[i].isUpdated = false;
    }

    queue.clear();
}

size_t SpriteBatch::getHash(QueueEntry entry){
    size_t result = entry.texture.id();

    for(int i = 0; i < entry.quads.size(); i++){
        result = (result << 1) ^ getHash(entry.quads[i]);
    }

    return result;
}

size_t SpriteBatch::getHash(Vertex vertex){
    size_t result = *(size_t*)&vertex.x;
    result ^= *(size_t*)&vertex.y << 1;
    result ^= *(size_t*)&vertex.u << 2;
    result ^= *(size_t*)&vertex.v << 3;

    return result;
}

SpriteBatch::QueueEntry::QueueEntry(Texture texture, Shader* shader) : texture(texture), shader(shader){
    quads = std::vector<Vertex>();
}

void SpriteBatch::QueueEntry::add(Rectangle source, Rectangle destination, Color color){
    Vertex temp[6] = {
        Vertex(destination.x, destination.y, source.x, source.y, color),
        Vertex(destination.x + destination.width, destination.y, source.x + source.width, source.y, color),
        Vertex(destination.x + destination.width, destination.y + destination.height, source.x + source.width, source.y + source.height, color),
        Vertex(destination.x, destination.y, source.x, source.y, color),
        Vertex(destination.x + destination.width, destination.y + destination.height, source.x + source.width, source.y + source.height, color),
        Vertex(destination.x, destination.y + destination.height, source.x, source.y + source.height, color)
    };

    for(int i = 0; i < 6; i++){
        quads.push_back(temp[i]);
    }
}

void SpriteBatch::colorWindow(Color color){
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SpriteBatch::colorWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}