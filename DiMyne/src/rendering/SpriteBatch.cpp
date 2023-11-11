#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(){
    old = std::vector<size_t>();
    queue = std::vector<QueueEntry>();
    VBOs = std::vector<GLuint>();
}

void SpriteBatch::addDefualtShader(Shader* shader){
    defaultShader = shader;
    activeShader = defaultShader;
}

void SpriteBatch::addFontShader(Shader* shader){
    fontShader = shader;
}

Shader* SpriteBatch::activateDefault(){
    activeShader = defaultShader;
    return activeShader;
}

Shader* SpriteBatch::activateFont(){
    activeShader = fontShader;
    return activeShader;
}

void SpriteBatch::draw(Texture texture, Rectangle source, 
            Rectangle destination, Color color){
    if(queue.size() == 0){
        QueueEntry temp = QueueEntry(texture, activeShader);
        temp.add(source, destination, color);
        queue.push_back(temp);
    }
    else if(queue.back().texture.id() == texture.id() && activeShader->ID == queue.back().shader->ID){;
        queue.back().add(source, destination, color);
    }
    else{
        QueueEntry temp = QueueEntry(texture, activeShader);
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

    //bind VAO
    glBindVertexArray(activeShader->VAO);

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
            std::cout << "[DiMyne] Creating new buffer..." << std::endl;
            GLuint temp;
            glGenBuffers(1, &temp);

            std::cout << "[DiMyne] Buffer created: VBO " << temp << std::endl;

            VBOs.push_back(temp);
        }

        //unbind VAO
        glBindVertexArray(0);
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

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
            NULL);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
            8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
            (void*)(4 * sizeof(GLfloat)));
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

/// @brief Fletcher 16-bit hash function
/// @param vertex vertex to hash
/// @return hash of the vertex
size_t SpriteBatch::getHash(Vertex vertex){
    size_t result = 0;
    size_t sum1 = 0;
    size_t sum2 = 0;

    uint32_t addler = 65521;

    sum1 = fmod((sum1 + vertex.x), addler);
    sum2 = fmod((sum2 + sum1), addler);

    sum1 = fmod((sum1 + vertex.y), addler);
    sum2 = fmod((sum2 + sum1), addler);

    sum1 = fmod((sum1 + vertex.u), addler);
    sum2 = fmod((sum2 + sum1), addler);

    sum1 = fmod((sum1 + vertex.v), addler);
    sum2 = fmod((sum2 + sum1), addler);

    result = (sum2 << 16) | sum1;

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
    //change color values to floats
    GLfloat* colors = color.toFloats();

    glClearColor(colors[0], colors[1], colors[2], colors[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    delete[] colors;
    colors = nullptr;
}