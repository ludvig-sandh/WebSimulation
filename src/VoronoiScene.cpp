#include "VoronoiScene.h"

#define JC_VORONOI_IMPLEMENTATION
#include "jc_voronoi.h"
#include <iostream>
#include <algorithm>
#include <random>

std::random_device rd;  // Seed generator
std::mt19937 gen(rd()); // Mersenne Twister engine
std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Range [0, 1)

VoronoiScene::VoronoiScene(const Vec2 screenSize) : Scene(screenSize) {
    int numPointsToPrespawn = 20000;
    for (int i = 0; i < numPointsToPrespawn; i++) {
        m_points.push_back(Vec2(dist(gen) * m_screenSize.x, dist(gen) * m_screenSize.y));
    }
    ComputeVoronoiDiagram();
}

void VoronoiScene::Update(float timeDelta) {
    // ComputeVoronoiDiagram();
}

void VoronoiScene::ComputeVoronoiDiagram() {
    for (auto &object : polies) {
        RemoveObject(object);
    }
    polies.clear();

    jcv_rect bounding_box = { { 0.0f, 0.0f }, { m_screenSize.x, m_screenSize.y } };
    jcv_diagram diagram;
    jcv_point points[m_points.size()];
    const jcv_site* sites;
    jcv_graphedge* graph_edge;

    memset(&diagram, 0, sizeof(jcv_diagram));

    for (size_t i = 0; i < m_points.size(); i++) {
        points[i].x = m_points[i].x;
        points[i].y = m_points[i].y;
    }

    jcv_diagram_generate(m_points.size(), (const jcv_point *)points, &bounding_box, 0, &diagram);

    sites = jcv_diagram_get_sites(&diagram);
    for (int i = 0; i < diagram.numsites; i++) {
        std::vector<Vec2> ps;
        graph_edge = sites[i].edges;
        while (graph_edge) {
            // This approach will potentially print shared edges twice
            ps.emplace_back(graph_edge->pos[0].x, graph_edge->pos[0].y);
            graph_edge = graph_edge->next;
        }
        Vec2 center = Vec2(sites[i].p.x, sites[i].p.y);
        Vec3 color;
        if (colors.find(center) == colors.end()) {
            color = Vec3(dist(gen), 0.0, dist(gen));
            colors[center] = color;
        }else {
            color = colors[center];
        }
        try {
            auto poly = std::make_shared<SceneConvexPolygon>(Vec2(0, 0), ps, color.x, color.y, color.z);
            AddObject(poly);
            polies.push_back(poly);
        }catch (std::runtime_error &e) {
            // Pass
        }
    }

    jcv_diagram_free(&diagram);
}

void VoronoiScene::MouseUpdate(Vec2 mouseLocation, bool isButtonDown) {
    // if (!mouseDownLast && isButtonDown) {
    //     // Click
    //     m_points.push_back(mouseLocation);
    //     ComputeVoronoiDiagram();
    // }
    // mouseDownLast = isButtonDown;

    for (auto &obj : polies) {
        bool contains = obj->Contains(mouseLocation);
        if (isButtonDown) {
            if (contains) {
                RemoveObject(obj);
            }
        }
        obj->color.y = contains ? 1.0 : 0.0;
    }
}