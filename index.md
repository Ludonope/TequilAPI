# Getting started

##How does the server works ?

The server works with a core and different types of module.

- The Connection module manages the network I/O and communicate with the Core through input and output queues.
- The Config Loader module, well, loads the configurations.
- Logger modules does log.
- Handlers take an http request, and if it can handle it, fill an http response.

There is also something called Filter. Thoses are functions that are called at specific stages of the request processing to modify (if needed) the data.

The Core is here to store and manage every modules.

![Picture describing how it works](https://github.com/Ludonope/TequilAPI/raw/master/how_does_it_works.png)

##The Core

It can load or unload a specific module.

```cpp
virtual IModule *load(std::string const &path);
virtual void unload(IModule *module);
```

It can set or unset one of the main modules (Config Loader and Connection).

```cpp
virtual void setConfigLoader(IConfigLoader *module);
virtual void setConnection(IConnection *module);
virtual void unsetConfigLoader(IConfigLoader *module);
virtual void unsetConnection(IConnection *module);
```

---
Here is the `SlotRegister`, it allows you to add or remove elements in a "list", with positionning priority.

```cpp
namespace teq
{
  enum class Priority
  {
    VeryLow = 0,
    Low = 1,
    Normal = 2,
    High = 3,
    VeryHigh = 4
  };
}
```

```cpp
namespace teq
{
  template <typename T>
  class SlotRegister
  {
  public:
    // ...
    T &add(IModule const *parent, T const &value, Priority priority = Priority::Normal);
    void remove(T const &value);
    void clear(IModule const *parent);
    // ...
  };
}
```

Note that the `SlotRegister` does not allow to access the stored elements.
To access thoses, we use a `SlotList` (which is a `SlotRegister`). This one allow direct access to the storage.

```cpp
namespace teq
{
  template <typename T>
  class SlotList final : public SlotRegister<T>
  {
    // ...
    size_type size() const noexcept;
    bool empty() const noexcept;
    T const &operator[](size_type index) const;
    T &operator[](size_type index);
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
  };
}
```

> The `begin()` and `end()` method will allow you to use this container in range-based for loops.

The `Filter.hpp` file also define aliases on those types for uniform usage.

```cpp
namespace teq
{
  namespace filter
  {
    enum class Type
    {
      InputData,
      Request,
      Response,
      OutputData
    };

    template <Type T>
    using Register = SlotRegister<...>;

    template <Type T>
    using List = SlotList<...>;
  }
}
```

---

Let's move back on the `ACore`.
So here are the loggers, handlers and filters getters.

```cpp
virtual SlotRegister<ILogger *> &loggers();
virtual SlotRegister<IHandler *> &handlers();

template <filter::Type T>
filter::Register<T> &get();
```

You can add a specific filter this way

```cpp
core.get<filter::Type::Request>().add(...);
```

Finally, it has a `log` method which will pass the parameters to every registered logger.

```cpp
virtual void log(LogType type, std::string const &message);
```
---
> All of these methods are already implemented in the ACore, but you are free to override them as you want.

---

The `ACore` store all of theses modules.

```cpp
// List of every loaded modules
std::vector<std::pair<std::unique_ptr<GenModule>, std::unique_ptr<IModule>>> m_modules;

// Main modules
IConfigLoader *m_configLoader;
IConnection *m_connection;

// Filter lists
filter::List<filter::Type::InputData> m_inputFilters;
filter::List<filter::Type::Request> m_requestFilters;
filter::List<filter::Type::Response> m_responseFilters;
filter::List<filter::Type::OutputData> m_outputFilters;

SlotList<IHandler *> m_handlers;
SlotList<ILogger *> m_loggers;

nlohmann::json m_config;
```

The `GenModule` stored with each `IModule` represents the dynamically loaded library, and need to be
stored as long as the corresponding module exists.

The `nlohmann::json m_config` is the global config object,
it will store every module's config.

##The http Request and Response

##IBase
Both of these elements have a lot in common. This is why there is an `http::IBase` which provide them some methods.

Firstly, you can get and set the version.

```cpp
virtual std::pair<std::int32_t, std::int32_t> version() const = 0;
virtual void setVersion(std::int32_t major = 1, std::int32_t minor = 1) = 0;
```

This would allow this usage
```cpp
req.setVersion(1, 1); // Setting the http version to 1.1

auto [major, minor] = req.version();

std::cout << "Request version is << major << '.' << minor << std::endl;
```

Same thing for the body
```cpp
virtual std::string const &body() const = 0;
virtual void setBody(std::string const &body) = 0;
```

Then you can access and manipulate the different parameters with those methods.
```cpp
virtual bool hasParam(std::string const &param) const = 0;
virtual std::string &operator[](std::string const &param) = 0;
virtual std::string const &at(std::string const &param) const = 0;
virtual std::string &at(std::string const &param) = 0;
virtual void clearParams() = 0;
virtual size_type paramCount() const noexcept = 0;

virtual iterator begin() noexcept = 0;
virtual iterator end() noexcept = 0;
virtual const_iterator begin() const noexcept = 0;
virtual const_iterator end() const noexcept = 0;
```

> Again, you can note the `begin()` and `end()` methods for range-based for loop.

Finally, both Request and Response might need to be displayed as a string.
```cpp
virtual std::string toString() = 0;
```
---
## Uri

The `http::Uri` object will be used by the `IRequest` interface.
It can store a uri of this format.

```http
https://www.ludonope.com/path/to/something.html?p=oui&p2=non&p3=ah
```

You can access the path with those methods
```cpp
std::string const &path() const;
void setPath(std::string const &path);
```

You can check if it has a certain parameter
```cpp
bool hasParam(std::string const &param) const;
```

This method allow you to get the uri as a string
```cpp
std::string toString() const;
```

Also, the global `operator<<` has been overloaded to allow using `http::Uri` directly with an `std::ostream`.
```cpp
std::ostream &operator<<(std::ostream &os, teq::http::Uri const &uri);
```

Finally, to make the Uri parameters convenient, we made it inherit an `std::map`.
```cpp
namespace teq
{
  namespace http
  {
    class Uri final : public std::map<std::string, std::vector<std::string>>
    {
      // ...
    };
  }
}
```

This way, you can use it like a regular `std::map`, with all the good methods which come with it !
```cpp
auto val = uri["search"][0];
```

Notice that it's a `std::map` of `std::string` and a `vector<std::string>`. This is because you can have a parameter more than once. For example, this is a valid uri.
```http
https://www.ludonope.com/search.php?query=hello&query=world
```
---
##IRequest

The request is quite simple. In addition of the IBase methods, it simply is composed of a method and a Uri.

```cpp
virtual Method method() const = 0;
virtual void setMethod(Method method) = 0;
virtual Uri const &uri() const = 0;
virtual void setUri(Uri const &uri) = 0;
```

The http methods are stored in an enum.
```cpp
namespace teq
{
  namespace http
  {
    enum class Method
    {
      GET,
      HEAD,
      POST,
      PUT,
      DELETE,
      CONNECT,
      OPTIONS,
      TRACE
    };
  }
}
```
---
##IResponse

Similarly, the response is simply made of a status code and a reason (the corresponding message).

```cpp
virtual StatusCode status() const = 0;
virtual void setStatus(StatusCode status) = 0;
virtual std::string const &reason() const = 0;
virtual void setReason(std::string const &reason) = 0;
```

The different status code are stored in a enum. You can add custom ones in your implementation.

```cpp
namespace teq
{
  namespace http
  {
    struct StatusCode
    {
      enum
      {
        // Informational
        Continue = 100,
        SwitchingProtocol = 101,

        // Success
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,

        // Redirection
        MultipleChoices = 300,
        MovedPermanently = 301,
        Found = 302,
        SeeOther = 303,
        NotModified = 304,
        UseProxy = 305,
        TemporaryRedirect = 307,

        // Client Error
        BadRequest = 400,
        Unauthorized = 401,
        PaymentRequired = 402,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        NotAcceptable = 406,
        ProxyAuthentificationRequired = 407,
        RequestTimeOut = 408,
        Conflict = 409,
        Gone = 410,
        LengthRequired = 411,
        PreconditionFailed = 412,
        RequestEntityTooLarge = 413,
        RequestURITooLarge = 414,
        UnsupportedMediaType = 415,
        RequestedRangeNotSatisfiable = 416,
        ExpectationFailed = 417,

        // Server Error
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeOut = 504,
        HTTPVersionNotSupported = 505
      };
    };
  }
}
```
##The modules

Every module inherit from `IModule`. This basic interface provide just what is needed to manipulate each module in the same fashion.

```cpp
namespace teq
{
  class IModule
  {
  public:
    virtual ~IModule() noexcept {}
    virtual std::string const &name() const = 0;
    virtual std::string const &description() const = 0;
    virtual void init(ACore &core, nlohmann::json const &config) = 0;
  };
}
```

The `init` method will be called by the core when it just finished loading the module.
This way, the module will be able to register itself in the right slots onto the core.

For example, a logger `init` method could look something like this
```cpp
void Logger::init(teq::ACore &core, nlohmann::json const &)
{
  core.loggers().add(this, this);
}
```

We also defined a bit mode specific module type, which is the `IMainModule`, from which inherit both the Connection module and the Configuration Loader module.

```cpp
namespace teq
{
  class IMainModule : public IModule
  {
  public:
    virtual ~IMainModule() noexcept {}
    virtual void enable() = 0;
    virtual void disable() = 0;
  };
}
```

This might allow us to launch a thread in these modules.
This will be needed by the Connection module, but it can also be used for the Connection Loader module, if we want some hot reload configuration features for example.

##The Connection module

The connection module has one major functionnality. It has to launch his own thread to manage network I/O with the client independently.

To manage this, the core will give it two `http::Message` queues.

An `http::Message` is really simple, it's just a `string` with an `id`. This is used by the connection module when it has to send a response, to which request it correspond.

```cpp
namespace teq
{
  namespace http
  {
    struct Message
    {
      std::string id;
      std::string content;
    };
  }
}
```

To achieve that, the `IConnection` interface provides those methods, in addition to the `IMainModule` ones
```cpp
virtual void setInput(std::queue<http::Message> &queue) = 0;
virtual void setOutput(std::queue<http::Message> &queue) = 0;
```

##The Configuration Loader module

The `IConfigLoader` allow the core to simply load a configuration file. Your implementation will define the file language (JSON, XML, YAML, ...), but the config itself will be stored as a JSON object (from the [nlohmann json Library](https://github.com/nlohmann/json)).

It provide a single method in complement of the `IMainModule` ones
```cpp
namespace teq
{
  class IConfigLoader : public IMainModule
  {
  public:
    virtual ~IConfigLoader() noexcept {}
    virtual void load(std::string const &path, nlohmann::json &config) = 0;
  };
}
```

##The Logger module

The `ILogger` interface only add a `log` method, which takes a `LogType` and a `string` message
```cpp
namespace teq
{
  enum class LogType
  {
    Trace,
    Debug,
    Info,
    Warning,
    Error
  };
}
```

```cpp
virtual void log(LogType type, std::string const &message) = 0;
```

##The Handler module

The handler module is also quite simple.
The `handle` method takes the input request, and the output response to fill, and returns a `bool` to indicate if it effectively handled the request.

```cpp
virtual bool handle(http::IRequest &req, http::IResponse &res) = 0;
```

For example, if you made a simple `php` file handler, it would look something like this

```cpp
bool PhpHandler::handle(http::IRequest &req, http::IResponse &res)
{
  auto path = req.uri().path();

  if (path.size() >= 4 && path.substr(path.size() - 4, 4) != ".php")
  {
    return false;
  }

  // Handle the request and fill the response
  // ...

  return true;
}
```

> Please note that this handler is only checking for ".php" extension, which is not the only php valid extension. This is only for code simplicity.

##The Filter module

And finally, the `IFilter` interface. This one is a little bit different, in the fact that it doesn't add any method.
It is only used as a Marker Interface, for polymophism and readability.

Why doesn't it have any method ?
Because filters themselves are functions, and not a module.
With the `IModule::init(...)` method, you can add callbacks in the differents filter registers.

There are 4 different types of filter
```cpp
namespace teq
{
  namespace filter
  {
    enum class Type
    {
      InputData,
      Request,
      Response,
      OutputData
    };
  }
}
```
---
The `InputData` filter applies on the input `string` which comes directly from the Connection module. This is before the string is parsed as a request. It can for example apply some decryption or decompression to the data.
```cpp
std::function<void(std::string &)>
```
---
The `Request` filter applies, as the name suggest, on the request. This step occurs once the request was parsed, but before it is consumed by a handler.
```cpp
std::function<void(http::IRequest &)>
```
---
The `Response` filter is really similar to the `Request` one, it applies on the reponse right after it was filled by a handler.
```cpp
std::function<void(http::IResponse &)>
```
---
The `OutputData` filter is just as the `InputData` one, but applies on the output `string`. This one can apply encryption or compression for example.
```cpp
std::function<void(std::string &)>
```

##The Project UML
![UML of the API](https://github.com/Ludonope/TequilAPI/raw/master/project_uml.png)