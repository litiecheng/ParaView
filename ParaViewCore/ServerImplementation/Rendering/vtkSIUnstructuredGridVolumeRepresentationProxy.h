/*=========================================================================

  Program:   ParaView
  Module:    vtkSIUnstructuredGridVolumeRepresentationProxy.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSIUnstructuredGridVolumeRepresentationProxy - representation that can be used to
// show a unstructured grid volume in a render view.
// .SECTION Description
// vtkSIUnstructuredGridVolumeRepresentationProxy is a concrete representation that can be used
// to render the unstructured grid volume in a vtkSIRenderViewProxy.

#ifndef vtkSIUnstructuredGridVolumeRepresentationProxy_h
#define vtkSIUnstructuredGridVolumeRepresentationProxy_h

#include "vtkPVServerImplementationRenderingModule.h" //needed for exports
#include "vtkSIProxy.h"

class VTKPVSERVERIMPLEMENTATIONRENDERING_EXPORT vtkSIUnstructuredGridVolumeRepresentationProxy : public vtkSIProxy
{
public:
  static vtkSIUnstructuredGridVolumeRepresentationProxy* New();
  vtkTypeMacro(vtkSIUnstructuredGridVolumeRepresentationProxy, vtkSIProxy);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkSIUnstructuredGridVolumeRepresentationProxy();
  ~vtkSIUnstructuredGridVolumeRepresentationProxy();

  // Description:
  // Register the mappers
  bool CreateVTKObjects() VTK_OVERRIDE;


private:
  vtkSIUnstructuredGridVolumeRepresentationProxy(const vtkSIUnstructuredGridVolumeRepresentationProxy&) VTK_DELETE_FUNCTION;
  void operator=(const vtkSIUnstructuredGridVolumeRepresentationProxy&) VTK_DELETE_FUNCTION;

};

#endif
