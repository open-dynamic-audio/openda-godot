
#include "register_types.h"

// Godot headers
#include "object_type_db.h"
#include "reference.h"
#include "ustring.h"

// Wrap for oda
#include "engine.h"

#include <vector>
#include <string>

using std::string;
using std::vector;

class ODAModule : public Reference {
  OBJ_TYPE(ODAModule, Reference);
  public:
    bool start (const String &path) {
      return engine_.start(vector<string>(1, path.ascii().get_data()));
    }
    bool ok () const { return engine_.ok(); }
    size_t eventInstance (const String &name) {
      return engine_.eventInstance(name.ascii().get_data());
    }
    void tick (double dt) {
      engine_.tick(dt);
    }
  protected:
    static void _bind_methods () {
      ObjectTypeDB::bind_method("ok", &ODAModule::ok);
      ObjectTypeDB::bind_method("start", &ODAModule::start);
      ObjectTypeDB::bind_method("eventInstance", &ODAModule::eventInstance);
      ObjectTypeDB::bind_method("tick", &ODAModule::tick);
    }
  private:
    oda::godot::Engine engine_;
};

void register_openda_types () {
  ObjectTypeDB::register_type<ODAModule>();
}

void unregister_openda_types () {
  // nothing at all?
}

