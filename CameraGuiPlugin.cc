#include <QtCore/qobjectdefs.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qframe.h>
#include <QtWidgets/qpushbutton.h>

#include <gazebo/common/Console.hh>
#include <gazebo/transport/TransportIface.hh>
#include <gazebo/transport/TransportTypes.hh>

#include <sstream>

#include <gazebo/msgs/msgs.hh>

#include <vector>

#include "CameraGuiPlugin.hh"

using namespace gazebo;

GZ_REGISTER_GUI_PLUGIN(CameraGuiPlugin)

CameraGuiPlugin::CameraGuiPlugin() : GUIPlugin(){
	
	this -> setStyleSheet(
			"QFrame { background-color : rgba(100, 100, 100, 255); color : white;}");
	
	QHBoxLayout *mainLayout = new QHBoxLayout;

	QFrame *mainFrame = new QFrame();

	QVBoxLayout *frameLayout = new QVBoxLayout();
	
	// QPushButton *button = new QPushButton(tr("Camera"));
	cmb = new QComboBox();
	
	cmb->setSizeAdjustPolicy(QComboBox::AdjustToContents);	
	std::list<std::string> topics = camera_topics();	
	
	for ( auto topic: topics){
		cmb->addItem(topic.c_str());
	}
	
	connect(cmb, SIGNAL(activated(int)), this, SLOT(OnButton(int)));

	// connect(button,  SIGNAL(clicked()), this, SLOT(OnButton()));

	frameLayout->addWidget(cmb);

	mainFrame->setLayout(frameLayout);
	
	mainLayout->addWidget(mainFrame);

	// Remove margins to reduce space
	frameLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setContentsMargins(0, 0, 0, 0);

	this->setLayout(mainLayout);

	this->move(10, 10);
        // this->resize(120, 40);
	
	this->node = transport::NodePtr(new transport::Node());

	this->node->Init();
	
	
}

std::list<std::string> CameraGuiPlugin::camera_topics(){
	
	std::map<std::string, std::list<std::string>> topic_type = transport::getAdvertisedTopics();
		
	return topic_type["gazebo.msgs.ImageStamped"];
}
CameraGuiPlugin::~CameraGuiPlugin(){
}

void CameraGuiPlugin::camera_callback(ConstImageStampedPtr& msg){
	
	cv::Mat mRGBAImg = cv::Mat(cv::Size(msg->image().width(),msg->image().height()),CV_8UC3);
	
	memcpy(mRGBAImg.data,msg->image().data().c_str(),msg->image().data().size());

	cv::imshow("Camera Feed", mRGBAImg);
	cv::waitKey(1);
}
void CameraGuiPlugin::OnButton(int x){
	
	gzmsg << x <<'\n';
	this->cameraSub = node->Subscribe( cmb->itemText(x).toStdString(), 
			 &CameraGuiPlugin::camera_callback, this);
}

