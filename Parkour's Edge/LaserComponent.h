#include "MeshComponent.h"
#include "SegmentCast.h"
#include <vector>


class LaserComponent : public MeshComponent
{
public:
    LaserComponent(class Actor* inOwner);
    void Draw(class Shader* shader);
    void Update(float deltaTime);
    Matrix4 transformHelper(LineSegment inLine);
private:
    std::vector<LineSegment> mLines;
};
