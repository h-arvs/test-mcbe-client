target_sources(client PRIVATE
	"imgui.cpp"
	"imgui_demo.cpp"
	"imgui_draw.cpp"
	"imgui_impl_dx12.cpp"
	"imgui_impl_win32.cpp"
	"imgui_tables.cpp"
	"imgui_widgets.cpp"
)

target_include_directories(client PRIVATE "${CMAKE_CURRENT_LIST_DIR}")