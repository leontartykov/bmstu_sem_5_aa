class Error(Exception):
    pass

class MismatchtMatrixSizesMul(Error):
    def __init__(self, message='Несовпадение размеров матриц'):
        self.message = message
        super().__init__(self.message)
    pass