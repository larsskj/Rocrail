///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 21 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "waybilldlggen.h"

///////////////////////////////////////////////////////////////////////////

waybillgen::waybillgen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_WaybillBook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_IndexPanel = new wxPanel( m_WaybillBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_WaybillList = new wxListBox( m_IndexPanel, wxID_ANY, wxDefaultPosition, wxSize( -1,200 ), 0, NULL, 0 ); 
	bSizer2->Add( m_WaybillList, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_NewWaybill = new wxButton( m_IndexPanel, wxID_ANY, wxT("New"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_NewWaybill, 0, wxALL, 5 );
	
	m_DeleteWaybill = new wxButton( m_IndexPanel, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_DeleteWaybill, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, 0, 5 );
	
	m_IndexPanel->SetSizer( bSizer2 );
	m_IndexPanel->Layout();
	bSizer2->Fit( m_IndexPanel );
	m_WaybillBook->AddPage( m_IndexPanel, wxT("Index"), true );
	m_GeneralPanel = new wxPanel( m_WaybillBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labID = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("ID"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labID->Wrap( -1 );
	fgSizer1->Add( m_labID, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_ID = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_ID, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_labShipper = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("Shipper"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labShipper->Wrap( -1 );
	fgSizer1->Add( m_labShipper, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_Shipper = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_Shipper, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labShipperAddr = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("Address"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labShipperAddr->Wrap( -1 );
	fgSizer1->Add( m_labShipperAddr, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_ShipperAddr = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_ShipperAddr, 0, wxALL|wxEXPAND, 5 );
	
	m_labConsignee = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("Consignee"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labConsignee->Wrap( -1 );
	fgSizer1->Add( m_labConsignee, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_Consignee = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_Consignee, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labConsigneeAddr = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("Address"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labConsigneeAddr->Wrap( -1 );
	fgSizer1->Add( m_labConsigneeAddr, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_ConsigneeAddr = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_ConsigneeAddr, 0, wxALL|wxEXPAND, 5 );
	
	m_labCargo = new wxStaticText( m_GeneralPanel, wxID_ANY, wxT("Cargo"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labCargo->Wrap( -1 );
	fgSizer1->Add( m_labCargo, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_Cargo = new wxTextCtrl( m_GeneralPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	fgSizer1->Add( m_Cargo, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer4->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	m_GeneralPanel->SetSizer( bSizer4 );
	m_GeneralPanel->Layout();
	bSizer4->Fit( m_GeneralPanel );
	m_WaybillBook->AddPage( m_GeneralPanel, wxT("General"), false );
	m_RoutingPanel = new wxPanel( m_WaybillBook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	bSizer5->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_RoutingPanel->SetSizer( bSizer5 );
	m_RoutingPanel->Layout();
	bSizer5->Fit( m_RoutingPanel );
	m_WaybillBook->AddPage( m_RoutingPanel, wxT("Routing"), false );
	
	bSizer1->Add( m_WaybillBook, 1, wxEXPAND | wxALL, 5 );
	
	m_stdButton = new wxStdDialogButtonSizer();
	m_stdButtonOK = new wxButton( this, wxID_OK );
	m_stdButton->AddButton( m_stdButtonOK );
	m_stdButtonApply = new wxButton( this, wxID_APPLY );
	m_stdButton->AddButton( m_stdButtonApply );
	m_stdButtonCancel = new wxButton( this, wxID_CANCEL );
	m_stdButton->AddButton( m_stdButtonCancel );
	m_stdButton->Realize();
	bSizer1->Add( m_stdButton, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	m_WaybillList->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( waybillgen::onWaybillList ), NULL, this );
	m_NewWaybill->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onNewWaybill ), NULL, this );
	m_DeleteWaybill->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onDeleteWaybill ), NULL, this );
	m_stdButtonApply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onApply ), NULL, this );
	m_stdButtonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onCancel ), NULL, this );
	m_stdButtonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onOK ), NULL, this );
}

waybillgen::~waybillgen()
{
	// Disconnect Events
	m_WaybillList->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( waybillgen::onWaybillList ), NULL, this );
	m_NewWaybill->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onNewWaybill ), NULL, this );
	m_DeleteWaybill->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onDeleteWaybill ), NULL, this );
	m_stdButtonApply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onApply ), NULL, this );
	m_stdButtonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onCancel ), NULL, this );
	m_stdButtonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( waybillgen::onOK ), NULL, this );
}
