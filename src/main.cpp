// This node will recognize the kind of activity a human is involved in.

#include <ros/ros.h>
#include <toaster_msgs/Fact.h>
#include <toaster_msgs/FactList.h>
#include "toaster_msgs/GetFacts.h"
#include "toaster_msgs/AddFact.h"
#include <iterator>

int main(int argc, char** argv) {

    ros::init(argc, argv, "activity_recognition");
    ros::NodeHandle node;

    //Services clients
    ros::ServiceClient getFactsClient = node.serviceClient<toaster_msgs::GetFacts>("/belief_manager/get_fact_value", true);

    //Services servers

    // Publishing
    ros::Publisher fact_pub = node.advertise<toaster_msgs::FactList>("activity_recognition/factList", 1000);

    // Set this in a ros service?
    ros::Rate loop_rate(30);

    toaster_msgs::Fact monitorFact;
    toaster_msgs::Fact vendingMachineFact;
    toaster_msgs::Fact touristicPointFact;

    std::string property = "IsInArea";
    std::string monitor = "monitor";
    std::string vendingMachine = "vendingMachine";
    std::string touristicPoint = "touristicPoint";

    while (node.ok()) {
        toaster_msgs::FactList factList_msg;
        toaster_msgs::Fact fact_msg;

        toaster_msgs::GetFacts getFactsMonitor;
        toaster_msgs::GetFacts getFactsVending;
        toaster_msgs::GetFacts getFactsTouristic;


        getFactsMonitor.request.reqFact.property = property;
        getFactsMonitor.request.reqFact.subProperty = monitor;

        getFactsVending.request.reqFact.property = property;
        getFactsVending.request.reqFact.subProperty = vendingMachine;

        getFactsTouristic.request.reqFact.property = property;
        getFactsTouristic.request.reqFact.subProperty = touristicPoint;

        if (getFactsClient.call(getFactsMonitor)) {
            for (std::vector<toaster_msgs::Fact>::iterator it = getFactsMonitor.response.resFactList.factList.begin();
                    it != getFactsMonitor.response.resFactList.factList.end(); ++it) {

                // Fact watching monitor
                fact_msg.property = "IsWatchingMonitor";
                fact_msg.propertyType = "activity";
                //fact_msg.subProperty = ;
                fact_msg.subjectId = (*it).subjectId;
                fact_msg.subjectName = (*it).subjectName;
                fact_msg.targetName = (*it).targetName;
                fact_msg.targetId = (*it).subjectId;
                fact_msg.confidence = (*it).confidence;
                //fact_msg.doubleValue = angleResult;
                //fact_msg.valueType = 1;
                fact_msg.factObservability = 0.5;
                fact_msg.time = (*it).time;

                factList_msg.factList.push_back(fact_msg);


            }


        }


        if (getFactsClient.call(getFactsVending)) {
for (std::vector<toaster_msgs::Fact>::iterator it = getFactsMonitor.response.resFactList.factList.begin();
                    it != getFactsMonitor.response.resFactList.factList.end(); ++it) {

                // Fact vending machine
                fact_msg.property = "IsUsingVendingMachine";
                fact_msg.propertyType = "activity";
                //fact_msg.subProperty = ;
                fact_msg.subjectId = (*it).subjectId;
                fact_msg.subjectName = (*it).subjectName;
                fact_msg.targetName = (*it).targetName;
                fact_msg.targetId = (*it).subjectId;
                fact_msg.confidence = (*it).confidence;
                //fact_msg.doubleValue = angleResult;
                //fact_msg.valueType = 1;
                fact_msg.factObservability = 0.5;
                fact_msg.time = (*it).time;

                factList_msg.factList.push_back(fact_msg);


            }


        }


        if (getFactsClient.call(getFactsTouristic)) {
for (std::vector<toaster_msgs::Fact>::iterator it = getFactsMonitor.response.resFactList.factList.begin();
                    it != getFactsMonitor.response.resFactList.factList.end(); ++it) {

                // Fact watching monitor
                fact_msg.property = "IsEnjoyingTouristicPoint";
                fact_msg.propertyType = "activity";
                //fact_msg.subProperty = ;
                fact_msg.subjectId = (*it).subjectId;
                fact_msg.subjectName = (*it).subjectName;
                fact_msg.targetName = (*it).targetName;
                fact_msg.targetId = (*it).subjectId;
                fact_msg.confidence = (*it).confidence;
                //fact_msg.doubleValue = angleResult;
                //fact_msg.valueType = 1;
                fact_msg.factObservability = 0.5;
                fact_msg.time = (*it).time;

                factList_msg.factList.push_back(fact_msg);


            }


        }


        fact_pub.publish(factList_msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

}
