#include <Task.h>
extern TaskManager taskManager;
class Nitrate : public Task
{
  public:
    static Nitrate *s_instance;
    Nitrate() : Task(MsToTaskTime(100))
    {
        current_time = 0;
    }
    static Nitrate *instance()
    {
        if (!s_instance)
            s_instance = new Nitrate;
        return s_instance;
    }

  private:
    float current_time;
    virtual bool OnStart()
    {
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        current_time += delta_time / 1000;
        if (current_time >= 2000)
        {
            sendRequest();
            current_time = 0;
        }

        while (sensorCom.available())
        {
            int data = sensorCom.read();
            mpuCom.println(data);
        }
    }

    void sendRequest()
    {
        byte req[8] = {0x01, 0x03, 0x00, 0x07, 0x00, 0x01, 0x35, 0xCB};
        sensorCom.write(req,8);
    }
};
Nitrate *Nitrate::s_instance = 0;