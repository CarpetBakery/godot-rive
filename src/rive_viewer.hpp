#ifndef RIVEEXTENSION_VIEWER_H
#define RIVEEXTENSION_VIEWER_H

// godot-cpp
#include <godot_cpp/classes/control.hpp>

// extension
#include "rive_viewer_base.h"

using namespace godot;

class RiveViewer : public Control {
    GDCLASS(RiveViewer, Control);
    // RIVE_VIEWER_WRAPPER(RiveViewer);

private:
    RiveViewerBase base = RiveViewerBase(Object::cast_to<CanvasItem>(this));

public:
    void _draw() override {
        base.on_draw();
    }

    void _ready() override {
        set_process_internal(true);
        base.on_ready();
    }

    void _get_property_list(List<PropertyInfo> *list) const {
        base.get_property_list(list);
    }

    bool _set(const StringName &prop, const Variant &value) {
        return base.on_set(prop, value);
    }

    bool _get(const StringName &prop, Variant &return_value) const {
        return base.on_get(prop, return_value);
    }
    RIVE_VIEWER_SETGET(String, file_path)
    RIVE_VIEWER_SETGET(int, fit)
    RIVE_VIEWER_SETGET(int, alignment)
    RIVE_VIEWER_SETGET(bool, disable_press)
    RIVE_VIEWER_SETGET(bool, disable_hover)
    RIVE_VIEWER_SETGET(bool, paused)
    RIVE_VIEWER_GET(float, elapsed_time)
    RIVE_VIEWER_GET(Ref<RiveFile>, file)
    RIVE_VIEWER_GET(Ref<RiveArtboard>, artboard)
    RIVE_VIEWER_GET(Ref<RiveScene>, scene)
    RIVE_VIEWER_GET(Ref<RiveAnimation>, animation)

    void go_to_artboard(Ref<RiveArtboard> artboard) {
        base.go_to_artboard(artboard);
    }

    void go_to_scene(Ref<RiveScene> scene) {
        base.go_to_scene(scene);
    }

    void go_to_animation(Ref<RiveAnimation> animation) {
        base.go_to_animation(animation);
    }

    void press_mouse(Vector2 position) {
        base.press_mouse(position);
    }

    void release_mouse(Vector2 position) {
        base.release_mouse(position);
    }

    void move_mouse(Vector2 position) {
        base.move_mouse(position);
    }

protected:
    static void _bind_methods() {
        // RIVE_VIEWER_BIND(RiveViewer);
        ADD_PROP_WITH_HINT(RiveViewer, Variant::STRING, file_path, PROPERTY_HINT_FILE, "*.riv");
        ADD_PROP_WITH_HINT(RiveViewer, Variant::INT, fit, PROPERTY_HINT_ENUM, FitEnumPropertyHint);
        ADD_PROP_WITH_HINT(RiveViewer, Variant::INT, alignment, PROPERTY_HINT_ENUM, AlignEnumPropertyHint);
        ADD_PROP(RiveViewer, Variant::BOOL, disable_press);
        ADD_PROP(RiveViewer, Variant::BOOL, disable_hover);
        ADD_PROP(RiveViewer, Variant::BOOL, paused);
        ADD_SIGNAL(MethodInfo("pressed", PropertyInfo(Variant::VECTOR2, "position")));
        ADD_SIGNAL(MethodInfo("released", PropertyInfo(Variant::VECTOR2, "position")));
        ADD_SIGNAL(MethodInfo(
            "scene_property_changed",
            PropertyInfo(Variant::OBJECT, "scene"),
            PropertyInfo(Variant::STRING, "property"),
            PropertyInfo(Variant::VARIANT_MAX, "new_value"),
            PropertyInfo(Variant::VARIANT_MAX, "old_value")
        ));
        BIND_GET(RiveViewer, elapsed_time);
        BIND_GET(RiveViewer, file);
        BIND_GET(RiveViewer, artboard);
        BIND_GET(RiveViewer, scene);
        BIND_GET(RiveViewer, animation);
        ClassDB::bind_method(D_METHOD("go_to_artboard", "artboard"), &RiveViewer::go_to_artboard);
        ClassDB::bind_method(D_METHOD("go_to_scene", "scene"), &RiveViewer::go_to_scene);
        ClassDB::bind_method(D_METHOD("go_to_animation", "animation"), &RiveViewer::go_to_animation);
        ClassDB::bind_method(D_METHOD("press_mouse", "position"), &RiveViewer::press_mouse);
        ClassDB::bind_method(D_METHOD("release_mouse", "position"), &RiveViewer::release_mouse);
        ClassDB::bind_method(D_METHOD("move_mouse", "position"), &RiveViewer::move_mouse);
    }

public:
    void _notification(int what) {
        switch (what) {
            case NOTIFICATION_INTERNAL_PROCESS:
            case NOTIFICATION_PROCESS:
                base.on_process(get_process_delta_time());
                break;
            case NOTIFICATION_RESIZED:
                base.set_size(get_size());
                break;
        }
    }

    void _gui_input(const Ref<InputEvent> &event) override {
        base.on_input_event(event);
    }
};

#endif