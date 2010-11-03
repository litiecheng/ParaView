/*=========================================================================

  Program:   ParaView
  Module:    vtkSMRemoteObjectUpdateUndoElement.cxx

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkSMRemoteObjectUpdateUndoElement.h"

#include "vtkObjectFactory.h"
#include "vtkSMSession.h"
#include "vtkSMMessage.h"
#include "vtkSMRemoteObject.h"
#include "vtkCollection.h"

vtkStandardNewMacro(vtkSMRemoteObjectUpdateUndoElement);
//-----------------------------------------------------------------------------
vtkSMRemoteObjectUpdateUndoElement::vtkSMRemoteObjectUpdateUndoElement()
{
}

//-----------------------------------------------------------------------------
vtkSMRemoteObjectUpdateUndoElement::~vtkSMRemoteObjectUpdateUndoElement()
{
}

//-----------------------------------------------------------------------------
void vtkSMRemoteObjectUpdateUndoElement::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}
//-----------------------------------------------------------------------------
int vtkSMRemoteObjectUpdateUndoElement::Undo()
{
  return this->UpdateState(&this->BeforeState);
}

//-----------------------------------------------------------------------------
int vtkSMRemoteObjectUpdateUndoElement::Redo()
{
  return this->UpdateState(&this->AfterState);
}

//-----------------------------------------------------------------------------
int vtkSMRemoteObjectUpdateUndoElement::UpdateState(const vtkSMMessage* state)
{
  if(this->Session && state->has_global_id())
    {
    // Creation or update
    vtkSMRemoteObject* remoteObj =
        this->Session->GetRemoteObject(state->global_id());
    if(remoteObj)
      {
      // Update
      remoteObj->LoadState(state);
      return 1; // OK
      }
    else
      {
      vtkWarningMacro("Unable to update RemoteObject state since no remote object with id " << state->global_id() << " were found.");

      vtkCollection *remoteObjects = vtkCollection::New();
      this->Session->GetAllRemoteObjects(remoteObjects);
      cout << "List of availabe remote objects: ";
      for(int i=0;i<remoteObjects->GetNumberOfItems();i++)
        {
        cout << " " << vtkSMRemoteObject::SafeDownCast(remoteObjects->GetItemAsObject(i))->GetGlobalID();
        }
      cout << endl;
      state->PrintDebugString();

      remoteObjects->Delete();
      }
    }
  return 0; // ERROR
}

//-----------------------------------------------------------------------------
void vtkSMRemoteObjectUpdateUndoElement::SetUndoRedoState(
    const vtkSMMessage* before, const vtkSMMessage* after)
{
  this->BeforeState.Clear();
  this->AfterState.Clear();
  if(before && after)
    {
    this->BeforeState.CopyFrom(*before);
    this->AfterState.CopyFrom(*after);
    }
  else
    {
    vtkErrorMacro("Invalid SetUndoRedoState. At least one of the provided states is NULL.");
    }
}
