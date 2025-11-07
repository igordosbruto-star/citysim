#pragma once

#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/propgrid/propgrid.h>

namespace CitySim::Editor {

class PropertiesPanel : public wxPanel {
public:
    PropertiesPanel(wxWindow* parent);
    
    void updateForTile(const sf::Vector2i& position);
    void updateForZone(const sf::Vector2i& position);
    void clearProperties();
    
private:
    wxNotebook* m_notebook;
    wxPropertyGrid* m_tileProperties;
    wxPropertyGrid* m_zoneProperties;
    
    // Configuração dos painéis
    void setupTileProperties();
    void setupZoneProperties();
    
    // Event handlers
    void onPropertyChange(wxPropertyGridEvent& event);
};

} // namespace CitySim::Editor