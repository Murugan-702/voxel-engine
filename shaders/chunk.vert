#version 330 core

layout(location = 0) in uint packed_data;
int x ,y ,z;

int flip_id;
int ao_id;

uniform mat4 m_proj;
uniform mat4 m_view;
uniform mat4 m_model;

flat out int voxel_id;
flat out int face_id;

out vec3 voxel_color;
out vec2 uv;
out float shading;

// Constants
const float ao_values[4] = float[4](0.1, 0.25, 0.5, 1.0);
const float face_shading[6] = float[6](1.0, 0.5, 0.5, 0.8, 0.5, 0.8);
const vec2 uv_coords[4] = vec2[4](
    vec2(0.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 0.0),
    vec2(1.0, 1.0)
);
const int uv_indices[24] = int[24](
    1, 0, 2, 1, 2, 3,  // flip = 0
    3, 0, 2, 3, 1, 0,  // flip = 1
    3, 1, 0, 3, 0, 2,  // flip = 2
    1, 2, 3, 1, 0, 2   // flip = 3
);

// Hash function for color generation
vec3 hash31(float p) {
    vec3 p3 = fract(vec3(p * 21.2) * vec3(0.1031, 0.1030, 0.0973));
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.xxy + p3.yyz) * p3.zyx) + 0.05;
}

// Unpacking function
void unpack(uint data) {
    const uint b_bit = 6u, c_bit = 6u, d_bit = 8u, e_bit = 3u, f_bit = 2u, g_bit = 1u;
    const uint b_mask = (1u << b_bit) - 1u;
    const uint c_mask = (1u << c_bit) - 1u;
    const uint d_mask = (1u << d_bit) - 1u;
    const uint e_mask = (1u << e_bit) - 1u;
    const uint f_mask = (1u << f_bit) - 1u;
    const uint g_mask = 1u;

    uint fg_bit = f_bit + g_bit;
    uint efg_bit = e_bit + fg_bit;
    uint defg_bit = d_bit + efg_bit;
    uint cdefg_bit = c_bit + defg_bit;
    uint bcdefg_bit = b_bit + cdefg_bit;

    x = int(data >> bcdefg_bit);
    y = int((data >> cdefg_bit) & b_mask);
    z = int((data >> defg_bit) & c_mask);
    voxel_id = int((data >> efg_bit) & d_mask);
    face_id = int((data >> fg_bit) & e_mask);
    ao_id = int((data >> g_bit) & f_mask);
    flip_id = int(data & g_mask);
}

void main() {
    unpack(packed_data);
    vec3 in_position = vec3(x, y, z);

    // Determine UV index using face and flip
    int uv_index = gl_VertexID % 6 + ((face_id & 1) + flip_id * 2) * 6;
    uv = uv_coords[uv_indices[uv_index]];

    // Procedural voxel color from ID
    voxel_color = hash31(float(voxel_id));

    // Ambient Occlusion shading
    shading = face_shading[face_id] * ao_values[ao_id];

    // Final vertex position
    gl_Position = m_proj * m_view * m_model * vec4(in_position, 1.0);
}
