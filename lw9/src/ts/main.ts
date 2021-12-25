import {EditorRenderer} from "./view/EditorRenderer";
import {EditorModel} from "./model/EditorModel";

function startApp() {
    const editorModel = new EditorModel()
    const editorRenderer = new EditorRenderer(editorModel)
    editorRenderer.render(document.body)
}

window.onload = () => {
    startApp()
}