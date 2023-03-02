#include "DataComponent.h"

DataComponent::DataComponent()
    :is_loaded{ false }
{
}

void DataComponent::loadFromTemplate(DataComponentTemplate& data_template)
{
    this->data = data_template.getData();
    this->is_loaded = true;
}

const bool DataComponent::isLoaded()
{
    return this->is_loaded;
}

const unsigned int DataComponent::get(const std::string& data_name)
{
    return this->data[data_name];
}
