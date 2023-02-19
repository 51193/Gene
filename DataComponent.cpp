#include "DataComponent.h"

DataComponent::DataComponent(DataTemplate& data_template)
    :data{data_template.getData()}
{
}

const unsigned int DataComponent::get(const std::string& data_name)
{
    return this->data[data_name];
}
