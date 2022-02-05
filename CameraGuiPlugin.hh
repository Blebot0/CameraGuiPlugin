#ifndef GZ_GUI_CAMERA_PLUGIN_HH
#define GZ_GUI_CAMERA_PLUGIN_HH

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <gazebo/msgs/image_stamped.pb.h>
#include <gazebo/transport/TransportTypes.hh>
#include <string>
#include <gazebo/gui/GuiPlugin.hh>

#ifndef Q_MOC_RUN
#include <gazebo/transport/transport.hh>
#endif


namespace gazebo
{
	class GAZEBO_VISIBLE CameraGuiPlugin : public GUIPlugin
	{
		Q_OBJECT

		// Default Constructor
		public: CameraGuiPlugin();

		// Default Destructor		
		public:	virtual ~CameraGuiPlugin();
      		
		// Callback triggered when Button is Pressed
		protected slots: void OnButton();

		// Node used to establish connection with gzserver
		private: transport::NodePtr node;

		// Subscriber for camera feedback
		private: transport::SubscriberPtr cameraSub;

		private: void camera_callback(ConstImageStampedPtr& ) ;
	};	
}
#endif
