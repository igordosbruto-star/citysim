#include "Panels/PropertiesPanel.hpp"
#include <wx/propgrid/advprops.h>

namespace CitySim::Editor {

PropertiesPanel::PropertiesPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY) {
    // Criar notebook para separar propriedades
    m_notebook = new wxNotebook(this, wxID_ANY);
    
    // Criar páginas para diferentes tipos de propriedades
    m_tileProperties = new wxPropertyGrid(m_notebook, wxID_ANY);
    m_zoneProperties = new wxPropertyGrid(m_notebook, wxID_ANY);
    
    m_notebook->AddPage(m_tileProperties, "Tile");
    m_notebook->AddPage(m_zoneProperties, "Zone");
    
    // Configurar layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);
    
    // Configurar propriedades
    setupTileProperties();
    setupZoneProperties();
    
    // Vincular eventos
    m_tileProperties->Bind(wxEVT_PG_CHANGED, &PropertiesPanel::onPropertyChange, this);
    m_zoneProperties->Bind(wxEVT_PG_CHANGED, &PropertiesPanel::onPropertyChange, this);
}

void PropertiesPanel::setupTileProperties() {
    // Categoria de Posição
    m_tileProperties->Append(new wxPropertyCategory("Position"));
    m_tileProperties->Append(new wxIntProperty("X", "x", 0));
    m_tileProperties->Append(new wxIntProperty("Y", "y", 0));
    
    // Categoria de Visual
    m_tileProperties->Append(new wxPropertyCategory("Visual"));
    m_tileProperties->Append(new wxIntProperty("Tile ID", "tile_id", 0));
    m_tileProperties->Append(new wxEnumProperty("Layer", "layer",
        wxArrayString({"Ground", "Objects", "Overlay"})));
}

void PropertiesPanel::setupZoneProperties() {
    // Categoria de Zona
    m_zoneProperties->Append(new wxPropertyCategory("Zone"));
    m_zoneProperties->Append(new wxEnumProperty("Type", "zone_type",
        wxArrayString({"None", "Residential", "Commercial", "Industrial"})));
    m_zoneProperties->Append(new wxIntProperty("Level", "level", 0));
    m_zoneProperties->Append(new wxFloatProperty("Happiness", "happiness", 1.0));
}

void PropertiesPanel::updateForTile(const sf::Vector2i& position) {
    m_tileProperties->GetProperty("x")->SetValue(position.x);
    m_tileProperties->GetProperty("y")->SetValue(position.y);
    
    // TODO: Buscar informações do tile na posição e atualizar outras propriedades
    m_tileProperties->Refresh();
}

void PropertiesPanel::updateForZone(const sf::Vector2i& position) {
    // TODO: Buscar informações da zona na posição e atualizar propriedades
    m_zoneProperties->Refresh();
}

void PropertiesPanel::clearProperties() {
    m_tileProperties->ClearModifiedStatus();
    m_zoneProperties->ClearModifiedStatus();
    
    // Resetar valores para padrão
    m_tileProperties->GetProperty("x")->SetValue(0);
    m_tileProperties->GetProperty("y")->SetValue(0);
    m_tileProperties->GetProperty("tile_id")->SetValue(0);
    m_tileProperties->GetProperty("layer")->SetValue(0);
    
    m_zoneProperties->GetProperty("zone_type")->SetValue(0);
    m_zoneProperties->GetProperty("level")->SetValue(0);
    m_zoneProperties->GetProperty("happiness")->SetValue(1.0);
}

void PropertiesPanel::onPropertyChange(wxPropertyGridEvent& event) {
    wxPGProperty* property = event.GetProperty();
    if (!property) return;
    
    const wxString& name = property->GetName();
    wxVariant value = property->GetValue();
    
    // TODO: Atualizar o tile/zona com os novos valores
}

} // namespace CitySim::Editor