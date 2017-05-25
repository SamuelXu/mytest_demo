#!env python

#def makeHtmlTag(tag, *args, **kwds):
#    def real_decorator(fn):
#        css_class = " class='{0}'".format(kwds["css_class"]) \
#                if "css_class" in kwds else ""
#
#        def wrapper(*args, **kwds):
#            return "<"+tag+css_class+">"+fn(*args, **kwds)+"</"+tag+">"
#        return wrapper
#
#    return real_decorator


class makeHtmlTagClass(object):
    def __init__(self, tag, css_class=""):
        self._tag = tag
        self._css_class = " class='{0}'".format(css_class) \
                if css_class != "" else ""

    def __call__(self, fn):
        def wrapper(*args, **kwargs):
            return "<" + self._tag + self._css_class + ">" \
                    + fn(*args, **kwargs) + "</" + self._tag + ">"
        return wrapper


#@makeHtmlTag(tag="b", css_class="bold_css")
#@makeHtmlTag(tag="i", css_class="italic_css")
@makeHtmlTagClass(tag="b", css_class="bold_css")
@makeHtmlTagClass(tag="i", css_class="italic_css")
def hello():
    return "hello world"

print hello()

