
//
// This example introduces the concepts of interaction into the
// C++ environment. A different interaction style (than
// the default) is defined.定义了除默认的交互外的新的交互动作
//

// First include the required header files for the VTK classes we are using.
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"

int main()
{
  //
  // Next we create an instance of vtkConeSource and set some of its
  // properties. The instance of vtkConeSource "cone" is part of a
  // visualization pipeline (it is a source process object); it produces data
  // (output type is vtkPolyData) which other filters may process.
  //
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight( 3.0 );//cone的高
  cone->SetRadius( 1.0 );//底部半径
  cone->SetResolution( 20 );//设置cone的棱的数目

  //
  // In this example we terminate终结 the pipeline with a mapper process object.
  // (Intermediate中间的 filters such as vtkShrinkPolyData could be inserted in
  // between the source and the mapper.)  We create an instance of
  // vtkPolyDataMapper to map the polygonal data into graphics primitives图元. We
  // connect the output of the cone souece to the input of this mapper.
  //创建vtkPolyDataMapper对象来将多边形数据变为图元，将cone源的输出与绘图的输入相连
  //
  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection( cone->GetOutputPort() );

  //
  // Create an actor to represent the cone. The actor orchestrates编排 rendering
  // of the mapper's graphics primitives. An actor also refers to properties
  // via a vtkProperty instance, and includes an internal transformation
  // matrix. We set this actor's mapper to be coneMapper which we created
  // above.
  //
  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper( coneMapper );//将actor和可视化管道的末尾连接起来

  //
  // Create the Renderer渲染器 and assign actors to it. A renderer is like a
  // viewport观察孔. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the background
  // color here.
  //将actor分配给渲染器，也可以在此设置背景颜色
  //
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( coneActor );
  ren1->SetBackground( 0.0, 0.2, 0.4 );//设置绘制窗口的颜色

  //
  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.
  //将渲染器的结果发送到渲染窗口，并且设置窗口的初始大小
  //
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 300, 300 );//窗口大小

  //
  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
  // mouse) in the vtkRenderWindow. These events are translated into
  // event invocations请求 that VTK understands (see VTK/Common/vtkCommand.h
  // for all events that VTK processes). Then observers of these VTK
  // events can process them as appropriate.
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);//将交互动作发送给渲染窗口

  //
  // By default the vtkRenderWindowInteractor instantiates实例化 an instance
  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
  // it observes into operations on the camera, actors, and/or properties
  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
  // Here we specify a particular interactor style.
  vtkInteractorStyleTrackballCamera *style =
    vtkInteractorStyleTrackballCamera::New();
  iren->SetInteractorStyle(style);

  //
  // Unlike the previous scripts where we performed some operations and then
  // exited, here we leave an event loop running循环运行. The user can use the mouse
  // and keyboard to perform the operations on the scene according to the
  // current interaction style. When the user presses the "e" key, by default
  // an ExitEvent is invoked by the vtkRenderWindowInteractor which is caught
  // and drops out of the event loop (triggered by the Start() method that
  // follows.
  //
  iren->Initialize();
  iren->Start();

  //
  // Final note: recall that an observers can watch for particular events and
  // take appropriate action. Pressing "u" in the render window causes the
  // vtkRenderWindowInteractor to invoke a UserEvent. This can be caught to
  // popup a GUI, etc. So the Tcl Cone5.tcl example for an idea of how this
  // works.

  //
  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.
  //
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  ren1->Delete();
  renWin->Delete();
  iren->Delete();
  style->Delete();//退出时删除所有创造的实例

  return 0;
}
