/*
	If you use a hell of a built-in property at a big golfing challenge 
	you can alias every property to a one character equivalent:
*/

[Math,Number,S=String,Array].map(b=>
    Object.getOwnPropertyNames(b).map((p,i)=>
        b.prototype[S.fromCharCode(i+248)]=b[p]
    )
)
/*
	After executing the code above you can use it like this:
*/
"foo".Č(/.*/,'bar') // replaces foo with bar
/*
	It may be browser dependent and i'm not sure if it's shorter than 
	with(Array){join(foo),...} or defining variables as used properties 
	with(Array){j=join,m=map...} but still it is worth mentioning.
*/