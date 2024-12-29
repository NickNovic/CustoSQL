**Architecture**

I prefer to use Clean architecture in this project:
https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html

Project structure:




##
**Presentation**

I think now for presentation layer there would be an API with HTTP querries but in future I hope we will use TCP/IP protocol of communication for our application.


**Infrastructure**

**-------------------**

**Application**

In application layer there would be USE-Cases system. Now I'm not sure about structure because any SQL querry contains a lot of "actions" so I would need somehow controll all of them, maybe split a querry on subquerries etc.

**Domain**

Here domain layer would contain basic types wrotten by me and some structures like tables or databases. Also, I think, there should be model for an Querry and for querry output.