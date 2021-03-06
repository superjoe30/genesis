#ifndef DOCKABLE_PANE_WIDGET
#define DOCKABLE_PANE_WIDGET

#include "widget.hpp"

#include <assert.h>

class DockablePaneWidget;
class TabWidget;
class Label;
struct SpritesheetImage;

struct DockablePaneTab {
    DockablePaneWidget *pane;
};

enum DockAreaLayout {
    DockAreaLayoutTabs,
    DockAreaLayoutHoriz,
    DockAreaLayoutVert,
};

class DockAreaWidget : public Widget {
public:
    DockAreaWidget(GuiWindow *window);
    ~DockAreaWidget() override;

    void draw(const glm::mat4 &projection) override;
    void on_mouse_move(const MouseEvent *event) override;
    void on_drag(const DragEvent *event) override;
    void on_resize() override { update_model(); }

    void add_left_pane(DockablePaneWidget *pane);
    void add_right_pane(DockablePaneWidget *pane);
    void add_top_pane(DockablePaneWidget *pane);
    void add_bottom_pane(DockablePaneWidget *pane);
    void add_tab_pane(DockablePaneWidget *pane);


    void add_left_dock_area(DockAreaWidget *dock_area);
    void add_right_dock_area(DockAreaWidget *dock_area);
    void add_top_dock_area(DockAreaWidget *dock_area);
    void add_bottom_dock_area(DockAreaWidget *dock_area);

    void set_auto_hide_tabs(bool value);

    void collapse();
    void remove_a();
    void remove_b();

    // destroys all children and resets state
    void reset_state();

    DockAreaLayout layout;
    DockAreaWidget *child_a; // left/top
    DockAreaWidget *child_b; // right/bottom
    TabWidget *tab_widget; // if layout == DockAreaLayoutTabs
    float split_ratio;
    int split_area_size; // width/height of the split ui
    glm::mat4 split_border_start_model;
    glm::mat4 split_border_end_model;
    glm::vec4 light_border_color;
    glm::vec4 dark_border_color;
    bool resize_down;
    int resize_down_pos;
    float resize_down_ratio;
    bool auto_hide_tabs;
    glm::mat4 insert_arrow_model;
    bool insert_tab_arrow;
    glm::vec4 insert_tab_arrow_color;

    bool show_drop_lines;
    int center_drop_left;
    int center_drop_top;
    int center_drop_width;
    int center_drop_height;
    int center_drop_right;
    int center_drop_bottom;
    glm::mat4 drop_lines[4];
    Label *drop_area_labels[5];
    glm::mat4 drop_area_label_models[5];
    const SpritesheetImage *drop_area_icon;
    glm::mat4 drop_area_icon_model;

    DockAreaWidget * transfer_state_to_new_child();
    void transfer_state(DockAreaWidget *source, DockAreaWidget *dest);
    void add_tab_widget(DockablePaneWidget *pane);
    DockAreaWidget *create_dock_area_for_pane(DockablePaneWidget *pane);
    void update_model();
    void handle_tab_drag(const DragEvent *event);
    void clear_drag_ui();
};

class DockablePaneWidget : public Widget {
public:
    DockablePaneWidget(Widget *child, const String &title);
    ~DockablePaneWidget() override {}

    void draw(const glm::mat4 &projection) override;
    void on_mouse_move(const MouseEvent *event) override;
    void on_drag(const DragEvent *event) override;
    void on_resize() override;

    Widget *child;
    String title;
};

#endif
