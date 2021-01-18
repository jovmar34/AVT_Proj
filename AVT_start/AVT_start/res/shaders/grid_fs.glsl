#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;
in vec3 view_pos;

out vec4 FragmentColor;

precision highp float;

const float gridSize = 100;
const float gridLineWidth = 2.0;
const vec3  gridColor = vec3(1,1,1);
const float gridAlpha = 0.5;

const float axisLineWidth = 3.0;
const vec3 xAxisColor = vec3(1,0,0);
const vec3 yAxisColor = vec3(0,1,0);
const float axisAlpha = 0.8;

const float alphaFalloff = 2;

void main()
{
    //grid properties
    vec2 uv = exTexcoord;
    float squareSize = 1 / gridSize;

    // angle alpha falloff
    vec3 normal = normalize(exNormal);
    vec3 view_dir = normalize(-exPosition);
    float angleAlpha = pow(max(abs(dot(normal, view_dir)), 0.1), alphaFalloff);
    float gridAlpha = gridAlpha * angleAlpha;
    float axisAlpha = axisAlpha * angleAlpha;

    // calculate deriviatives
    float dXy = abs(dFdx(uv.y)) / 2.0;
    float dYy = abs(dFdy(uv.y)) / 2.0;
    float dXx = abs(dFdx(uv.x)) / 2.0;
    float dYx = abs(dFdy(uv.x)) / 2.0;

    // x lines
    int roundPos = int(uv.y / squareSize);
    float remainder = uv.y - float(roundPos)*squareSize;
    float width = max(dYy, dXy) * gridLineWidth;

    if (remainder <= width)
    {
        float diff = (width - remainder) / width;
        FragmentColor += vec4(gridColor, diff * gridAlpha);
    }

    if (remainder >= (squareSize - width))
    {
        float diff = (remainder - squareSize + width) / width;
        FragmentColor += vec4(gridColor, diff * gridAlpha);
    }

    // x axis
    float dist = abs(0.5 - uv.y);
    width = max(dYy, dXy) * axisLineWidth;
    if(dist < width){
        FragmentColor = vec4(xAxisColor,axisAlpha);
        return;
    }


    // y lines
    roundPos = int(uv.x / squareSize);
    remainder = uv.x - float(roundPos)*squareSize;
    width = max(dYx, dXx) * gridLineWidth;

    if (remainder <= width)
    {
        float diff = (width - remainder) / width;
        FragmentColor += vec4(gridColor, diff * gridAlpha);
    }

    if (remainder >= (squareSize - width))
    {
        float diff = (remainder - squareSize + width) / width;
        FragmentColor += vec4(gridColor, diff * gridAlpha);
    }

    // y axis
    dist = abs(0.5 - uv.x);
    width = max(dYx, dXx) * axisLineWidth;
    if(dist < width){
        FragmentColor = vec4(yAxisColor,axisAlpha);
        return;
    }

    return;
}

