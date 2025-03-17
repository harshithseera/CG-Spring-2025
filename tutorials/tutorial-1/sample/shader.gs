#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 9) out;


void main() {
    vec3 newvertex1 = vec3(1.0, 1.0, 0.0);
    gl_Position = vec4(0.5 * newvertex1, 1.0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();

    gl_Position = vec4(0.5 * newvertex1, 1.0);
    EmitVertex();

    vec3 newvertex2 = vec3(0.0, 1.5, 0.0);
    gl_Position = vec4(0.5 * newvertex2, 1.0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    EndPrimitive();

}