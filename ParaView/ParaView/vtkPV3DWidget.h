/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPV3DWidget.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkPV3DWidget - superclass of 3D Widgets
// .SECTION Description

// Todo:
// Cleanup GUI:
//       * Visibility
//       * Resolution
//       *

#ifndef __vtkPV3DWidget_h
#define __vtkPV3DWidget_h

#include "vtkPVObjectWidget.h"

class vtkKWCheckButton;
class vtkKWLabeledFrame;
class vtk3DWidget;
class vtkPV3DWidgetObserver;
class vtkKWFrame;

class VTK_EXPORT vtkPV3DWidget : public vtkPVObjectWidget
{
public:
  vtkTypeRevisionMacro(vtkPV3DWidget, vtkPVObjectWidget);

  void PrintSelf(ostream& os, vtkIndent indent);

  virtual void Create(vtkKWApplication *pvApp);
  
  // Description:
  // Called when accept button is pushed.  
  // Sets objects variable to the widgets value.
  // Adds a trace entry.  Side effect is to turn modified flag off.
  virtual void Accept();
  virtual void Accept(const char* sourceTclName);
  
  // Description:
  // Called when the reset button is pushed.
  // Sets widget's value to the object-variable's value.
  // Side effect is to turn the modified flag off.
  virtual void Reset();
  virtual void Reset(const char* sourceTclName);

  // Description:
  // Set the widget visibility.
  void SetVisibility();
  void SetVisibility(int val);
  void SetVisibilityNoTrace(int val);
  vtkBooleanMacro(Visibility, int);

  // Description:
  // Set modified to 1 when value has changed.
  void SetValueChanged();

  // Description:
  // This method is called when the source that contains this widget
  // is selected. 
  virtual void Select();

  // Description:
  // This method is called when the source that contains this widget
  // is deselected. 
  virtual void Deselect();

  // Description:
  // This method sets the input to the 3D widget and places the widget.
  virtual void PlaceWidget();

  // Description:
  // This method does the actual placing. If the subclass is doing
  // something fancy, it should overwrite it.
  virtual void ActualPlaceWidget();

  // Description:
  // Get the 3D Widget.
  vtkGetObjectMacro(Widget3D, vtk3DWidget);

  // Description:
  // Determines whether there is a label-border around the widget
  // ui.
  vtkSetMacro(UseLabel, int);
  vtkGetMacro(UseLabel, int);

protected:
  vtkPV3DWidget();
  ~vtkPV3DWidget();

  void Render();
  
  vtk3DWidget* Widget3D;
  vtkPV3DWidgetObserver* Observer;

  // Description:
  // Set label of the frame
  void SetFrameLabel(const char* label);

  // Description:
  // Call creation on the child.
  virtual void ChildCreate(vtkPVApplication*) = 0;

  // Description:
  // Set the 3D widget we are observing.
  void SetObservable3DWidget(vtk3DWidget*);

//BTX
  virtual void CopyProperties(vtkPVWidget* clone, vtkPVSource* pvSource,
                              vtkArrayMap<vtkPVWidget*, vtkPVWidget*>* map);

  friend class vtkPV3DWidgetObserver;
//ETX

  // Description:
  // Execute event of the 3D Widget.
  virtual void ExecuteEvent(vtkObject*, unsigned long, void*);
  
  virtual int ReadXMLAttributes(vtkPVXMLElement* element,
                                vtkPVXMLPackageParser* parser);

  vtkKWFrame*        Frame;
  vtkKWLabeledFrame* LabeledFrame;
  vtkKWCheckButton* Visibility;
  int ValueChanged;
  int Placed;
  int Visible;
  int UseLabel;

private:  
  vtkPV3DWidget(const vtkPV3DWidget&); // Not implemented
  void operator=(const vtkPV3DWidget&); // Not implemented
};

#endif
