"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var EditorRenderer_1 = require("./view/EditorRenderer");
var EditorModel_1 = require("./model/EditorModel");
function startApp() {
    var editorModel = new EditorModel_1.EditorModel();
    var editorRenderer = new EditorRenderer_1.EditorRenderer(editorModel);
    editorRenderer.render(document.body);
}
window.onload = function () {
    startApp();
};
//# sourceMappingURL=main.js.map