#include "HierarchyPanel.h"

#include "../vendor/imgui/imgui.h"
#include <CBT/Application.h>

//#include "InspectorPanel.h"

//#include "../../Entities.h"
//#include <Wiwa/Resources.h>
//
//#include <Wiwa/ecs/systems/SpriteRenderer.h>
//
//#include "ScenePanel.h"
//#include "../EditorLayer.h"


#include "HierarchyPanel.h"
#include <list>
#include <algorithm>

#include "CBT/Application.h"
//#include "Lanna/GameObject/GameObject.h"


    HierarchyPanel::HierarchyPanel() : Panels("SceneObjects")
    {

    }
    HierarchyPanel::~HierarchyPanel()
    {
    }
    void HierarchyPanel::Draw()
    {
        //std::vector<GameObject*> entities = *CBT::Application::Get().GetEntityManager()->GetEntityList();

        ImGui::Begin("Scene objects", &active);

        static int selected = 0;
        {


            /*for (int i = 0; i < entities.size(); i++)
            {
                if (ImGui::Selectable(entities.at(i)->m_Name.c_str(), selected == i))
                    selected = i;
            }*/

           // CBT::Application::Get().GetEntityManager()->SetActiveEntity(selected);
        }
        ImGui::End();
    }