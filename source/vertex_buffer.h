void create_vertex_buffer(GLuint *p_vertex_array_id, GLuint *p_vertex_buffer_id) {
   GLuint vertex_array_id;
   glGenVertexArrays(1, &vertex_array_id);

   GLuint vertex_buffer_id;
   glGenBuffers(1, &vertex_buffer_id);

   float quad[] = {
       0.0,  0.0,   0.00, 0.33,
      16.0,  0.0,   0.12, 0.33,
      16.0, 16.0,   0.12, 0.0,

       0.0,  0.0,   0.00, 0.33,
      16.0, 16.0,   0.12, 0.00,
       0.0, 16.0,   0.00, 0.00
   };
   glBindVertexArray(vertex_array_id);
   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)2);
   glEnableVertexAttribArray(1);

   *p_vertex_array_id = vertex_array_id;
   *p_vertex_buffer_id = vertex_buffer_id;
}
