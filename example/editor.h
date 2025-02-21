//	TextEditor - A syntax highlighting text editor for ImGui
//	Copyright (c) 2024-2025 Johan A. Goossens. All rights reserved.
//
//	This work is licensed under the terms of the MIT license.
//	For a copy, see <https://opensource.org/licenses/MIT>.


//
//	Include files
//

#include <functional>
#include <string>

#include "../TextEditor.h"


//
//	Editor
//

class Editor {
public:
	// constructor
	Editor();

	// file releated functions
	void newFile();
	void openFile();
	void openFile(const std::string& path);
	void saveFile();

	// manage program exit
	void tryToQuit();
	inline bool isDone() const { return done; }

	// render the editor
	void render();

	private:
	// private functions
	void renderMenubar();
	void renderStatusbar();

	void showFileOpen();
	void showSaveFileAs();
	void showConfirmClose(std::function<void()> callback);
	void showConfirmQuit();
	void showError(const std::string& message);

	void renderFileOpen();
	void renderSaveAs();
	void renderConfirmClose();
	void renderConfirmQuit();
	void renderConfirmError();

	inline bool isDirty() const { return editor.GetUndoIndex() != version; }
	inline bool isSavable() const { return isDirty() && filename != "untitled"; }

	// properties
	TextEditor editor;
	std::string filename;
	size_t version;
	bool done = false;
	std::string errorMessage;
	std::function<void()> onConfirmClose;

	// editor state
	enum class State {
		edit,
		newFile,
		openFile,
		saveFileAs,
		confirmClose,
		confirmQuit,
		confirmError
	} state = State::edit;
};
