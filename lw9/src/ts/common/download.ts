function download(content: string, fileName: string) {
    const a = document.createElement('a')
    const file = new Blob([content], {type: 'text/plain'})
    a.href = URL.createObjectURL(file)
    a.download = fileName
    a.click()
    a.remove()
}

export {
    download,
}