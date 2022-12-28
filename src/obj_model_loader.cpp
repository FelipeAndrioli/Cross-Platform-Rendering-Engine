#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "./math.h"
/*

OBJ Data Format 

The following types of data may be included in an .obj file.

## Vertex Data
v       -> geometric vertices
vt      -> texture vertices
vn      -> vertex normals
vp      -> parameter space vertices
cstype  -> rational or non-rational forms of curve of surface type: basis matrix, 
          Bezier, B-spline, Cardinal, Taylor
deg     -> degree
bmat    -> basis matrix
step    -> step size

## Elements
p       -> point
l       -> line
f       -> face
curv    -> curve
curv2   -> 2D curve
surf    -> surface

## Free-form curve/surface body statements
parm    -> parameter values
trim    -> outer trimming loop
hole    -> inner trimming loop
scrv    -> special curve
sp      -> special point
end     -> end statement

## Connectivity between free-form surfaces
con     -> connect

## Grouping 
g       -> group name
s       -> smoothing group
mg      -> merging group
o       -> object name

## Display/render attributes
bevel   -> bevel interpolation
c_interp    -> color interpolation
d_interp    -> dissolve interpolation
lod     -> level of detail
usemtl  -> material name
mtllib  -> material library
shadow_obj  -> shadow casting
trace_obj   -> ray tracing
ctech   -> curve approximation technique
stech   -> surface approximation technique
*/

typedef enum {
    v         ,
    vt        ,
    vn        ,
    vp        ,
    cstype    ,
    deg       ,
    bmat      ,
    step      ,
    p         ,
    l         ,
    f         ,
    curv      ,
    curv2     ,
    surf      ,
    parm      ,
    trim      ,
    hole      ,
    scrv      ,
    sp        ,
    end       ,
    con       ,
    g         ,
    s         ,
    mg        ,
    o         ,
    bevel     ,
    c_interp  ,
    d_interp  ,
    lod       ,
    usemtl    ,
    mtllib    ,
    shadow_obj,
    trace_obj ,
    ctech     ,
    stech     ,
    invalid
} obj_identifier;

obj_identifier handleInput(std::string input) {
    if (input == "v")           return obj_identifier::v;
    if (input == "vt")          return obj_identifier::vt;
    if (input == "vn")          return obj_identifier::vn;
    if (input == "vp")          return obj_identifier::vp;
    if (input == "cstype")      return obj_identifier::cstype;
    if (input == "deg")         return obj_identifier::deg;
    if (input == "bmat")        return obj_identifier::bmat;
    if (input == "step")        return obj_identifier::step;
    if (input == "p")           return obj_identifier::p;
    if (input == "l")           return obj_identifier::l;
    if (input == "f")           return obj_identifier::f;
    if (input == "curv")        return obj_identifier::curv;
    if (input == "curv2")       return obj_identifier::curv2;
    if (input == "surf")        return obj_identifier::surf;
    if (input == "parm")        return obj_identifier::parm;
    if (input == "trim")        return obj_identifier::trim;
    if (input == "hole")        return obj_identifier::hole;
    if (input == "scrv")        return obj_identifier::scrv;
    if (input == "sp")          return obj_identifier::sp;
    if (input == "end")         return obj_identifier::end;
    if (input == "con")         return obj_identifier::con;
    if (input == "g")           return obj_identifier::g;
    if (input == "s")           return obj_identifier::s;
    if (input == "mg")          return obj_identifier::mg;
    if (input == "o")           return obj_identifier::o;
    if (input == "bevel")       return obj_identifier::bevel;
    if (input == "c_interp")    return obj_identifier::c_interp;
    if (input == "d_interp")    return obj_identifier::d_interp;
    if (input == "lod")         return obj_identifier::lod;
    if (input == "usemtl")      return obj_identifier::usemtl;
    if (input == "mtllib")      return obj_identifier::mtllib;
    if (input == "shadow_obj")  return obj_identifier::shadow_obj;
    if (input == "trace_obj")   return obj_identifier::trace_obj;
    if (input == "ctech")       return obj_identifier::ctech;
    if (input == "stech")       return obj_identifier::stech;

    return obj_identifier::invalid;
}

void log(const char *message) {
    std::cout << message << std::endl;
}

void log(unsigned int value) {
    std::cout << value << std::endl;
}

void log(math::vec3 v) {
    std::cout << "x -> " << v.x << " y -> " << v.y << " z -> " << v.z << std::endl; 
}

void log(math::vec2 v) {
    std::cout << "x -> " << v.x << " y -> " << v.y << std::endl; 
}

void log(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
}

void log(std::vector<math::vec3> &vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        log(vertices.at(i));
    }
}

void log(std::vector<math::vec2> &vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        log(vertices.at(i));
    }
}

void log(std::vector<std::vector<int>> faces) {
    for (int i = 0; i < faces.size(); i++) {
        for (int j = 0; j < faces[i].size(); j++) {
            std::cout << faces[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

math::vec2 splitVec2(std::string line) {
    math::vec2 vec;
    std::string delimiter = " ";
    std::string raw = line;
    std::string token;
    std::size_t pos = raw.find(delimiter);

    token = raw.substr(0, pos);
    raw.erase(0, pos + delimiter.length());

    vec.x = std::stof(token);
    vec.y = std::stof(raw);

    return vec;
}

math::vec3 splitVec3(std::string line) {
    math::vec3 vec;
    std::string delimiter = " ";
    std::string raw = line;
    std::string token;
    std::size_t pos = 0;
    int count = 0;

    while ((pos = raw.find(delimiter)) != std::string::npos) {
        token = raw.substr(0, pos);
        raw.erase(0, pos + delimiter.length());

        if (count == 0)
            vec.x = std::stof(token);
        if (count == 1)
            vec.y = std::stof(token);
        count++;
    }

    vec.z = std::stof(raw);

    return vec;
}

std::vector<int> splitFaces(std::string line) {
    std::vector<int> vec;
    std::string space_delimiter = " ";
    std::string slash_delimiter = "/";
    std::string raw = line;
    std::string token;
    std::string value;
    std::size_t pos_outer = 0;
    std::size_t pos_inner = 0;

    while ((pos_outer = raw.find(space_delimiter)) != std::string::npos) {
        token = raw.substr(0, pos_outer);
        raw.erase(0, pos_outer + space_delimiter.length());

        while ((pos_inner = token.find(slash_delimiter)) != std::string::npos) {
            value = token.substr(0, pos_inner);
            token.erase(0, pos_inner + slash_delimiter.length());
            vec.push_back(std::stoi(value));
        }
    }

    return vec;
}

void showSummary(std::map<std::string, int> summary) {
    std::map<std::string, int>::iterator it;

    log("--- Summary of the file ---");

    for (it = summary.begin(); it != summary.end(); it++) {
        log((it->first + " -> " + std::to_string(it->second)).c_str()); 
    }
}

void processV(std::vector<math::vec3> &vertices, std::string line) { 
    vertices.push_back(splitVec3(line.substr(2, line.length())));
}

void processVt(std::vector<math::vec2> &tex_coords, std::string line) { 
    tex_coords.push_back(splitVec2(line.substr(3, line.length())));
}

void processVn(std::vector<math::vec3> &normals, std::string line) { 
    normals.push_back(splitVec3(line.substr(3, line.length())));
}

void processF(std::vector<std::vector<int>> faces, std::string line) {
    faces.push_back(splitFaces(line.substr(2, line.length())));
}

int main() {

    //const char *path = "./Intergalatic_Spaceship/Intergalactic_Spaceship.obj";
    const char *path = "./Box/Weapon box.obj";
    std::ifstream file (path);
    std::string line;
    std::string delimiter = " ";
    std::map<std::string, int> summary;

    std::vector<math::vec3> vertices;
    std::vector<math::vec2> tex_coords;
    std::vector<math::vec3> normals;
    std::vector<std::vector<int>> faces;

    while (getline(file, line)) {
        std::string identifier = line.substr(0, line.find(delimiter));

        switch (handleInput(identifier)) {
            case obj_identifier::v:
                summary["v"]++;
                processV(vertices, line);
                break;
            case obj_identifier::vt:
                summary["vt"]++;
                processVt(tex_coords, line);
                break;
            case obj_identifier::vn:
                summary["vn"]++;
                processVn(normals, line);
                break;
            case obj_identifier::vp:
                summary["vp"]++;
                break;
            case obj_identifier::cstype:
                summary["cstype"]++;
                break;
            case obj_identifier::deg:
                summary["deg"]++;
                break;
            case obj_identifier::bmat:
                summary["bmat"]++;
                break;
            case obj_identifier::step:
                summary["step"]++;
                break;
            case obj_identifier::p:
                summary["p"]++;
                break;
            case obj_identifier::l:
                summary["l"]++;
                break;
            case obj_identifier::f:
                summary["f"]++;
                processF(faces, line);
                break;
            case obj_identifier::curv:
                summary["curv"]++;
                break;
            case obj_identifier::curv2:
                summary["curv2"]++;
                break;
            case obj_identifier::surf:
                summary["surf"]++;
                break;
            case obj_identifier::parm:
                summary["parm"]++;
                break;
            case obj_identifier::trim:
                summary["trim"]++;
                break;
            case obj_identifier::hole:
                summary["hole"]++;
                break;
            case obj_identifier::scrv:
                summary["scrv"]++;
                break;
            case obj_identifier::sp:
                summary["sp"]++;
                break;
            case obj_identifier::end:
                summary["end"]++;
                break;
            case obj_identifier::con:
                summary["con"]++;
                break;
            case obj_identifier::g:
                summary["g"]++;
                break;
            case obj_identifier::s:
                summary["s"]++;
                break;
            case obj_identifier::mg:
                summary["mg"]++;
                break;
            case obj_identifier::o:
                summary["o"]++;
                break;
            case obj_identifier::bevel:
                summary["bevel"]++;
                break;
            case obj_identifier::c_interp:
                summary["c_interp"]++;
                break;
            case obj_identifier::d_interp:
                summary["d_interp"]++;
                break;
            case obj_identifier::lod:
                summary["lod"]++;
                break;
            case obj_identifier::usemtl:
                summary["usemtl"]++;
                break;
            case obj_identifier::mtllib:
                summary["mtllib"]++;
                break;
            case obj_identifier::shadow_obj:
                summary["shadow_obj"]++;
                break;
            case obj_identifier::trace_obj:
                summary["trace_obj"]++;
                break;
            case obj_identifier::ctech:
                summary["ctech"]++;
                break;
            case obj_identifier::stech:
                summary["stech"]++;
                break;
            default:
                summary["invalid"]++;
                break;
        }
    }

    file.close();

    //showSummary(summary);
    log(faces.size());

    return 0;
}
