#version 330 core
layout(location=0) out vec4 fragColor;
const vec3 gamma =vec3(2.2);
const vec3 inv_gamma = 1/gamma;
uniform sampler2DArray u_texture_array_0;
in vec3 voxel_color;
in vec2 uv;
in float shading;
flat in int face_id;
flat in int voxel_id;

void main(){
    vec2 face_uv = uv;
    face_uv.x = uv.x / 3.0 - min(face_id,2) / 3.0;
    vec3 text_col =texture(u_texture_array_0,vec3(face_uv,voxel_id)).rgb;
    text_col = pow(text_col,gamma);
    //text_col*=voxel_color;
    // text_col = text_col *0.001 + vec3(1);
    text_col*=shading;
    text_col = pow(text_col,inv_gamma);
    fragColor = vec4(text_col,1);
}