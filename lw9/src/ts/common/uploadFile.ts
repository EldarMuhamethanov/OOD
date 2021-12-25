function uploadFile(onUploadCallback: (result: Object) => void) {
    const input = document.createElement('input')
    input.setAttribute('type', 'file')
    input.click()
    input.addEventListener("change", () => {
        const reader = new FileReader()
        const selectedFile =  input.files && input.files[0]
        if (selectedFile) {
            reader.onload = () => {
                if (typeof reader.result === 'string') {
                    onUploadCallback(JSON.parse(reader.result))
                }
            }
            reader.readAsText(selectedFile)
        }
    })
}

export {
    uploadFile,
}