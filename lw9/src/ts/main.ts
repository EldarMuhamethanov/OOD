import {EditorModel} from "./editor/EditorModel";
import {EditorRenderer} from "./editor/EditorRenderer";

function startApp() {
    const editor: EditorModel = new EditorModel()
    const editorRenderer: EditorRenderer = new EditorRenderer(editor)
    editorRenderer.render()
}

window.onload = () => {
    startApp()
}